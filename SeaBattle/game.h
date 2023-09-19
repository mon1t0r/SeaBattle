#pragma once
#include <stdbool.h>

#define FIELD_SIZE 10

typedef struct Cell {
	bool hasShip;
	bool isOpen;
} Cell;

extern Cell playerMatrix[FIELD_SIZE][FIELD_SIZE];
extern Cell computerMatrix[FIELD_SIZE][FIELD_SIZE];

void InitializeGame();