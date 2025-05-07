// Edgar Ramirez
// 4-25-25
// Project 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WORD 5
#define GUESSES 6
#define WORDS 40

void getWord(char list[][WORD + 1], int *wordCount);
void lowerCase(char str[]);
bool expectedGuess(char guess[]);
void userGuess(char guess[]);
void checkGuess(char guess[], char word[], bool samePlace[], bool rightMarks[]);
void showcase(char guesses[][WORD + 1], bool same[][WORD], bool rightMarks[][WORD], char word[]);

int main() {
    char list[WORDS][WORD + 1];
    int numWords = 0;
    char word[WORD + 1];

    getWord(list, &numWords);

    if (numWords == 0) {
        printf("No valid words found in word2.txt. Exiting.\n");
        return 1;
    }

    srand(time(NULL));
    int randomWord = rand() % numWords;

    for (int i = 0; i <= WORD; i++) {
        word[i] = list[randomWord][i];
    }

    lowerCase(word);

    char guesses[GUESSES][WORD + 1] = {0};
    bool same[GUESSES][WORD] = {0};
    bool rightMarks[GUESSES][WORD] = {0};
    int guessChecker = 0;
    bool winner = false;

    printf("Welcome, take a seat and give Wordup a try!\n");

    while (guessChecker < GUESSES && !winner) {
        printf("Guess %d! ", guessChecker + 1);
        char guess[WORD + 1];
        userGuess(guess);
        lowerCase(guess);

        for (int i = 0; i < WORD; i++) {
            guesses[guessChecker][i] = guess[i];
        }
        guesses[guessChecker][WORD] = '\0';

        checkGuess(guess, word, same[guessChecker], rightMarks[guessChecker]);

        winner = true;
        for (int i = 0; i < WORD; i++) {
            if (!same[guessChecker][i]) {
                winner = false;
                break;
            }
        }

        showcase(guesses, same, rightMarks, word);
        guessChecker++;
    }

    if (winner) {
        printf("\nYou beat Wordup in %d guesses, good job!\n", guessChecker);
    } else {
        printf("\nYou lost the game of Wordup, the word was '%s'.\n", word);
    }

    return 0;
}

void getWord(char list[][WORD + 1], int *numWords) {
    FILE *readFilePointer = fopen("word2.txt", "r");
    if (readFilePointer == NULL) {
        printf("Cannot open word2.txt\n");
        return;
    }

    char temporary[40];
    while (fgets(temporary, 40 , readFilePointer)) {
        int length = 0;
        while (temporary[length] != '\n' && temporary[length] != '\0') 
        	length++;
        if (length == WORD && *numWords < WORDS) {
		for (int i = 0; i < WORD; i++) {
                list[*numWords][i] = temporary[i];
            }
            list[*numWords][WORD] = '\0';
            (*numWords)++;
        }
    }

    fclose(readFilePointer);
}

void lowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}

bool expectedGuess(char guess[]) {
    for (int i = 0; i < WORD; i++) {
        char w = guess[i];
        if (!((w >= 'A' && w <= 'Z') || (w >= 'a' && w <= 'z'))) {
            return false;
        }
    }
    return true;
}

void userGuess(char guess[]) {
    while (1) {
        printf("Enter your guess of 5 letters here:\n");
        scanf("%s", guess);

        int i = 0;
        while (guess[i] != '\0') i++;
        if (i == WORD) {
            break;
        } else {
            printf("You must enter a word that's 5 letters, try again.\n");
        }
    }
}

void checkGuess(char guess[], char word[], bool samePlace[], bool rightMarks[]) {
    bool used[WORD] = {false};
    for (int i = 0; i < WORD; i++) {
        samePlace[i] = (guess[i] == word[i]);
        if (samePlace[i]) {
            used[i] = true;
        }
        rightMarks[i] = false;
    }

    for (int i = 0; i < WORD; i++) {
        if (!samePlace[i]) {
            for (int b = 0; b < WORD; b++) {
                if (!used[b] && guess[i] == word[b]) {
                    rightMarks[i] = true;
                    used[b] = true;
                    break;
                }
            }
        }
    }
}

void showcase(char guesses[][WORD + 1], bool same[][WORD], bool rightMarks[][WORD], char word[]) {
    for (int g = 0; g < GUESSES; g++) {
        if (guesses[g][0] == '\0')
            break;

        for (int i = 0; i < WORD; i++) {
            char wrd = guesses[g][i];
            if (same[g][i] && wrd >= 'a' && wrd <= 'z') {
                wrd = wrd - 'a' + 'A';
            }
            printf("%c", wrd);
        }
        printf("\n");

        for (int i = 0; i < WORD; i++) {
            if (rightMarks[g][i]) {
                printf("^");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
