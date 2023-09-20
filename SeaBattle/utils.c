
void MoveByDir(int dir, int x, int y, int* newX, int* newY)
{
	switch (dir)
	{
	default:
	case 0:
		*newX = x + 1;
		*newY = y;
		break;
	case 1:
		*newX = x - 1;
		*newY = y;
		break;
	case 2:
		*newX = x;
		*newY = y + 1;
		break;
	case 3:
		*newX = x;
		*newY = y - 1;
		break;
	}
}

int GetOppDir(int dir)
{
	switch (dir)
	{
	default:
	case 0:
		return 1;
	case 1:
		return 0;
	case 2:
		return 3;
	case 3:
		return 2;
	}
}