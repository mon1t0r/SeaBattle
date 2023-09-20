#pragma once

typedef struct ShipPlaceVar {
	int x1, y1;
	int x2, y2;
} ShipPlaceVar;

typedef struct ShipPlaceVarSet {
	ShipPlaceVar* variants;
	int count;
} ShipPlaceVarSet;

void InitializeMatrix(Cell[FIELD_SIZE][FIELD_SIZE], ShipPlaceVarSet*);
ShipPlaceVarSet* CreatePlaceVariantSet();
void InitPlaceVariantSet(ShipPlaceVarSet*);
void FreePlaceVariantSet(ShipPlaceVarSet*);