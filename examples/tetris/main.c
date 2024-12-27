#include <Muzzle.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 800
#define CELL_SIZE 40
#define TINT(r,g,b,a) (mz_tint){r,g,b,a}
#define CLONE_BLOCK(b) (block){.pos=b->pos, .palette_index=b->palette_index, .empty=b->empty}
#define SEC_TO_TIMESPEC(s) (struct timespec){.tv_sec = s}

#define TARGET_FPS 10.f

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

#define MAX_TETROMINOS 40
#define KEEP_TETROMINO (MUZZLE_TRUE)
#define TETROMINO_FALL_INTERVAL 0.5f

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

#define NUM_TETROMINO_TYPES (TETROMINO_Z + 1)

typedef struct block
{
	mz_vec2_i pos;
	uint8_t palette_index;
	mz_boolean empty;
	mz_boolean owned;
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
	double update_timer;
	block** blocks;
	mz_vec2_i top_left;
	tetromino_type type;
	uint8_t width;
	uint8_t height;
} tetromino;

typedef struct grid
{
	mz_tint* palette;
	block* blocks;
	uint8_t width;
	uint8_t height;
} grid;

/** GRID BEGIN **/

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
		g.blocks[i].owned = MUZZLE_FALSE;
	}

	return g;
}

void free_grid(const grid* g)
{
	MZ_FREE(g->blocks);
}

void allocate_block_space(const grid* g, const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t height, block** out)
{
	uint8_t bx = 0;
	uint8_t by = 0;

	for (int i = 0; i < width * height; i++)
	{
		out[i] = &g->blocks[(y + by) * g->width + (x + bx)];
		out[i]->owned = MUZZLE_TRUE;

		if (++bx == width)
		{
			bx = 0;
			by++;
		}
	}
}

void reallocate_block_space(const grid* g, const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t height, block** out)
{
	block copy[width * height];

	for (int i = 0; i < width * height; i++)
	{
		copy[i] = CLONE_BLOCK(out[i]);
		out[i]->empty = MUZZLE_TRUE;
		out[i]->palette_index = PALETTE_BACKGROUND;
		out[i]->owned = MUZZLE_FALSE;
	}

	allocate_block_space(g, x, y, width, height, out);

	for (int i = 0; i < width * height; i++)
	{
		out[i]->empty = copy[i].empty;
		out[i]->palette_index = copy[i].palette_index;
	}
}


void draw_block(mz_applet* applet, const grid* g, const block* b)
{
	mz_draw_rectangle(applet, b->pos.x * CELL_SIZE,  b->pos.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, g->palette[b->palette_index]);
}

