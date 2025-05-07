// Edgar Ramirez
// 4-25-25
// Project 10

#include <stdio.h>
#include <stdbool.h>
#define WORD 5
#define GUESSES 6

void getWord(char word[]);
void lowerCase(char str[]);
bool expectedGuess(char guess[]);
void userGuess(char guess[]);
void checkGuess(char guess[], char word[], bool samePlace[], bool rightMarks[]);
void showcase(char guesses[][WORD + 1], bool same[][WORD],bool rightMarks[][WORD], char word[]);

int main(){
	char word[WORD + 1];
	getWord(word);
	lowerCase(word);
	
	if(word[0] == '\0') 
	return 1;
	
	char guesses[GUESSES][WORD + 1] = {0};
	bool same[GUESSES][WORD] = {0};
	bool rightMarks[GUESSES][WORD] = {0};
	int guessChecker = 0;
	bool winner = false;
	
	printf("Welcome, take a seat and give Wordup a try!\n");

	while(guessChecker < GUESSES && !winner){
		printf("Guess %d! ", guessChecker + 1);
		char guess[WORD + 1];
		userGuess(guess);
		lowerCase(guess);
		
		for(int i = 0; i < WORD; i++){
			guesses[guessChecker][i] = guess[i];
		}
		guesses[guessChecker][WORD] = '\0';
		checkGuess(guess, word, same[guessChecker], rightMarks[guessChecker]);
		winner = true;
		for(int i = 0; i < WORD; i++){
			if(!same[guessChecker][i]){
				winner = false;
				break;
			}
		}
		
		showcase(guesses, same, rightMarks, word);
		guessChecker++;
	}
	if(winner){
		printf("\nYou beat Wordup in %d guesses, good job!\n", guessChecker);
	}
	else{
		printf("\nYou lost the game of Wordup, the word was '%s'. \n", word);
	}
return 0;
}
void getWord(char word[]){
	FILE* readFilePointer = fopen("word.txt", "r");
		if(readFilePointer == NULL){
			printf("Can not open word.txt \n");
		return;
	}
		if(fgets(word, WORD + 1, readFilePointer)){
			for(int i = 0; word[i] != '\0'; i++){
				if(word[i] == '\n'){
				word[i] = '\0';
				break;
			}
		}
	}
	fclose(readFilePointer);
	}
void lowerCase(char str[]){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] <= 'Z' && str[i] >= 'A'){
			str[i] += 'a' - 'A';
			}
		}
	}
bool expectedGuess(char guess[]){
	for(int i = 0; i < WORD; i++){
		char w = guess[i];
		if(!((w >= 65 && w <= 90) || (w >= 97 && w <= 122))){
			return false;
		}
	}
	return true;
}
void userGuess(char guess[]){
	while(1){
		printf("Enter your guess of 5 letters here: \n");
		scanf("%s", guess);
		
		int i = 0;
		while(guess[i] != '\0')
			i++;
		if(i == WORD){
			break;
		}
		else{
			printf("You must enter a word that's 5 letters, try again.\n");
		}
	}
}	
void checkGuess(char guess[], char word[], bool samePlace[], bool rightMarks[]){
	bool used[WORD] = { false };
	for(int i = 0; i < WORD; i++){
		if(guess[i] == word[i]){
		samePlace[i] = true;
		used[i] = true;
	}
	else{
		samePlace[i] = false;
	}
	rightMarks[i] = false;
	}
	for(int i = 0; i < WORD; i++){
		if(guess[i] == word[i]){
			samePlace[i] = true;
			used[i] = true;
		}
	}
	for(int i = 0; i < WORD; i++){
		if(!samePlace[i]){
			for(int b = 0; b < WORD; b++){
				if(!used[b] && guess[i] == word[b]){
					rightMarks[i] = true;
					used[b] = true;
					break;
				}
			}
		}
	}
}
void showcase(char guesses[][WORD + 1], bool same[][WORD],bool rightMarks[][WORD], char word[]){
	for(int g = 0; g < GUESSES; g++){
		if(guesses[g][0] == '\0')
		break;
		
		for(int i = 0; i < WORD; i++){
			char wrd = guesses[g][i];
			if(same[g][i] && wrd >= 'a' && wrd <= 'z'){
				wrd = wrd - 'a' + 'A';
			}
			printf("%c", wrd);
		}
		printf("\n");
		
		for(int i = 0; i < WORD; i++){
			if(rightMarks[g][i]){
				printf("^");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}
