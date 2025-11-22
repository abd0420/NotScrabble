#include <stdio.h>
#include <stdlib.h> //for rand()
#include <ctype.h>
#include <string.h>

char players[2][50]; //two players with length 50

char takeUserNames() {

    printf("\n\n\t\t------NotScrabble------\n");
    printf("Enter player 1 name : ");
    scanf("%s" , players[0]);
    printf("Enter player 2 name : ");
    scanf("%s", players[1]);

}

int RandomLetter(int LetterCount[26], int *bagptr){
    int r;
    do {
        r = rand() % 26;
    } 
    while(LetterCount[r] == 0);

    LetterCount[r] -= 1;
    (*bagptr)--;
    return r;
}

int VerifyWord(char letters[26], char word[7], int rack[7], int LetterCount[26], int *bagptr) {
    
    int i, j;
    for (i = 0; i < 7; i++) {
        word[i] = tolower(word[i]); // All the words in our files are in lowercase, so we do the same here.   
    }
    
    // Checking: if word exists in the pre written file for valid words //
    char initialLetter = word[0];      //We are constructing the name of the file to open through the user's entered word.
    char fileName[5];
    sprintf(fileName, "%c.txt", initialLetter);

    FILE *fp = fopen(fileName, "r");
    char line[50];

    if (fp == NULL) {  //necessary error handling.
        printf("Could not open file for reading.\n");
        return 0;
    }
    int wordFound = 0;
    while(fgets(line, 50, fp) != NULL) {

        // to check for newline and replace it with string terminator :P
        size_t lenOfLineRead = strlen(line);
        if (lenOfLineRead > 0 && line[lenOfLineRead - 1] == '\n') {
            line[lenOfLineRead - 1] = '\0';
        }
        if (strcmp(word, line) == 0) {
            wordFound = 1;
            break;
        }
    }
    fclose(fp);
    if (wordFound == 0) {
        return 3;
    }
        
    char tempRack[7];
    for (i = 0; i < 7; i++) {
        tempRack[i] = letters[rack[i]];
    }
    for (i = 0; i < strlen(word); i++) {

       // int letterUsed = 0;
        for (j = 0; j < 7; j++) {

            if (word[i] == tempRack[j]) {  // comparing word with rack
                tempRack[j] = '0';
                //letterUsed = 1;
                break;
            }  
        } 
       /* if (letterUsed == 0) {

            (*bagptr)++;
            (LetterCount[i]++);
            return 2;
        } */
    }
    return 1;
}

int main() {
    
    takeUserNames(); // extracted user input process into a dedicated function, achieved a more readable main() function body.

    char letters[26] =   {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                                'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ; 
    const int LetterScore[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; //stored in order of alphabets
    int LetterCount[26]    =    {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};  //stored in order of alphabets
    
    int bag = 100; //stores count of total letters available
    int*bagptr = &bag ; //making a pointer to bag bcz we cant update the bag value inside another functions so we update at its memory
    
    int PlayerPoints[2] = {0,0} ; //total score of both players
    int x = 0, score = 0;
    char word[7];

    int i,j; 
    int rack[7];
    int repeat = 1; //if repeat == 0 loop stops game stops 
    
    while(repeat == 1){
        for(i=0 ; i<2 ; i++) { 
            printf("\n%s's turn:\n", players[i]);  //e.g. meesam's turn:
            for(j=0 ; j<7; j++){
                rack[j] = RandomLetter(LetterCount, bagptr);
            }
            
            //displaying rack letters
            printf("RACK   : ");
            for(j=0;j<7;j++){
                printf("%c ", letters[rack[j]]);
            }
            printf("\n");

            //displaying letter points
            printf("POINTS : ");
            for(j=0;j<7;j++){
                printf("%d ", LetterScore[rack[j]]);
            }
            printf("\n");

            printf("Enter Your Word : ");
            scanf("%s", word);

            x = VerifyWord(letters, word, rack, LetterCount , bagptr);   // this will take the word as parameter and return 1 if the word is correct else 0
            
            printf("\n%d\n", x); //testing
            
            if(x == 1) {

                printf("WORD MATCHED!!!!"); // AsadADDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   TESTING

                //score = CalculateScore(word) ;
                //printf("%s score is %d", players[i], score) ;
                //PlayerPoints[i] += score;  //updates total score of each player
                //score = 0;
                //x=0;
            }
            else if(x == 2) { 
                printf("%s Doesn't have same letters as given rack!!! \n", word);
            }
            else if (x == 3) {
                printf("%s Does not exist! \n" , word);
            }
        }
        if(bag < 16) {
            printf("Insufficient letters available.\n");
            break;
        }
        printf("\nIF you want to END the game press 0 ELSE press 1  : ");
        scanf("%d" , &repeat);

    }
    printf("\n\t\t-----GAME END-----");
    //Result(players , PlayerPoints); //displays final scores and winner or tied with a message 
    //UpdateGameHistoryFile() ; //this will append the file of player data with names,scores, and winner
    return 0;
}