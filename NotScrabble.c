#include <stdio.h>

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
    
    int PlayerPoints[2] = {0,0} ; //total score of both players
    int x=0 , score=0;
    char word[8];
    int i;
    int repeat = 1; //if repeat == 0 loop stops game stops 
    
    while(repeat){
        for(i=0 ; i<2 ; i++){ 
            printf("\n%s's turn:\n", players[i]);  //e.g. meesam's turn:
            // 7randomletters(letters,LetterScore,LetterCount);   this will print 7 random letters using rand() function for a player
            printf("Enter Your Word : ");
            scanf("%s", word);
            // x = VerifyWord(word);   this will take the word as parameter and return 1 if the word is  else 0
            if(x){
                //score = CalculateScore(word) ;
                //printf("%s score is %d", players[i], score) ;
                //PlayerPoints[i] += score;  //updates total score of each player
                //score = 0;
                //x=0;
            }
            else{
                printf("%s does not exist !!! /n" , word);
            }
        }
        printf("\nIF you want to END the game press 0 ELSE press 1  : ");
        scanf("%d" , &repeat);
    }

    //Result(players , PlayerPoints); //displays final scores and winner or tied with a message 
    //UpdateGameHistoryFile() ; //this will append the file of player data with names,scores, and winner
    return 0;
}