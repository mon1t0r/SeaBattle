#include "game.h"

void PerformComputerMove(Cell matrix[FIELD_SIZE][FIELD_SIZE])
{
	int emptyCells[FIELD_SIZE * FIELD_SIZE] = { 0 };
	int emptyCellsCount = 0;

	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			if (!matrix[i][j].isOpen)
				emptyCells[emptyCellsCount++] = (i << 16) | j;

	if (emptyCellsCount)
	{
		int cell = emptyCells[rand() % emptyCellsCount];

		int x = (cell >> 16) & 0xFFFF;
		int y = cell & 0xFFFF;

		OpenCell(matrix, x, y);
	}
}