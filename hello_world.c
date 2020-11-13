#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Feldgröße ist 32
const int GAME_SIZE = 32;
int gameBoard[32][32];

void field_initializer()
{
	// fills fields with random numbers 0 = dead, 1 = alive
	srand(time(0));
	for (int i = 0; i < GAME_SIZE; i++)
	{
		for (int j = 0; j < GAME_SIZE; j++)
		{
			gameBoard[i][j] = rand() % 2;
		}
	}
}

int main()
{
	field_initializer();
	for (int i = 0; i < GAME_SIZE; i++)
	{
		for (int j = 0; j < GAME_SIZE; j++)
		{
			printf("%d ", gameBoard[i][j]);
		}
		printf("\n");
	}
	return 0;
}