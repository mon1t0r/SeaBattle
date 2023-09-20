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