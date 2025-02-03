#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int randomNumber();
char* randomWord();
char* hangman(int level);

int searchLetter(char* word, char letter);
char completeWord(char* word, char* chosenLetters);
int gameOver(int hangmanState, char* word, char* chosenLetters);


int main() {
    printf("Random number: %d\n",randomNumber());
    printf("%s\n", randomWord());

    char* word = randomWord();

    searchLetter(word, 'a');

    //printf("Longitud de \"%s\": %lu\n", word, strlen(word));

    /*
    for(int i = 0; i < 7; i++){
        printf("%s\n", hangman(i));
    }

    return 0;
    */
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


int searchLetter(char* word, char letter){
    for(int x = 0; x < strlen(word); x++){
        if(letter == word[x]){
            printf("There is a %c in %s\n", letter, word);
        }else{
            printf("There is NO a %c in %s\n", letter, word);
        }
    }
};



/*
|‾‾‾| 
|1  |
|___|
*/