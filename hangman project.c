#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_SIZE_OF_WORD 32

// every func used in this program
void addToList();
void printStartMenu();
void createNewGame();
void continueToGame();
void printTree();
void getInput();

struct linked_list_node {
    char data[MAX_SIZE_OF_WORD];
    struct linked_list_node *next;
};

typedef struct linked_list_node NODE;

// this is a pointer to the supposed "first" node
NODE *first_ptr = NULL;

void addToList(char *nameofinput) {
    NODE *new_node;

    new_node = malloc(sizeof(NODE));
    strcpy(new_node->data, nameofinput);
    new_node->next = first_ptr;

    first_ptr = new_node;
}

int main() {
    printStartMenu();
    return 0;
}

// present user with choices: start (begin adding words), and quit
void printStartMenu() {
    char nameofinput[MAX_SIZE_OF_WORD];
    char choice;
    
    printf("-------------------------------------------------\n");
    printf("\tgame of hangman\n");
    printf("-------------------------------------------------\n\n");

    printf("press 1: begin game\n");
    printf("press q: quit\n");

    while (1) {
        printf("input choice: ");
        getInput(&nameofinput);
        sscanf(nameofinput, "%c", &choice);

        switch (choice) {
            case '1':
                printf("entered 1, beginning game...\n");
                createNewGame();
                exit(0);
            case 'q':
            case 'Q':
                printf("entered q, quitting...\n");
                exit(0);
            default:
                printf("invalid key\n");
                continue;
        }
    }
}

void createNewGame() {
    char nameofinput[MAX_SIZE_OF_WORD];
    int wordcounter = 1;

    printf("first, input at least two words. one will be randomly selected.\n");

    while (1) {
        printf("enter word %d, input q to move onto the game: ", wordcounter);
        getInput(&nameofinput);

        if (strcmp(nameofinput, "q") == 0) {
            printf("continuing to game...\n");
            continueToGame();
            break;
        } else if (strcmp(nameofinput, "Q") == 0) {
            printf("continuing to game...\n");
            continueToGame();
            break;
        } else {
            addToList(nameofinput);
            wordcounter++;
            continue;
        }
    }
}

void continueToGame() {
    char guessedchar;
    char mysteryword[MAX_SIZE_OF_WORD];
    char nameofinput[MAX_SIZE_OF_WORD];

    srand(time(NULL));
    int randomnumber = (rand() % 10);

    for (int i = 0; i < randomnumber; i++) {
        if (first_ptr->data == NULL) {
            printf("there are no inputs\n");
            exit(0);
        }
        
        first_ptr = first_ptr->next;

        if (first_ptr->next == NULL) {
            break;
        }
    }

    strcpy(mysteryword, first_ptr->data);

    int lengthofword = strlen(mysteryword);
    int revealed[lengthofword];

    // each corresponding letter of mysteryword[lengthofword] has its own revealed[lengthofword]
    // if revealed[i] = 1, then print mysteryword[i], else if 0 print *
    for (int i = 0; i < lengthofword; i++) {
        revealed[i] = 0;
    }

    while (1) {
        int wincount = 0;
        printf("your word is: ");

        for (int i = 0; i < lengthofword; i++) {
            if (revealed[i] == 1) {
                printf("%c", mysteryword[i]);
            } else {
                printf("*");
            }
        }

        printf("\n");

        printf("enter a guess: ");
        getInput(&nameofinput);
        sscanf(nameofinput, "%c", &guessedchar);

        // after obtaining a letter, go through the entire word. if mysteryword[i] matches with guessedchar, revealed[i] = 1
        for (int i = 0; i < lengthofword; i++) {
            if (mysteryword[i] == guessedchar) {
                revealed[i] = 1;
            }
        }

        // win check. for each revealed[i] == 1, increment wincount. if wincount == lengthofword, player wins.
        for (int i = 0; i < lengthofword; i++) {
            if (revealed[i] == 1) {
                wincount++;
            }
        }

        if (wincount == lengthofword) {
            printf("you won! the word was %s\n", mysteryword);
            exit(0);
        }

        continue;
    }
}

void getInput(char *nameofinput) {
    fgets(nameofinput, MAX_SIZE_OF_WORD, stdin);
    nameofinput[strlen(nameofinput)-1] = '\0';
    fflush(stdin);
}