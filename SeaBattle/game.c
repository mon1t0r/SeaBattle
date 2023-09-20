#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "game.h"
#include "ship_gen.h"
#include "ship_ai.h"

Cell playerMatrix[FIELD_SIZE][FIELD_SIZE];
Cell computerMatrix[FIELD_SIZE][FIELD_SIZE];

void InitializeGame()
{
	srand(time());

	AllocConsole();
	FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;
	freopen_s(&fpstdin, "CONIN$", "r", stdin);
	freopen_s(&fpstdout, "CONOUT$", "w", stdout);
	freopen_s(&fpstderr, "CONOUT$", "w", stderr);

	ShipPlaceVarSet* playerVarSet = CreatePlaceVariantSet();
	ShipPlaceVarSet* computerVarSet = CreatePlaceVariantSet();

	InitPlaceVariantSet(playerVarSet);
	InitPlaceVariantSet(computerVarSet);

	InitializeMatrix(playerMatrix, playerVarSet);
	InitializeMatrix(computerMatrix, computerVarSet);

	FreePlaceVariantSet(playerVarSet);
	FreePlaceVariantSet(computerVarSet);
}

bool CheckCellExists(int xCell, int yCell)
{
	return xCell >= 0 && xCell < FIELD_SIZE &&
		yCell >= 0 && yCell < FIELD_SIZE;
}

bool CheckCellNearbyShips(Cell matrix[FIELD_SIZE][FIELD_SIZE], int xCell, int yCell, int prevXCell, int prevYCell, bool shouldOpen)
{
	bool hasShips = true;

	for (int i = 0; i < 4; ++i)
	{
		int x, y;
		MoveByDir(i, xCell, yCell, &x, &y);

		if (!CheckCellExists(x, y) || (x == prevXCell && y == prevYCell))
			continue;

		Cell* cell = &matrix[x][y];

		if (cell->hasShip)
		{
			if (!cell->isOpen)
				return false;
			hasShips = hasShips && CheckCellNearbyShips(matrix, x, y, xCell, yCell, shouldOpen);
		}


		if (shouldOpen)
			for (int x1 = xCell - 1; x1 <= xCell + 1; ++x1)
				for (int y1 = yCell - 1; y1 <= yCell + 1; ++y1)
				{
					if (!CheckCellExists(x1, y1))
						continue;

					Cell* cell1 = &matrix[x1][y1];

					if (!cell1->isOpen && !cell1->hasShip)
						cell1->isOpen = true;
				}
	}

	return hasShips;
}

bool OpenCell(Cell matrix[FIELD_SIZE][FIELD_SIZE], int xCell, int yCell)
{
	Cell* cell = &matrix[xCell][yCell];

	if (cell->isOpen)
		return false;

	cell->isOpen = true;

	if (cell->hasShip && CheckCellNearbyShips(matrix, xCell, yCell, -1, -1, false))
		CheckCellNearbyShips(matrix, xCell, yCell, -1, -1, true);

	return true;
}

void HandleMouseClick(int mouseX, int mouseY, int viewport[4])
{
	float x = ((mouseX - viewport[0]) / (float)viewport[2] - 0.5f) * 2.0f;
	float y = 1.0f - ((mouseY - viewport[1]) / (float)viewport[3] - 0.25f) * 2.0f;

	if (x < 0.0f || y < 0.0f)
		return;

	int xCell = (int)(FIELD_SIZE * x);
	int yCell = (int)(FIELD_SIZE * y);

	if (xCell >= FIELD_SIZE || yCell >= FIELD_SIZE)
		return;

	if(OpenCell(computerMatrix, xCell, yCell))
		PerformComputerMove(playerMatrix, Medium);
}