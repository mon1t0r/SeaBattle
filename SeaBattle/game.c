#include <stdlib.h>
#include "game.h"

Cell playerMatrix[FIELD_SIZE][FIELD_SIZE];
Cell computerMatrix[FIELD_SIZE][FIELD_SIZE];

void InitializeMatrix(Cell[FIELD_SIZE][FIELD_SIZE]);

void InitializeGame()
{
	srand(time());
	InitializeMatrix(playerMatrix);
	InitializeMatrix(computerMatrix);
}

void InitializeMatrix(Cell matrix[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			matrix[i][j].isOpen = false;
			matrix[i][j].hasShip = rand() % 2;
		}
}