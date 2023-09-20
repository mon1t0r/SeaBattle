#include <stdlib.h>
#include "game.h"
#include "ship_gen.h"

#define SHIP_MAX_SIZE 4

int InitPlaceVariant(int, ShipPlaceVar*);
void ClearAllIntrWithVariant(ShipPlaceVarSet*, ShipPlaceVar*);

void InitializeMatrix(Cell matrix[FIELD_SIZE][FIELD_SIZE], ShipPlaceVarSet* varSet)
{
	for (int i = 0; i < SHIP_MAX_SIZE; ++i)
	{
		for (int j = SHIP_MAX_SIZE - i; j > 0; --j)
		{
			if (varSet[i].count <= 0)
				continue;
			int varIndex = rand() % varSet[i].count;
			ShipPlaceVar var = varSet[i].variants[varIndex];
			ClearAllIntrWithVariant(varSet, &var);

			for (int j = var.x1; j <= var.x2; ++j)
				for (int k = var.y1; k <= var.y2; ++k)
					matrix[j][k].hasShip = true;
		}
	}
}

ShipPlaceVarSet* CreatePlaceVariantSet()
{
	int maxPlaceVariants = FIELD_SIZE * FIELD_SIZE * 4;
	ShipPlaceVarSet* varSet = (ShipPlaceVarSet*)malloc(SHIP_MAX_SIZE * sizeof(ShipPlaceVarSet));
	for (int i = 0; i < SHIP_MAX_SIZE; ++i)
	{
		varSet[i].variants = (ShipPlaceVar*)malloc(maxPlaceVariants * sizeof(ShipPlaceVar));
		varSet[i].count = maxPlaceVariants;
	}
	return varSet;
}

void InitPlaceVariantSet(ShipPlaceVarSet* varSet)
{
	for (int i = 0; i < SHIP_MAX_SIZE; ++i)
	{
		int count = InitPlaceVariant(i, varSet[i].variants);
		varSet[i].count = count;
	}
}

void FreePlaceVariantSet(ShipPlaceVarSet* varSet)
{
	for (int i = 0; i < SHIP_MAX_SIZE; ++i)
		free(varSet[i].variants);
	free(varSet);
}

bool CheckPlaceVariantCorrect(ShipPlaceVar* var)
{
	return var->x1 >= 0 && var->x2 < FIELD_SIZE &&
		var->y1 >= 0 && var->y2 < FIELD_SIZE;
}

ShipPlaceVar* CreateShipPlaceVar(int startX, int startY, int shipSize, int direction)
{
	ShipPlaceVar* var = malloc(sizeof(ShipPlaceVar));

	var->x1 = startX;
	var->y1 = startY;

	switch (direction)
	{
	default:
	case 0:
		var->x2 = startX + shipSize;
		var->y2 = startY;
		break;
	case 1:
		var->x2 = startX - shipSize;
		var->y2 = startY;
		break;
	case 2:
		var->x2 = startX;
		var->y2 = startY + shipSize;
		break;
	case 3:
		var->x2 = startX;
		var->y2 = startY - shipSize;
		break;
	}

	if (var->x1 > var->x2)
	{
		var->x1 += var->x2;
		var->x2 = var->x1 - var->x2;
		var->x1 = var->x1 - var->x2;
	}

	if (var->y1 > var->y2)
	{
		var->y1 += var->y2;
		var->y2 = var->y1 - var->y2;
		var->y1 = var->y1 - var->y2;
	}

	return var;
}

int InitPlaceVariant(int shipSize, ShipPlaceVar* arr)
{
	int varsCount = 0;
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			for (int k = 0; k < 4; ++k)
			{
				ShipPlaceVar* var = CreateShipPlaceVar(i, j, shipSize, k);
				if (CheckPlaceVariantCorrect(var))
					arr[varsCount++] = *var;
				free(var);
			}
	return varsCount;
}

bool CheckPlaceVariantsIntersect(ShipPlaceVar* var1, ShipPlaceVar* var2)
{
	if (var1 == var2)
		return true;

	return var1->x1 - 1 < var2->x2 + 1 && var1->x2 + 1 > var2->x1 - 1 &&
		var1->y2 + 1 > var2->y1 - 1 && var1->y1 - 1 < var2->y2 + 1;
}

void ClearAllIntrWithVariant(ShipPlaceVarSet* varSetArr, ShipPlaceVar* var)
{
	ShipPlaceVar curVar = *var;
	for (int i = 0; i < SHIP_MAX_SIZE; ++i)
	{
		ShipPlaceVar* varArr = varSetArr[i].variants;
		for (int j = 0; j < varSetArr[i].count; ++j)
		{
			if (CheckPlaceVariantsIntersect(&curVar, &varArr[j]))
			{
				memmove(&varArr[j], &varArr[j + 1], (varSetArr[i].count - j - 1) * sizeof(ShipPlaceVar));
				varSetArr[i].count--;
				j--;
			}
		}
	}
}