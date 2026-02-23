package dev.pikostudios.muzzle.bridge;

public final class GPUTypeSizes
{
	public static final int INT_SIZE = 4;
    public static final int FLOAT_SIZE = 4;
    public static final int VEC2_SIZE = FLOAT_SIZE * 2;
    public static final int VEC3_SIZE = FLOAT_SIZE * 3;
    public static final int VEC3_STD430_SIZE = 16; // std430 vec3s are aligned
    public static final int VEC4_SIZE = FLOAT_SIZE * 4;
    public static final int MAT3_SIZE = FLOAT_SIZE * 3 * 3;
    public static final int MAT3_STD430_SIZE = 48; // std430 mat3s are aligned
    public static final int MAT4_SIZE = FLOAT_SIZE * 4 * 4;

    private GPUTypeSizes()
    {
    }
}
