#ifndef MUZZLE_CORE_VECTOR_H
#define MUZZLE_CORE_VECTOR_H

struct _mz_vec2
{
	float x;
	float y;
};

struct _mz_vec2_d
{
	double x;
	double y;
};

struct _mz_vec2_i
{
	int x;
	int y;
};

struct _mz_vec3
{
	float x;
	float y;
	float z;
};

struct _mz_vec3_d
{
	double x;
	double y;
	double z;
};

struct _mz_vec3_i
{
	int x;
	int y;
	int z;
};

struct _mz_vec4
{
	float x;
	float y;
	float z;
	float w;
};

struct _mz_vec4_d
{
	double x;
	double y;
	double z;
	double w;
};

struct _mz_vec4_i
{
	int x;
	int y;
	int z;
	int w;
};

typedef struct _mz_vec2 vec2;
typedef struct _mz_vec2_d vec2_d;
typedef struct _mz_vec2_i vec2_i;

typedef struct _mz_vec3 vec3;
typedef struct _mz_vec3_d vec3_d;
typedef struct _mz_vec3_i vec3_i;

typedef struct _mz_vec4 vec4;
typedef struct _mz_vec4_d vec4_d;
typedef struct _mz_vec4_i vec4_i;

#endif // MUZZLE_CORE_VECTOR_H