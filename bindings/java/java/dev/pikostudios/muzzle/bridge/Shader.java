package dev.pikostudios.muzzle.bridge;

public class Shader
{
    public enum ShaderTarget
    {
        DIRECT_QUAD,
        DIRECT_CIRCLE,
        DIRECT_SPRITE,
        DIRECT_TEXT
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

    // TODO: Add error checking if type is pipeline
    public void useAsShaderPass(Applet applet) throws IllegalStateException
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
