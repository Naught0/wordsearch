#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define STRLEN 30 

typedef struct word{
	char word[STRLEN];
}word;

void welcome();
int getBoardSize();
int getNumWords();
void genArray(int x, char[x][x]);
void getWords(int, word[]);
int randNum(int);
void revStr(char[], char[]);
void blankStr(char[]);
void displayBoard(int s, char wordSearch[s][s]);

// Checks to see if you can lay the word horizontally
int checkHoriz(int s, char wordSearch[s][s], char[], int *x, int *y);
void placeHoriz(int s, char wordSearch[s][s], char word[], int x, int y);
int checkVert(int s, char wordSearch[s][s], char[], int *x, int *y);
void placeVert(int s, char wordSearch[s][s], char word[], int x, int y);

int main(){
    // seed random #
    srand(time(NULL));

	// delcarations
    int boardSize, numWords;
    char tempStr[STRLEN];
    blankStr(tempStr);

    // welcome dialogue
    welcome();

    // get & store info
    boardSize = getBoardSize();
    numWords = getNumWords();
    word wordBank[numWords];

    // store words
    getWords(numWords, wordBank);

    // Create the board
    char wordSearch[boardSize][boardSize];
    
    // populate array
    genArray(boardSize, wordSearch);

    // place words in array
    for(int i = 0; i < numWords; i++){
        int initx = 0, inity = 0;
        // Decide horizontal, vertical, backwards
        int decide = randNum(2);
            if(decide == 0 || decide == 2){
                while(checkHoriz(boardSize, wordSearch, wordBank[i].word, &initx, &inity)){
                    placeHoriz(boardSize, wordSearch, wordBank[i].word, initx, inity);
                    printf("Placed!\n");
                    break;
                }
            }
            if(decide == 1){
                while(checkVert(boardSize, wordSearch, wordBank[i].word, &initx, &inity)){
                    placeVert(boardSize, wordSearch, wordBank[i].word, initx, inity);
                    printf("Placed!\n");
                    break;
                }
            }
            // Reverse
                /*
        		revStr(wordBank[i].word, tempStr);
                blankStr(tempStr);*/
    }
    displayBoard(boardSize, wordSearch);
    	// transform if needed
    	// place

}

void placeHoriz(int s, char wordSearch[s][s], char word[], int x, int y){
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        wordSearch[x][y + i] = word[i];
    }
}

int checkHoriz(int s, char wordSearch[s][s], char word[], int *x, int *y){
    *x = randNum(s);
    *y = randNum(s);
    int len = strlen(word);
    for(int i = 0; i < len; i++){ 
        if(wordSearch[*x][*y + i] != '.'){
            return 0;
        }
    }
    return 1;
}

void placeVert(int s, char wordSearch[s][s], char word[], int x, int y){    
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        wordSearch[x + i][y] = word[i];
    }
}

int checkVert(int s, char wordSearch[s][s], char word[], int *x, int *y){
    *x = randNum(s);
    *y = randNum(s);
    int len = strlen(word);
    for(int i = 0; i < len; i++){ 
        if(wordSearch[*x + i][*y] != '.'){
            return 0;
        }
    }
    return 1;
}


void welcome(){
    printf("This program will generate a word search based on user input.\n\n");
}

int getBoardSize(){
	int boardSize;
    printf("How large would you like your board to be?\n(i.e. X*X)\n> ");
    scanf("%d", &boardSize);
    return boardSize; 
}

int getNumWords(){
	int numWords;
    printf("How many words will you enter?\n> ");
    scanf("%d", &numWords);
    return numWords;
}

void getWords(int numWords, word wordBank[]){
	printf("You will be asked to enter %d words\n", numWords);
	for(int i = 0; i < numWords; i++){
		printf("%d: ", i + 1);
		scanf("%s", wordBank[i].word);
		printf("\n");
	}
	printf("Thanks.\n");
}

// Generates a blank 2d array that will create a grid
void genArray(int aSize, char arr[aSize][aSize]){
	for(int i = 0; i < aSize; i++){
		for(int j = 0; j < aSize; j++){
			arr[i][j] = '.';
		}
	}
}

// return a random number between 0 and limit inclusive.
int randNum(int limit){
    int divisor = RAND_MAX / (limit + 1);
    int retval;

    do{ 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

void revStr(char orig[], char new[]){
    int len = strlen(orig);
    for(int i = len; i >= 0; i--){
        new[len - i - 1] = orig[i];
    }
}

void blankStr(char str[]){
    for(int i = 0; i < STRLEN; i++){
        str[i] = '\0';
    }
}

void displayBoard(int s, char wordSearch[s][s]){
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            printf("%c ", wordSearch[i][j]);
        }
        printf("\n");
    } 
}