void update_grid(const grid* g)
{
	for (int i = g->height - 1; i >= 0; i--)
	{
		uint8_t filled = 0;

		for (int j = 0; j < g->width; j++)
		{
			const int idx = i * g->width + j;

			if (g->blocks[idx].owned == MUZZLE_FALSE && g->blocks[idx].empty == MUZZLE_FALSE)
			{
				filled++;
			}
		}

		if (filled == g->width)
		{
			for (int j = 0; j < g->width; j++)
			{
				const int idx = i * g->width + j;

				g->blocks[idx].empty = MUZZLE_TRUE;
				g->blocks[idx].palette_index = PALETTE_BACKGROUND;
			}

			// TODO: Shift blocks down
		}
	}
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

/** GRID END **/

/** TETROMINO BEGIN **/

tetromino init_tetromino(const grid* g, const tetromino_type type, const uint8_t x)
{
	tetromino t = (tetromino){0};
	t.type = type;

	uint8_t palette_index = 0;
	const char* definition = "";

	switch (type)
	{
		case TETROMINO_I:
			t.width = TETROMINO_I_WIDTH;
			t.height = TETROMINO_I_HEIGHT;
			definition = TETROMINO_I_DEFINITION;
			palette_index = PALETTE_TETROMINO_I;
			break;

		case TETROMINO_O:
			t.width = TETROMINO_O_WIDTH;
			t.height = TETROMINO_O_HEIGHT;
			definition = TETROMINO_O_DEFINITION;
			palette_index = PALETTE_TETROMINO_O;
			break;

		case TETROMINO_T:
			t.width = TETROMINO_T_WIDTH;
			t.height = TETROMINO_T_HEIGHT;
			definition = TETROMINO_T_DEFINITION;
			palette_index = PALETTE_TETROMINO_T;
			break;

		case TETROMINO_L:
			t.width = TETROMINO_L_WIDTH;
			t.height = TETROMINO_L_HEIGHT;
			definition = TETROMINO_L_DEFINITION;
			palette_index = PALETTE_TETROMINO_L;
			break;

		case TETROMINO_J:
			t.width = TETROMINO_J_WIDTH;
			t.height = TETROMINO_J_HEIGHT;
			definition = TETROMINO_J_DEFINITION;
			palette_index = PALETTE_TETROMINO_J;
			break;

		case TETROMINO_S:
			t.width = TETROMINO_S_WIDTH;
			t.height = TETROMINO_S_HEIGHT;
			definition = TETROMINO_S_DEFINITION;
			palette_index = PALETTE_TETROMINO_S;
			break;

		case TETROMINO_Z:
			t.width = TETROMINO_Z_WIDTH;
			t.height = TETROMINO_Z_HEIGHT;
			definition = TETROMINO_Z_DEFINITION;
			palette_index = PALETTE_TETROMINO_Z;
			break;
	}

	t.blocks = MZ_CALLOC(t.width * t.height, sizeof(block*));
	t.top_left = (mz_vec2_i){x, 0};

	if (t.blocks == NULL)
	{
		printf("Failed to allocate memory for tetromino block space\n");
		exit(-1);
	}

	allocate_block_space(g, x, 0, t.width, t.height, t.blocks);

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

tetromino_type random_tetromino()
{
	return rand() % NUM_TETROMINO_TYPES; // NOLINT(cert-msc50-cpp)
}

mz_boolean tetromino_colliding_bottom(const grid* g, const tetromino* t)
{
	for (int i = 0; i < t->width; i++)
	{
		if (t->top_left.y + t->height < g->height && g->blocks[(t->top_left.y + t->height) * g->width + (t->top_left.x + i)].empty == MUZZLE_FALSE)
		{
			return MUZZLE_TRUE;
		}
	}

	return MUZZLE_FALSE;
}

mz_boolean update_tetromino(mz_applet* applet, const grid* g, tetromino* t, uint8_t* cursor)
{
	if (mz_key_pressed(applet, KEY_LEFT) && t->top_left.x > 0)
	{
		(*cursor)--;
		t->top_left.x--;
	}

	else if (mz_key_pressed(applet, KEY_RIGHT) && t->top_left.x + t->width < g->width)
	{
		(*cursor)++;
		t->top_left.x++;
	}

	else if ((mz_key_pressed(applet, KEY_DOWN) || t->update_timer > TETROMINO_FALL_INTERVAL) && t->top_left.y + t->height < g->height && tetromino_colliding_bottom(g, t) == MUZZLE_FALSE)
	{
		t->top_left.y++;
		t->update_timer = 0;
	}

	else if (t->top_left.y + t->height == g->height || tetromino_colliding_bottom(g, t) == MUZZLE_TRUE)
	{
		return !KEEP_TETROMINO;
	}

	else
	{
		t->update_timer += applet->delta_time;
		return KEEP_TETROMINO;
	}

	reallocate_block_space(g, t->top_left.x, t->top_left.y, t->width, t->height, t->blocks);
	return KEEP_TETROMINO;
}

void free_tetromino(tetromino* t)
{
	for (int i = 0; i < t->width * t->height; i++)
	{
		t->blocks[i]->owned = MUZZLE_FALSE;
	}

	MZ_FREE(t->blocks);
}

/** TETROMINO END **/

void applet_loop(mz_applet* applet)
{
	srand(time(NULL)); // NOLINT(cert-msc51-cpp)

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
	uint8_t cursor = 4;
	tetromino t = init_tetromino(&g, random_tetromino(), cursor);

	while (mz_keep_applet(applet))
	{
		if (applet->delta_time < 1.f / TARGET_FPS)
		{
			mz_sleep((1.f / TARGET_FPS) - applet->delta_time);
		}

		if (update_tetromino(applet, &g, &t, &cursor) != KEEP_TETROMINO)
		{
			free_tetromino(&t);
			t = init_tetromino(&g, random_tetromino(), cursor);
		}

		update_grid(&g);

		mz_begin_drawing(applet);
			mz_clear_screen(g.palette[PALETTE_BACKGROUND]);
			draw_grid(applet, &g);
		mz_end_drawing(applet);
	}

	free_tetromino(&t);
	free_grid(&g);
}

int main(void)
{
	mz_applet applet = mz_initialize_applet("Muzzle [EXAMPLE] - Tetris", SCREEN_WIDTH, SCREEN_HEIGHT, APPLET_FLAG_VSYNC | APPLET_FLAG_TRACK_DELTA_TIME);
	mz_start_applet(&applet, applet_loop);
	
	mz_terminate_applet(&applet);
	return 0;
}
