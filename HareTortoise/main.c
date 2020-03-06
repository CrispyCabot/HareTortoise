#include <stdio.h> //for printf
#include <time.h> //To seed random numbers
#include <stdlib.h> //For random numbers

#define MAX 60;

//Prototypes
char* moveTortoise(char*, char*, int*);
char* moveHare(char*, char*, int*, int*);
void print(char*, char*, char*, int, int*, int*);

void main() {
	char path[] = " R  R  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R "; //The path that the hare/tortoise will navigate
	char* hare;
	char* tortoise; //Hare & Tortoise pointers that will point to something inside of path
	int turnNum = 1; //Keeps track of the turn we are on
	int collision = 0, nap = 0; //Booleans to track if there was a collision or if the hare is napping
	
	srand(time(NULL)); //Seed random # generator

	hare = path;
	tortoise = path;

	//while hare and tortoise are still in path,
	//each animal takes its turn then a summary is outputted
	print(path, hare, tortoise, turnNum, &collision, &nap); //Prints out initial set up before everything runs
	turnNum++;
	while (hare < path + 60 && tortoise < path + 60) {
		tortoise = moveTortoise(hare, tortoise, &collision);
		hare = moveHare(hare, tortoise, &collision, &nap);
		print(path, hare, tortoise, turnNum, &collision, &nap);
		turnNum++;
	}
	if (hare > tortoise)
		printf("Hare wins!");
	else
		printf("Tortoise wins!");
}

char* moveTortoise(char* hare, char* tortoise, int* collision) {
	tortoise += rand() % 3 + 1;
	if (tortoise == hare) {
		*collision = 1;
		tortoise--;
	}
	return tortoise;
}

char* moveHare(char* hare, char* tortoise, int* collision, int *nap) {
	if (rand() % 3 + 1 == 1) {
		*nap = 1;
	}
	else if (*hare == 'C') {
		*hare = ' ';
	}
	else {
		hare += rand() % 8 + 1;
		if (hare == tortoise) {
			hare--;
			*collision = 1;
		}
		while (*hare == 'S' || *hare == 'R') {
			hare--;
		}
		if (hare == tortoise) {
			hare--;
			*collision = 1;
		}
	}
	return hare;
}

void print(char* path, char* hare, char* tortoise, int turnNum, int* collision, int* nap) {
	char* pathLooper;
	printf("Turn: %3d: ", turnNum);
	pathLooper = path;
	while (*pathLooper != '\0') {
		if (pathLooper == hare == tortoise) { //For when they are on top of each other like beginning
			printf("HT");
			pathLooper += 2;
		}
		else if (pathLooper == hare)
			printf("H");
		else if (pathLooper == tortoise)
			printf("T");
		else
			printf("%c", *pathLooper);
		pathLooper++;
	}
	if (*collision) {
		printf(" -collision- ");
		*collision = 0;
	}
	if (*nap) {
		printf(" -hare napping- ");
		*nap = 0;
	}
	printf("\n");
}