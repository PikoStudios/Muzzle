#include <Muzzle.h>
#include <stdio.h>
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 800
#define CELL_SIZE 40
#define TINT(r,g,b,a) (mz_tint){r,g,b,a}

#define PALETTE_SIZE 9
#define PALETTE_BACKGROUND 0
#define PALETTE_GRID_LINES 1
#define PALETTE_TETROMINO_I 2
#define PALETTE_TETROMINO_O 3
#define PALETTE_TETROMINO_T 4
#define PALETTE_TETROMINO_L 5
#define PALETTE_TETROMINO_J 6
#define PALETTE_TETROMINO_S 7
#define PALETTE_TETROMINO_Z 8

#define TETROMINO_I_DEFINITION "****"
#define TETROMINO_I_WIDTH 1
#define TETROMINO_I_HEIGHT 4

#define TETROMINO_O_DEFINITION "****"
#define TETROMINO_O_WIDTH 2
#define TETROMINO_O_HEIGHT 2

#define TETROMINO_T_DEFINITION "***.*."
#define TETROMINO_T_WIDTH 3
#define TETROMINO_T_HEIGHT 2

#define TETROMINO_L_DEFINITION "*.*.**"
#define TETROMINO_L_WIDTH 2
#define TETROMINO_L_HEIGHT 3

#define TETROMINO_J_DEFINITION ".*.***"
#define TETROMINO_J_WIDTH 2
#define TETROMINO_J_HEIGHT 3

#define TETROMINO_S_DEFINITION ".****."
#define TETROMINO_S_WIDTH 3
#define TETROMINO_S_HEIGHT 2

#define TETROMINO_Z_DEFINITION "**..**"
#define TETROMINO_Z_WIDTH 3
#define TETROMINO_Z_HEIGHT 2

typedef struct block
{
	mz_vec2_i pos;
	uint32_t palette_index;
	mz_boolean empty;
} block;

typedef enum
{
	TETROMINO_I = 0,
	TETROMINO_O = 1,
	TETROMINO_T = 2,
	TETROMINO_L = 3,
	TETROMINO_J = 4,
	TETROMINO_S = 5,
	TETROMINO_Z = 6,
} tetromino_type;

typedef struct tetromino
{
	mz_vec2_i top_left;
	block** blocks;
	tetromino_type type;
} tetromino;

typedef struct grid
{
	mz_tint* palette;
	block* blocks;
	uint32_t width;
	uint32_t height;
} grid;

grid init_grid(mz_tint *palette)
{
	grid g = (grid){0};
	g.width = SCREEN_WIDTH / CELL_SIZE;
	g.height = SCREEN_HEIGHT / CELL_SIZE;
	g.blocks = MZ_CALLOC(g.width * g.height, sizeof(block));
	g.palette = palette;

	if (g.blocks == NULL)
	{
		printf("Failed to allocate memory for cells\n");
		exit(-1);
	}

	for (int i = 0; i < g.width * g.height; i++)
	{
		g.blocks[i].pos = (mz_vec2_i){i % g.width, i / g.width};
		g.blocks[i].palette_index = PALETTE_BACKGROUND;
		g.blocks[i].empty = MUZZLE_TRUE;
	}

	return g;
}

void free_grid(const grid* g)
{
	MZ_FREE(g->blocks);
}

