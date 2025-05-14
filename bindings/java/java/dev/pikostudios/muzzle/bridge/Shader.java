package dev.pikostudios.muzzle.bridge;

public class Shader
{
    public enum ShaderType
    {
        PASS,
        DIRECT_QUAD,
        DIRECT_CIRCLE,
        DIRECT_SPRITE,
        DIRECT_TEXT
    }

    private int id;
    private int type;

    private Shader(int id, int type)
    {
        this.id = id;
        this.type = type;
    }

    // For ShaderPipeline only
    protected Shader(int id)
    {
        this.id = id;
        this.type = 5;
    }

    public static Shader create(String vertexSource, String fragmentSource, ShaderType type)
    {
        return create(vertexSource, fragmentSource, type.ordinal());
    }

    public static Shader load(String vertexFilepath, String fragmentFilepath, ShaderType type)
    {
        return load(vertexFilepath, fragmentFilepath, type.ordinal());
    }

    private static native Shader create(String vertexSource, String fragmentSource, int type);

    private static native Shader load(String vertexFilepath, String fragmentFilepath, int type);

    // TODO: Add error checking if type is pipeline
    public void use(Applet applet) throws IllegalStateException
    {
        if (this.type != ShaderType.PASS.ordinal())
        {
            throw new IllegalStateException("Cannot call use() on a non-shader pass. Use beginShader instead");
        }

        this._use(applet);
    }

    public void beginShader(Applet applet) throws IllegalStateException
    {
        if (this.type == ShaderType.PASS.ordinal())
        {
            throw new IllegalStateException("Cannot call beginShader() on a shader-pass. Use use() instead");
        }

        this._beginShader(applet);
    }

    public void endShader(Applet applet) throws IllegalStateException
    {
        if (this.type == ShaderType.PASS.ordinal())
        {
            throw new IllegalStateException("Cannot call endShader() on a shader-pass.");
        }

        this._endShader(applet);
    }

    public void uploadUniformMatrix(String uniform, float[] matrix) throws IllegalArgumentException
    {
        if (matrix.length == 9)
        {
            this.uploadUniformMat3(uniform, matrix);
        }

        else if (matrix.length == 16)
        {
            this.uploadUniformMat4(uniform, matrix);
        }

        else
        {
            throw new IllegalArgumentException("Matrix must be size 3x3 or 4x4");
        }
    }

    public native void uploadUniform(String uniform, int value);
    public native void uploadUniform(String uniform, float value);
    public native void uploadUniform(String uniform, float x, float y);
    public native void uploadUniform(String uniform, float x, float y, float z);
    public native void uploadUniform(String uniform, float x, float y, float z, float w);

    public native void unload();

    private native void _use(Applet applet);
    private native void _beginShader(Applet applet);
    private native void _endShader(Applet applet);

    private native void uploadUniformMat3(String uniform, float[] matrix);
    private native void uploadUniformMat4(String uniform, float[] matrix);
}
