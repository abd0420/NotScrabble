#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

char players[2][50]; //two players with length 50

char takeUserNames() {

    printf("\n\t\t------NotScrabble------\n\n");
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
    for (i = 0; i < strlen(word); i++) {
        word[i] = tolower(word[i]); // All the words in our files are in lowercase, so we do the same here.   
    }
    
    // Checking: if word exists in the pre written file for valid words //
    char initialLetter = word[0];      //We are constructing the name of the file to open through the user's entered word.
    char fileName[20];
    
    //checking that the input only contains letters
    for(i=0;i<strlen(word);i++){
        if(isdigit(word[i]) || !(isalnum(word[i]))){
            return 0;
        }
    }

    sprintf(fileName, "words/%c.txt", initialLetter);

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
        for(i = 0 ; i<7 ; i++){
            if (rack[i] >= 0 && rack[i] < 26){
                LetterCount[rack[i]]++;    //incrementing counts of all letters in rack because all are unused
            }
        }
        (*bagptr) += 7;  //incrementing bag by 7
        return 3; //word not in dictionary
    }
        
    char LetterRack[7]; //an array tht will store letters of rack
    for (i = 0; i < 7; i++) {
        LetterRack[i] = tolower(letters[rack[i]]);
    }

    for (i = 0; i < strlen(word); i++) {
        int found = 0;
        for(j=0; j< 7 ; j++) {  
            if (word[i] == LetterRack[j]) {  // comparing word letter with rack letter
                LetterRack[j] = '0';
                rack[j] = -1; //to show in rack tht a letter is gone
                found = 1;
                break; //stops looping if the letter is found
            }
        }
        if (found == 0) {
            for(j = 0 ; j<7 ; j++){
                if (rack[j] >= 0 && rack[j] < 26){
                    LetterCount[rack[j]]++;    //incrementing counts of all letters in rack because all are unused
                }
            }
            (*bagptr) += 7;  //incrementing bag by 7
            return 2; //word doesnt have same letters as rack
        }
    }

    //if everything is correct, word exists and word has letters as the rack,
    //we have to increment the unused letters ad bag
    for(i=0; i<7 ; i++){
        if(!(rack[i] == -1)){
            LetterCount[rack[i]]++;
            (*bagptr)++;
        }
    }
    return 1;
}

int CalculateScore(char word[7], int LetterScore[26]){
    int index , i, score = 0;
    for(i=0;i<strlen(word);i++){
        index = toupper(word[i]) - 65; //stores value 0-25 in word index according to letter in word[i]
        score += LetterScore[index];
    }
    return score;
}

int Result(int playerPoints[2]) {
    printf("\t\t FINAL RESULT\n");
    printf("\t| P1: %s\tScore: %d |\n", players[0], playerPoints[0]);
    printf("\t| P2: %s\tScore: %d |\n", players[1], playerPoints[1]);

    if(playerPoints[0] > playerPoints[1]) {
        printf("\n\t\tWINNER IS: %s\n", players[0]);
        return 1;
    }
    else if(playerPoints[1] > playerPoints[0]) {
        printf("\n\t\tWINNER IS: %s\n", players[1]);
        return 2;
    }
    else {
        printf("\n\t\tGAME DRAW(\n");
        return 3;
    }
}

void UpdateGameHistoryFile(int playerPoints[2], int result) {

    FILE *fp = fopen("gamehistory.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
    }
    char *gameWinner;  
    if (result == 1) {
        gameWinner = players[0]; 
    }
    else if(result == 2) {
        gameWinner = players[1];
    }
    else {
        gameWinner = "Draw";
    }
    fprintf(fp, "%s,%s,%d,%d,%s\n", players[0], players[1], playerPoints[0], playerPoints[1], gameWinner);

    fclose(fp);
   
}

int main() {
    
    takeUserNames(); // extracted user input process into a dedicated function, achieved a more readable function body.

    char letters[26] =   {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                          'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ; 
    int LetterScore[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; //stored in order of alphabets
    int LetterCount[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};  //stored in order of alphabets
    
    int bag = 100; //stores count of total letters available
    int*bagptr = &bag ; //making a pointer to bag bcz we cant update the bag value inside another functions so we update at its memory
    
    int playerPoints[2] = {0,0} ; //total score of both players
    int penalties[2] = {0,0} ; //stroes total penalties of a player
    int x = 0, score = 0;
    char word[7];

    int i,j; 
    int rack[7];
    int repeat = 1; //if repeat == 0 loop stops game stops 
    srand(time(NULL)); // for rand()

    while(repeat == 1 && penalties[0] != 3 && penalties[1] != 3 && bag > 16){
        for(i=0 ; i<2 ; i++) { 
            printf("\n%s's turn:\n", players[i]);  //e.g. meesam's turn:
            for(j=0 ; j<7; j++) {
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

            x = VerifyWord(letters, word, rack, LetterCount , bagptr);
            switch(x) {
                case 0:
                    printf("Invalid Input !!! You entered a number or symbol\n");
                    penalties[i] += 1;
                    printf("%s gets a penalty !!!\n", players[i]);
                    printf("%s penalties = %d\n", players[i], penalties[i]);
                    break;
                case 1:
                    score = CalculateScore(word,LetterScore);
                    playerPoints[i] += score;  //updates total score of each player
                    printf("Score = %d", score);
                    score = 0;
                    break;
                case 2:
                    printf("%s Doesn't have same letters as given rack!!! \n", word);
                    penalties[i] += 1;
                    printf("%s gets a penalty !!!\n", players[i]);
                    printf("%s penalties = %d\n", players[i], penalties[i]);
                    break;
                case 3:
                    printf("%s Does not exist! \n" , word);
                    penalties[i] += 1;
                    printf("%s gets a penalty !!!\n", players[i]);
                    printf("%s penalties = %d\n", players[i], penalties[i]);
                    break;
            }
        }

        if(penalties[0] != 3 && penalties[1] != 3){ //checking if any of the player has penalties then game has to end without asking
            printf("\nIf you want to END the game press 0 ELSE press 1  : ");
            scanf("%d" , &repeat);
        }
    }
    if(bag < 16) {
        printf("\nInsufficient letters available so...\n");
    }
    else if(penalties[0] == 3 && penalties[1]==3){
        printf("Both players have 3 Penalties so...");
    }
    else{
        if(penalties[0] == 3 ){
            printf("\n%s have 3 Penalties so...\n\n", players[0]);
        } 
        else if(penalties[1] == 3){
            printf("\n%s have 3 Penalties so...\n\n", players[0]);
        }
    }
    printf("\n\t\t-----GAME END-----\n\n");
    
    int result;
    result = Result(playerPoints); //displays names, final scores and winner or tied with a message , and return result (1 = player 1 win , 2 = player 2 win , 3 = tied) 
    UpdateGameHistoryFile(playerPoints, result) ; //this will append the file of gamehistory.txt with names,scores, and winner
    return 0;
}