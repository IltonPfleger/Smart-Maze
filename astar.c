SET SET_CreateSet()
{
	SET set;
	set.current_size = 0;
	set.data = (CELL **)malloc(sizeof(CELL *));
	return set;
};

void SET_Insert(SET *set, CELL *cell)
{
	set->current_size++;
	set->data = (CELL **)realloc(set->data, sizeof(CELL *) * set->current_size);
	set->data[set->current_size - 1] = cell;
};

CELL *SET_Pop(SET *set)
{
	CELL *temp = set->data[set->current_size - 1];
	set->current_size--;
	set->data = (CELL **)realloc(set->data, sizeof(CELL *) * (set->current_size));
	return temp;
};

void SET_Swap(SET * set, int i, int j)
{
	CELL * temp = set->data[i];
	set->data[i] = set->data[j];
	set->data[j] = temp;
}


void SET_Sort(SET * set, int start, int end)
{
	if(start >= end)return;

	int i = start, j = start;

	while(j < end - 1)
	{
		if(set->data[j]->f <= set->data[end - 1]->f)
			j++;
		if(set->data[j]->f > set->data[end - 1]->f)
			SET_Swap(set, i++, j++);
	}
	SET_Swap(set, i, end - 1);
	SET_Sort(set, start, i);
	SET_Sort(set, i + 1, end);
}


void ASTAR_GetCellNeighborns(CELL ** grid, CELL * current, CELL ** neighborns)
{
	int dX[] = {0, 0, 1, -1};
	int dY[] = {1, -1, 0, 0};
	for (int k = 0; k < 4; k++)
	{
		int dx = current->i + dX[k];
		int dy = current->j + dY[k];
		int iStep = dx - current->i;
		int jStep = dy - current->j;

		if (dx >= 0 && dx < MAZE_SIZE && dy >= 0 && dy < MAZE_SIZE)
		{
			if(jStep == 1 && current->walls[1] == 1)
				continue;
			if(jStep == -1 && current->walls[3] == 1)
				continue;
			if(iStep == 1 && current->walls[2] == 1)
				continue;
			if(iStep == -1 && current->walls[0] == 1)
				continue;
			neighborns[k] = &grid[dx][dy];
		}
	}
};

int ASTAR_GetDistance(int i, int j, int k, int l)
{
	return abs(i - k) + abs(j - l);
};

int ASTAR_FindPath(CELL **grid, int startX, int startY, int endX, int endY)
{
	SET open_set = SET_CreateSet();
	SET_Insert(&open_set, &grid[startX][startY]);

	while (open_set.current_size > 0)
	{
		SET_Sort(&open_set, 0, open_set.current_size);
		CELL *current = SET_Pop(&open_set);
		grid[current->i][current->j].onOpen = 0;
		CELL *neighborns[4] = {NULL};
		ASTAR_GetCellNeighborns(grid, current, neighborns);

		if (current->i == endX && current->j == endY)
			break;

		for (int i = 0; i < 4; i++)
		{
			CELL * neighborn = neighborns[i];

			if (neighborn == NULL)
				continue;

			int G = current->g + ASTAR_GetDistance(current->i, current->j, neighborn->i, neighborn->j);

			if (neighborn->onClose)
				continue;
			if (neighborn->onOpen)
			{
				if (G < neighborn->g)
				{
					neighborn->pathParent = current;
					neighborn->g = G;
				}
			}
			else
			{
				neighborn->g = G;
				neighborn->onOpen = 1;
				neighborn->pathParent = current;
				SET_Insert(&open_set, neighborn);
			};
			neighborn->f = neighborn->g + ASTAR_GetDistance(neighborn->i, neighborn->j, endX, endY);
		};
		grid[current->i][current->j].onClose = 1;
		usleep(10000);
	};
	free(open_set.data);
};




