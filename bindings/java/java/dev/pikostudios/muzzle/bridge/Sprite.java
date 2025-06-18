package dev.pikostudios.muzzle.bridge;

public class Sprite
{
    public enum WrappingMode
    {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE
    }

    public enum Format
    {
        RGBA8,
        RGBA32F
    }

    public enum FilterMode
    {
        NEAREST,
        FILTER
    }
    
    private final int width;
    private final int height;
    private int id;

    protected Sprite(int width, int height, int id)
    {
        this.width = width;
        this.height = height;
        this.id = id;
    }

    public static Sprite create(int width, int height, WrappingMode wrappingMode, FilterMode minFilter, FilterMode magFilter, Format format, byte[] data)
    {
        return create(width, height, wrappingMode.ordinal(), minFilter.ordinal(), magFilter.ordinal(), format.ordinal(), data);
    }

    public static native Sprite load(String filepath);
    public static native void unload(Sprite sprite);

    private static native Sprite create(int width, int height, int wrappingMode, int minFilter, int magFilter, int filter, byte[] data);

    public native void draw(Applet applet, float x, float y, Tint tint);
    public native void drawScaled(Applet applet, float x, float y, float scale, Tint tint);
    public native void drawResized(Applet applet, float x, float y, int width, int height, Tint tint);

    public native void bind(Applet applet, byte textureUnit);
    
    public native byte[] getPixels();

    public int getWidth()
    {
        return this.width;
    }

    public int getHeight()
    {
        return this.height;
    }

    public int getID()
    {
        return this.id;
    }
}
