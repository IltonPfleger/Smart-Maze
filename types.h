typedef struct CELLS {
	int i, j;
	int x, y;
	int f, g;
	int onOpen, onClose;
	struct CELLS * pathParent;
	struct CELLS * mazeParent;
	int walls[4];
}CELL;

typedef struct
{
	int max_size;
	int current_size;
	CELL **data;
} SET;


typedef struct {
	int size;
	int visited_sum;
	int **visited;
	CELL **cells;
}MAZE;



