#ifndef MUZZLE_CORE_TINT_H
#define MUZZLE_CORE_TINT_H

#include "../backend.h"

typedef struct mz_tint
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
} mz_tint;

#define TINT_WHITE      MZ_LITERAL(mz_tint){255,255,255,255}
#define TINT_GRAY       MZ_LITERAL(mz_tint){84, 84, 84, 255}
#define TINT_RED        MZ_LITERAL(mz_tint){255,0,0,255}
#define TINT_ORANGE     MZ_LITERAL(mz_tint){255,153,51,255}
#define TINT_GREEN      MZ_LITERAL(mz_tint){102,255,102,255}
#define TINT_BLUE       MZ_LITERAL(mz_tint){0,128,255,255}
#define TINT_PURPLE     MZ_LITERAL(mz_tint){178,102,255,255}
#define TINT_PINK       MZ_LITERAL(mz_tint){255,204,255,255}
#define TINT_MAGENTA    MZ_LITERAL(mz_tint){255,102,255,255}
#define TINT_YELLOW     MZ_LITERAL(mz_tint){255,255,51,255}
#define TINT_USAF_BLUE  MZ_LITERAL(mz_tint){0,48,143,255}
#define TINT_BLACK      MZ_LITERAL(mz_tint){0,0,0,255}

#endif // MUZZLE_CORE_TINT_H
