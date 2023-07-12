#ifndef MUZZLE_CORE_TINT_H
#define MUZZLE_CORE_TINT_H

#define NORMALIZE_TINT_AS_VEC4(x) MZ_LITERAL(vec4){x.r / 255, x.g / 255, x.b / 255, x.a / 255};

struct _mz_tint
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
};

typedef struct _mz_tint tint;

#define WHITE      MZ_LITERAL(tint){255,255,255,255}
#define GRAY       MZ_LITERAL(tint){84, 84, 84, 255}
#define RED        MZ_LITERAL(tint){255,0,0,255}
#define ORANGE     MZ_LITERAL(tint){255,153,51,255}
#define GREEN      MZ_LITERAL(tint){102,255,102,255}
#define BLUE       MZ_LITERAL(tint){0,128,255,255}
#define PURPLE     MZ_LITERAL(tint){178,102,255,255}
#define PINK       MZ_LITERAL(tint){255,204,255,255}
#define MAGENTA    MZ_LITERAL(tint){255,102,255,255}
#define YELLOW     MZ_LITERAL(tint){255,255,51,255}
#define USAF_BLUE  MZ_LITERAL(tint){0,48,143,255}
#define BLACK      MZ_LITERAL(tint){0,0,0,255}


#endif // MUZZLE_CORE_TINT_H