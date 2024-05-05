#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720
#define MAZE_SIZE 40
#define CELL_W SCREEN_WIDTH/MAZE_SIZE
#define CELL_H SCREEN_HEIGHT/MAZE_SIZE
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "types.h"
#include "maze.c"
#include "astar.c"




int THREAD(void* maze_ptr)
{
	MAZE *maze = maze_ptr;
	while(1)
	{
		MAZE_GenerateMaze(maze);
		ASTAR_FindPath(maze->cells, 0, 0, MAZE_SIZE - 1, MAZE_SIZE - 1);
		sleep(2);
		MAZE_ResetMaze(maze);
	}
};

int main(){
	srand(time(NULL));
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	MAZE maze = MAZE_CreateMaze(MAZE_SIZE);

	SDL_Thread * maze_thread = SDL_CreateThread(THREAD, "MAZE", &maze);


	while(1){
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		int dX[4] = {0, CELL_W, CELL_W, 0};
		int dY[4] = {0 ,0, CELL_H, CELL_H};
		int dW[4] = {CELL_W, CELL_W, 0, 0};
		int dH[4] = {0, CELL_H, CELL_H, 0};

		for(int i = 0; i < MAZE_SIZE; i++)
		{
			for(int j = 0; j < MAZE_SIZE; j++)
			{
				SDL_SetRenderDrawColor(renderer, 20, 30, 200, 255);
				for(int k = 0; k < 4; k++)
					if(maze.cells[i][j].walls[k])
							SDL_RenderDrawLine(renderer, maze.cells[i][j].x + dX[k], maze.cells[i][j].y + dY[k], maze.cells[i][j].x + dW[k], maze.cells[i][j].y + dH[k]);

				if(!maze.visited[i][j])
					SDL_RenderFillRect(renderer, &(SDL_Rect){maze.cells[i][j].x, maze.cells[i][j].y, CELL_W, CELL_H});

				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
				if(maze.cells[i][j].onOpen)
					SDL_RenderFillRect(renderer, &(SDL_Rect){maze.cells[i][j].x, maze.cells[i][j].y, CELL_W, CELL_H});
			};
		};


		CELL * current = &maze.cells[MAZE_SIZE - 1][MAZE_SIZE -1];
		SDL_SetRenderDrawColor(renderer, 50, 230, 90, 255);
		while(current->pathParent != NULL)
		{
			for(int l = 0; l < 3; l++)
				SDL_RenderDrawLine(renderer, current->j * CELL_W + CELL_W/2 + l, current->i * CELL_H + CELL_H/2 + l, current->pathParent->j * CELL_W + CELL_W/2 + l,current->pathParent->i * CELL_H + CELL_H/2 + l);
			current = current->pathParent;
		}


		SDL_Event event;
		if(SDL_PollEvent(&event))
			if(event.type == SDL_QUIT)
				break;


		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}

	SDL_Quit();
	return 0;
}
