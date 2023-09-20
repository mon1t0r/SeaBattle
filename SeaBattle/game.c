#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "ship_gen.h"

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

	computerMatrix[xCell][yCell].isOpen = true;
}