#ifndef MUZZLE_CORE_VECTOR_H
#define MUZZLE_CORE_VECTOR_H

#ifdef MUZZLE_INCLUDE_VECTOR_HELPERS
	#define MZ_VEC2(x,y)		(mz_vec2){x,y}
	#define MZ_VEC2_D(x,y)		(mz_vec2_d){x,y}
	#define MZ_VEC2_I(x,y)		(mz_vec2_i){x,y}

	#define MZ_VEC3(x,y,z)		(mz_vec3){x,y,z}
	#define MZ_VEC3_D(x,y,z)	(mz_vec3_d){x,y,z}
	#define MZ_VEC3_I(x,y,z)	(mz_vec3_i){x,y,z}

	#define MZ_VEC4(x,y,z,w)	(mz_vec4){x,y,z,w}
	#define MZ_VEC4_D(x,y,z,w)	(mz_vec4_d){x,y,z,w}
	#define MZ_VEC4_I(x,y,z,w)	(mz_vec4_i){x,y,z,w}
#endif

typedef struct mz_vec2
{
	float x;
	float y;
} mz_vec2;

typedef struct mz_vec2_d
{
	double x;
	double y;
} mz_vec2_d;

typedef struct mz_vec2_i
{
	int x;
	int y;
} mz_vec2_i;

typedef struct mz_vec3
{
	float x;
	float y;
	float z;
} mz_vec3;

typedef struct mz_vec3_d
{
	double x;
	double y;
	double z;
} mz_vec3_d;

typedef struct mz_vec3_i
{
	int x;
	int y;
	int z;
} mz_vec3_i;

typedef struct mz_vec4
{
	float x;
	float y;
	float z;
	float w;
} mz_vec4;

typedef struct mz_vec4_d
{
	double x;
	double y;
	double z;
	double w;
} mz_vec4_d;

typedef struct mz_vec4_i
{
	int x;
	int y;
	int z;
	int w;
} mz_vec4_i;

// TODO: Vector Operations

#endif // MUZZLE_CORE_VECTOR_H
