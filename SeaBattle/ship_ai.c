#include "utils.h"
#include "ship_ai.h"
#include "game.h"

bool OpenNearbyCellsAI(Cell[FIELD_SIZE][FIELD_SIZE], int, int, AIType, bool);

void PerformComputerMove(Cell matrix[FIELD_SIZE][FIELD_SIZE], AIType type)
{
	if (type == Easy)
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
	else
	{
		for (int i = 0; i < FIELD_SIZE; ++i)
			for (int j = 0; j < FIELD_SIZE; ++j)
				if (OpenNearbyCellsAI(matrix, i, j, type, false))
					return;

		for (int i = 0; i < FIELD_SIZE; ++i)
			for (int j = 0; j < FIELD_SIZE; ++j)
				if (OpenNearbyCellsAI(matrix, i, j, type, true))
					return;

		PerformComputerMove(matrix, Easy);
	}
}

bool OpenNearbyCellsAI(Cell matrix[FIELD_SIZE][FIELD_SIZE], int xCell, int yCell, AIType type, bool openLoners)
{
	Cell* curCell = &matrix[xCell][yCell];
	if (!curCell->isOpen || !curCell->hasShip)
		return false;

	for (int i = 0; i < 4; ++i)
	{
		int x, y;
		MoveByDir(i, xCell, yCell, &x, &y);

		if (!CheckCellExists(x, y))
			continue;

		Cell* cell = &matrix[x][y];

		if (!cell->isOpen && (type != Hard || cell->hasShip))
		{
			if (!openLoners)
			{
				int x1, y1;
				MoveByDir(GetOppDir(i), xCell, yCell, &x1, &y1);
				if (!CheckCellExists(x1, y1))
					continue;

				cell = &matrix[x1][y1];

				if (!cell->isOpen || !cell->hasShip)
					continue;
			}

			OpenCell(matrix, x, y);
			return true;
		}
	}

	return false;
}