block** allocate_block_space(const grid *g, const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
{
	uint32_t block_index = y * g->width + x;
	block** blocks = MZ_CALLOC(width * height, sizeof(block*));

	if (blocks == NULL)
	{
		printf("Failed to allocate memory for block space\n");
		exit(-1);
	}

	for (uint32_t i = block_index; i < block_index + (width * height); i++)
	{
		blocks[i] = &g->blocks[i];
	}

	return blocks;
}

tetromino init_tetromino(const grid *g, tetromino_type type, uint32_t x)
{
	tetromino t = (tetromino){0};
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t palette_index = 0;
	char* definition = "";

	switch (type)
	{
		case TETROMINO_I:
			width = TETROMINO_I_WIDTH;
			height = TETROMINO_I_HEIGHT;
			definition = TETROMINO_I_DEFINITION;
			palette_index = PALETTE_TETROMINO_I;
			break;

		case TETROMINO_O:
			width = TETROMINO_O_WIDTH;
			height = TETROMINO_O_HEIGHT;
			definition = TETROMINO_O_DEFINITION;
			palette_index = PALETTE_TETROMINO_O;
			break;

		case TETROMINO_T:
			width = TETROMINO_T_WIDTH;
			height = TETROMINO_T_HEIGHT;
			definition = TETROMINO_T_DEFINITION;
			palette_index = PALETTE_TETROMINO_T;
			break;

		case TETROMINO_L:
			width = TETROMINO_L_WIDTH;
			height = TETROMINO_L_HEIGHT;
			definition = TETROMINO_L_DEFINITION;
			palette_index = PALETTE_TETROMINO_L;
			break;

		case TETROMINO_J:
			width = TETROMINO_J_WIDTH;
			height = TETROMINO_J_HEIGHT;
			definition = TETROMINO_J_DEFINITION;
			palette_index = PALETTE_TETROMINO_J;
			break;

		case TETROMINO_S:
			width = TETROMINO_S_WIDTH;
			height = TETROMINO_S_HEIGHT;
			definition = TETROMINO_S_DEFINITION;
			palette_index = PALETTE_TETROMINO_S;
			break;

		case TETROMINO_Z:
			width = TETROMINO_Z_WIDTH;
			height = TETROMINO_Z_HEIGHT;
			definition = TETROMINO_Z_DEFINITION;
			palette_index = PALETTE_TETROMINO_Z;
			break;
	}

	t.blocks = allocate_block_space(g, x, 0, width, height);

	for (int i = 0; definition[i] != '\0'; i++)
	{
		switch (definition[i])
		{
			case '.':
				t.blocks[i]->empty = MUZZLE_TRUE;
				t.blocks[i]->palette_index = PALETTE_BACKGROUND;
				break;

			case '*':
				t.blocks[i]->empty = MUZZLE_FALSE;
				t.blocks[i]->palette_index = palette_index;
				break;

			default:
				break;
		}
	}

	return t;
}

void free_tetromino(tetromino* t)
{
	MZ_FREE(t->blocks);
}

void draw_block(mz_applet* applet, const grid* g, const block* b)
{
	mz_draw_rectangle(applet, b->pos.x * CELL_SIZE,  b->pos.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, g->palette[b->palette_index]);
}

void draw_grid(mz_applet* applet, const grid* g)
{
	// draw grid
	for (int i = 0; i < g->width * g->height; i++)
	{
		if (g->blocks[i].empty == MUZZLE_FALSE)
		{
			draw_block(applet, g, &g->blocks[i]);
		}
	}

	// draw grid lines
	for (int x = 0; x < g->width; x++)
	{
		mz_draw_rectangle(applet, x * CELL_SIZE, 0, 1, SCREEN_HEIGHT, g->palette[PALETTE_GRID_LINES]);
	}

	for (int y = 0; y < g->height; y++)
	{
		mz_draw_rectangle(applet, 0, y * CELL_SIZE, SCREEN_WIDTH, 1, g->palette[PALETTE_GRID_LINES]);
	}
}

void applet_loop(mz_applet* applet)
{
	mz_tint palette[PALETTE_SIZE] =
	{
		TINT_BLACK, // PALETTE_BACKGROUND
		TINT_GRAY, // PALETTE_GRID_LINES
		TINT(0, 255, 255, 255), // PALETTE_TETROMINO_I
		TINT(255, 255, 0, 255), // PALETTE_TETROMINO_O
		TINT(128, 0, 128, 255), // PALETTE_TETROMINO_T
		TINT(255, 165, 0, 255), // PALETTE_TETROMINO_L
		TINT(0, 0, 255, 255), // PALETTE_TETROMINO_J
		TINT(0, 255, 0, 255), // PALETTE_TETROMINO_S
		TINT(255, 0, 0, 255) // PALETTE_TETROMINO_Z
	};

	const grid g = init_grid(palette);
	int cursor = 0;

	while (mz_keep_applet(applet))
	{
		mz_begin_drawing(applet);
			mz_clear_screen(g.palette[PALETTE_BACKGROUND]);
			draw_grid(applet, &g);
		mz_end_drawing(applet);
	}

	free_grid(&g);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [EXAMPLE] - Tetris", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
