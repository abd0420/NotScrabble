#include <stdio.h>
#include <stdlib.h> //for rand()

int RandomLetter(int LetterCount[26], int *bagptr){
    int r;
    do{
        r = rand() % 26;
    }while(LetterCount[r] == 0);

    LetterCount[r] -= 1;
    (*bagptr)--;
    return r;
}

int VerifyWord(char word[7], char rack[7], int LetterCount[26], int *bagptr){
    //1. convert rack and word in lowercase first bcz words.txt is in lowercase
    //2. checks word has same letters as rack letters
    //     if any letter doesnt match, do LetterCount[i]++ for each Letter and return 2;
    //3. then check word exists in the word folder
    //     if it doesnt exist, return 0
    //4. do   LetterCount[i]++ , *bagptr++ , for each unused letter and return 1 in last. 
}

int main(){
    char players[2][50]; //two players with length 50

    printf("\n\n------NotScrabble------\n");
    printf("Enter player 1 name :");
    scanf("%s" , players[0]);
    printf("Enter player 2 name :");
    scanf("%s", players[1]);

    const char letters[26] =   {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                                'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'} ; 
    const int LetterScore[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; //stored in order of alphabets
    int LetterCount[26]    =    {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};  //stored in order of alphabets
    
    int bag = 100; //stores count of total letters available
    int*bagptr = &bag ; //making a pointer to bag bcz we cant update the bag value inside another functions so we update at its memory
    
    int PlayerPoints[2] = {0,0} ; //total score of both players
    int x=0 , score=0;
    char word[7];

    int i,j, rack[7];
    int repeat = 1; //if repeat == 0 loop stops game stops 
    
    while(repeat){
        for(i=0 ; i<2 ; i++){ 
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
            // x = VerifyWord(word, rack, LetterCount , bagptr);   this will take the word as parameter and return 1 if the word is correct else 0
            if(x==1){
                //score = CalculateScore(word) ;
                //printf("%s score is %d", players[i], score) ;
                //PlayerPoints[i] += score;  //updates total score of each player
                //score = 0;
                //x=0;
            }
            else if(x == 2){ 
                printf("%s doesnt has same letters as given rack !!! \n", word);
            }
            else{
                printf("%s does not exist !!! \n" , word);
            }
        }
        if(bag < 16){
            printf("Insufficient letters available.\n");
            break;
        }
        printf("\nIF you want to END the game press 0 ELSE press 1  : ");
        scanf("%d" , &repeat);
        printf("%d", bag);
    }
    printf("-----GAME END-----");
    //Result(players , PlayerPoints); //displays final scores and winner or tied with a message 
    //UpdateGameHistoryFile() ; //this will append the file of player data with names,scores, and winner
    return 0;
}