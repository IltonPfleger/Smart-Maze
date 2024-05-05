

MAZE MAZE_CreateMaze(int size)
{
	MAZE maze;
	maze.size = size;
	maze.visited_sum = 0;
	maze.cells = (CELL**)malloc(sizeof(CELL*)*maze.size);
	maze.visited = (int**)malloc(sizeof(int*)*maze.size);
	for(int i = 0; i < maze.size; i++)
	{
		maze.cells[i] = (CELL*)malloc(sizeof(CELL)*maze.size);
		maze.visited[i] = (int*)malloc(sizeof(int)*maze.size);
		for(int j = 0; j < maze.size; j++)
		{
			maze.cells[i][j] = (CELL){i, j, j*CELL_W, i*CELL_H, 0, 0, 0, 0, NULL, NULL, 1, 1, 1, 1};
			maze.visited[i][j] = 0;
		};
	};
	return maze;
};

void MAZE_UpdateMazeBasedOnStep(CELL * previous, CELL * current)
{
	int iStep = current->i - previous->i;
	int jStep = current->j - previous->j;

	if(jStep == 1)
	{
		current->walls[3] = 0;
		previous->walls[1] = 0;

	}
	if(jStep == -1)
	{
		current->walls[1] = 0;
		previous->walls[3] = 0;
	}
	if(iStep == 1)
	{
		current->walls[0] = 0;
		previous->walls[2] = 0;
	}
	if(iStep == -1)
	{
		current->walls[2] = 0;
		previous->walls[0] = 0;
	}
}



CELL * MAZE_GetRandomNeighborn(MAZE *maze, int iC, int jC)
{
	CELL *neighborns[4];
	int dx[4] = {0, 0, 1, -1};
	int dy[4] = {1, -1, 0, 0};
	int valid = 0;

	for(int k = 0; k < 4; k++)
	{
		int i = iC + dx[k];
		int j = jC + dy[k];
		if(i >= 0 && i < maze->size && j >= 0 && j < maze->size && !maze->visited[i][j])
			neighborns[valid++] = &maze->cells[i][j];
	}
	if(valid)
	{
		return neighborns[rand()%valid];
	}
	else
		return NULL;
}

void MAZE_GenerateMaze(MAZE *maze)
{
	CELL *current = &maze->cells[0][0];
	while(maze->visited_sum < (MAZE_SIZE*MAZE_SIZE) - 1)
	{
		maze->visited[current->i][current->j] = 1;
		maze->visited_sum++;
		CELL * choice = MAZE_GetRandomNeighborn(maze, current->i, current->j);

		if(choice == NULL)
		{
			CELL * parent = current;
			while(MAZE_GetRandomNeighborn(maze, parent->i, parent->j) == NULL)
			{
				MAZE_UpdateMazeBasedOnStep(parent, parent->mazeParent);
				parent = parent->mazeParent;
			}
			choice = MAZE_GetRandomNeighborn(maze, parent->i, parent->j);
			MAZE_UpdateMazeBasedOnStep(parent, choice);
		};

		MAZE_UpdateMazeBasedOnStep(current, choice);
		choice->mazeParent = current;
		current = choice;
		int t = usleep(3000);
	}
	maze->visited[current->i][current->j] = 1;
}


void MAZE_ResetMaze(MAZE * maze)
{
	maze->visited_sum = 0;
	for(int i = 0; i < maze->size; i++)
	{
		for(int j = 0; j < maze->size; j++)
		{
			maze->cells[i][j] = (CELL){i, j, j*CELL_W, i*CELL_H, 0, 0, 0, 0, NULL, NULL, 1, 1, 1, 1};
			maze->visited[i][j] = 0;
		};
	};
};




