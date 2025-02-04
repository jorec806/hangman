#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* 
    THE HANGMAN
    Game description:
    1. A random word is chosen and store in a variable
    2. Another variable is created to store an array with the same size as the
    random word's array but filled up with "_". The INCOMPLETE WORD. Variable
    for the amount of attemps, and LEVEL of the Hangman
    3. The hangman figure is displayed with the rules of the game
    4. A text input is displayed for the player to choose a letter(from A to Z)
    5. Player inputs a letter
    6. The game evaluates if the input letter is contained in the word and the
    next options can hapen:
        - If the letter is right, the INCOMPLETE WORD will replace any "_" with
        the proper letter. The hangman is not re-rendered
        - If the letter is wrong, A counter will start decreasing with the
        number of attemps remaining (6 attemps max). Message indicating the
        letter is incorrect will be displayed. Hangman is re-rendered.
    7. The game will loop until the player wins or loses. Either way, the
    program will finish
*/


int randomNumber();
char* randomWord();
char* hangman(int level);
int searchLetter(char* word, char letter, int wordLength);
void fillEmptyWord(char* word, char chosenLetter, char* emptyWord, int wordLength);
void wrongAttempt(int *hangmanLevel, int *attemps);
void renderGame(int hangmanLevel, int attemps, char *incompleteWord);
int gameOver(int attemps, char *incompleteWord, char *word);

int main() {
    //Variables
    char *word = NULL;
    char *incompleteWord = NULL;
    char letter;
    int attemps = 6, hangmanLevel = 0;
    int *pAttemps = &attemps, *pHangmanLevel = &hangmanLevel;

    word = randomWord();
    int wordLength = (int) strlen(word);

    //Creating Incomplete word
    incompleteWord = (char *)malloc(wordLength + 1);

    if (incompleteWord == NULL) return 1; // Memory allocation error

    for(int x = 0; x < wordLength; x++){
        incompleteWord[x] = '_';
    }

    incompleteWord[wordLength] = '\0';

    //GAME START
    printf("\nTHE HANGMAN GAME:\n");
    printf("____\n|/   |\n|   (_)\n|   \\|/ \n|    |\n|   / \\\n|\n|______\n \n");
    printf("Choose a letter from A to Z to guess the word, 6 attemps!\n\n");
    printf("%d-letter word: %s\n", wordLength, incompleteWord);

    //GAME LOOP
    while(attemps > 0){
        //Check if input is a letter
        printf("Choose a letter: ");
        scanf(" %c", &letter);
        printf("\n");

        //Check if letter is in Word
        if(searchLetter(word, letter, wordLength)){
            fillEmptyWord(word, letter, incompleteWord, wordLength);
            renderGame(hangmanLevel, attemps, incompleteWord);
        }else{
            wrongAttempt(pHangmanLevel, pAttemps);
            renderGame(hangmanLevel, attemps, incompleteWord);
        }

        //Check if Game over
        if(gameOver(attemps, incompleteWord, word) == 1){
            printf("You WON!");
            break;
        }else if (gameOver(attemps, incompleteWord, word) == 0) {
            printf("You LOST!");
            break;
        }
    }//END GAME LOOP

    free(incompleteWord);
    return 0;
}

int randomNumber(){
    /* Creates a random number between 1 and 10*/
    srand(time(NULL));
    int random = rand() % 10;

    return random;
}

char* randomWord(){
    /*Selects a random word from the list and returns it*/
    static char* listOfWords[] ={
        "champion", 
        "tomorrow", 
        "computer", 
        "bookstore", 
        "wherever", 
        "alligator", 
        "eucalypt", 
        "network", 
        "typhoon", 
        "australia"};

    return listOfWords[randomNumber()];
};

char* hangman(int level){
    static char* hangman[] =    {"____\n|/   |\n|\n|\n|\n|\n|\n|______\n",
                                 "____\n|/   |\n|   (_)\n|\n|\n|\n|\n|______\n",
                                 "____\n|/   |\n|   (_)\n|    |\n|    |\n|\n|\n|______\n",
                                 "____\n|/   |\n|   (_)\n|   \\|\n|    |\n|\n|\n|______\n",
                                 "____\n|/   |\n|   (_)\n|   \\|/\n|    |\n|\n|\n|______\n",
                                 "____\n|/   |\n|   (_)\n|   \\|/ \n|    |\n|   /\n|\n|______\n",
                                 "____\n|/   |\n|   (_)\n|   /|\\ \n|    |\n|   | |\n|\n|______\n"};

    return hangman[level];
}

int searchLetter(char* word, char letter, int wordLength){

    for(int x = 0; x < wordLength; x++){
        if(tolower(letter) == word[x]){
            return 1;
        }
    }

    return 0;
};

void fillEmptyWord(char* word, char chosenLetter, char* emptyWord, int wordLength){
    for(int x = 0; x < wordLength; x++){
        if(tolower(chosenLetter) == word[x]){
            emptyWord[x] = word[x];
        }
    }

}

void wrongAttempt(int *hangmanLevel, int *attemps){
    *hangmanLevel = *hangmanLevel + 1;
    *attemps = *attemps - 1;
}

void renderGame(int hangmanLevel, int attemps, char *incompleteWord){
    printf("%s\n", hangman(hangmanLevel));
    printf("%s\n", incompleteWord);
    printf("Attemps remaining: %d\n", attemps);
}

int gameOver(int attemps, char *incompleteWord, char *word){
    if(!attemps){
        return 0;
    }else if (strcmp(incompleteWord, word) == 0) {
        return 1;
    }

    return -1;
}

/*
|‾‾‾| 
|12 |
|___|
*/