#pragma once
#include "game.h"

typedef enum { Easy = 0, Medium = 1, Hard = 2 } AIType;

void PerformComputerMove(Cell[FIELD_SIZE][FIELD_SIZE], AIType);