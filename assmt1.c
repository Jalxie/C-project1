/*  C programming is fun
	Engineering computation: Assignment 1
	Name: Xiaoqian Xie   StudentID: 709716   Date: 21/9/2015
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_PLAYERS 1000
#define LENGTH_OF_NAME 50
#define FIRST_PLAYER 0

/* Define a string for surnames of players */
typedef char surname[LENGTH_OF_NAME];
/* Define a structure for the data of players */
typedef struct{
	int playerID;
	int nums_of_games;
	int nums_of_minutes;
	int goals;
	int shots;
	int assists;
	int yellowcards;
	int redcards;
	surname sur_name;
} player_data;

int inputdata(player_data *A);
void stage_1(player_data *C,int max_games);
void stage_2(player_data *D,int max_games,int NUMBERS_OF_PLAYERS);
void stage_3(player_data *F,int max_games,int NUMBERS_OF_PLAYERS);
double EffIndex(player_data *E,int k,int max_games);


int 
main(int argc, char *argv[]){
	int MaxGames,NUMBERS_OF_PLAYERS;
	player_data player[MAX_PLAYERS];
	/* Get the date of maxgames */
	scanf("%d",&MaxGames);
	/* Get data of individual players, 
	and count how many players in the test0.txt file */
	NUMBERS_OF_PLAYERS = inputdata(player);
	/* Stage 1 */
	stage_1(player,MaxGames);
	printf("\n");
	/* Stage 2 */
	stage_2(player,MaxGames,NUMBERS_OF_PLAYERS);
	printf("\n");
	/* Stage 3 */
	stage_3(player,MaxGames,NUMBERS_OF_PLAYERS);
	printf("\n");
return (0);
}

/* Functions used in main() */
/* Get players' data and count the numbers of players from test0.txt */
int 
inputdata(player_data A[]){
	int i=0;
	while(scanf("%d %d %d %d %d %d %d %d %s",&A[i].playerID,
		&A[i].nums_of_games,&A[i].nums_of_minutes,&A[i].goals,
		&A[i].shots,&A[i].assists,&A[i].yellowcards,
		&A[i].redcards,A[i].sur_name) != EOF){
		i++;
	}
	return i;
}

/* Stage 1 */
void 
stage_1(player_data C[],int max_games){
	printf("Stage 1\n");
	printf("==========\n");
	/* print out the data of the first player */
	printf("Player %02d scored %2d goals in %4d minutes from %2d games\n",
	C[FIRST_PLAYER].playerID,C[FIRST_PLAYER].goals,
	C[FIRST_PLAYER].nums_of_minutes,C[FIRST_PLAYER].nums_of_games);
	printf("Goals per game: %05.2f\n",(double)(C[FIRST_PLAYER].goals) / 
		(C[FIRST_PLAYER].nums_of_games));
	printf("Shots per goal: %05.2f\n",(double)(C[FIRST_PLAYER].shots) / 
		(C[FIRST_PLAYER].goals));
	printf("EffIndex: %05.2f\n",EffIndex(C,FIRST_PLAYER,max_games));
}

/* Stage 2 */
void 
stage_2(player_data C[],int max_games,int numbers_of_players){
	printf("Stage 2\n");
	printf("==========\n");
	int i,j;
	for(j=0;j<numbers_of_players;j++){
		if(EffIndex(C,j,max_games) >1 && EffIndex(C,j,max_games)< 100){
			printf("Player %02d, effIndex %05.2f |",C[j].playerID,
				EffIndex(C,j,max_games));
			for(i=1;i<EffIndex(C,j,max_games)+1;i++){
				if((i%10) != 0){
				printf("-");
				} else{
					printf("+");
					}
			}
			printf("\n");
		} else {
			printf("ERROR!");
			exit(EXIT_FAILURE);
		}
	}
}

/* Stage 3 */
void 
stage_3(player_data F[],int max_games,int NUMBERS_OF_PLAYERS){
	printf("Stage 3\n");
	printf("==========\n");
	int i;
	/* p is the number of player who has the largest effindex*/
	int p;
	double MaxEffIndex; 
	MaxEffIndex = EffIndex(F,FIRST_PLAYER,max_games);
    /* Select the surname of player with largest effindex */
	for(i=0;i<NUMBERS_OF_PLAYERS;i++){
		if(EffIndex(F,i,max_games) > MaxEffIndex){
			MaxEffIndex = EffIndex(F,i,max_games);
			p = i;
		}
	}
	printf("Total: %02d players\n",NUMBERS_OF_PLAYERS);
	printf("Top player: %s\n",F[p].sur_name);
	printf("Top effIndex: %05.2f",EffIndex(F,p,max_games));
}

/* Function to calculate effIndex of every player */
double 
EffIndex(player_data E[],int k,int max_games){
	double n;
	double effindex;
	n = (double)E[k].goals+(double)E[k].assists*0.5-
		(double)E[k].redcards*0.5-(double)E[k].yellowcards*0.15;
	effindex = 0.5*pow(n,(double)E[k].nums_of_games/max_games);
 return effindex;
}

