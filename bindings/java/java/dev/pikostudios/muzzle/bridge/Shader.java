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

    public native void unload();

    private native void _use(Applet applet);
    private native void _beginShader(Applet applet);
    private native void _endShader(Applet applet);
}
