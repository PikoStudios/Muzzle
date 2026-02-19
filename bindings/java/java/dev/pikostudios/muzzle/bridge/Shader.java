package dev.pikostudios.muzzle.bridge;

public class Shader
{
    public enum ShaderTarget
    {
        DIRECT_QUAD,
        DIRECT_CIRCLE,
        DIRECT_SPRITE,
        DIRECT_TEXT;

        public static ShaderTarget fromOrdinal(int target)
        {
            return switch (target)
            {
                case 0 -> DIRECT_QUAD;
                case 1 -> DIRECT_CIRCLE;
                case 2 -> DIRECT_SPRITE;
                case 3 -> DIRECT_TEXT;
                default -> throw new IllegalArgumentException("Unknown ShaderTarget ordinal of " + target);
            };
        }
    }

    private int id;

    private Shader(int id)
    {
        this.id = id;
    }

    @Deprecated
    protected static Shader fromShaderPipeline(int id)
    {
        return new Shader(id);
    }

    protected static Shader fromComputePipeline(int id)
    {
        return new Shader(id);
    }

    public static Shader create(String vertexSource, String fragmentSource)
    {
        return _create(vertexSource, fragmentSource);
    }

    public static Shader load(String vertexFilepath, String fragmentFilepath)
    {
        return _load(vertexFilepath, fragmentFilepath);
    }

    private static native Shader _create(String vertexSource, String fragmentSource);

    private static native Shader _load(String vertexFilepath, String fragmentFilepath);

    public int getID()
    {
        return this.id;
    }

    public void uploadUniformMatrix(String uniform, float[] matrix) throws IllegalArgumentException
    {
        switch (matrix.length)
        {
            case 9 -> this.uploadUniformMat3(uniform, matrix);
            case 16 -> this.uploadUniformMat4(uniform, matrix);
            default -> throw new IllegalArgumentException("Matrix must be size 3x3 or 4x4");
        }
    }

    public native void uploadUniform(String uniform, int value);
    public native void uploadUniform(String uniform, float value);
    public native void uploadUniform(String uniform, float x, float y);
    public native void uploadUniform(String uniform, float x, float y, float z);
    public native void uploadUniform(String uniform, float x, float y, float z, float w);

    public native void unload();

    private native void uploadUniformMat3(String uniform, float[] matrix);
    private native void uploadUniformMat4(String uniform, float[] matrix);
}
