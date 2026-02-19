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
        RGBA32F;

        public static Format fromOrdinal(int ordinal)
        {
            return switch (ordinal)
            {
                case 0 -> RGBA8;
                case 1 -> RGBA32F;
                default -> throw new IllegalArgumentException(ordinal + " is not a valid Sprite.Format ordinal");
            };
        }
    }

    public enum FilterMode
    {
        NEAREST,
        LINEAR
    }

    public enum FlipOrientation
    {
        VERTICAL,
        HORIZONTAL
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

    public void drawFlipped(Applet applet, float x, float y, FlipOrientation orientation, Tint tint)
    {
        this.drawFlipped(applet, x, y, orientation.ordinal(), tint);
    }

    public void drawFlippedScaled(Applet applet, float x, float y, float scale, FlipOrientation orientation, Tint tint)
    {
        this.drawFlippedScaled(applet, x, y, scale, orientation.ordinal(), tint);
    }

    public void drawFlippedResized(Applet applet, float x, float y, int width, int height, FlipOrientation orientation, Tint tint)
    {
        this.drawFlippedResized(applet, x, y, width, height, orientation.ordinal(), tint);
    }

    public native void draw(Applet applet, float x, float y, Tint tint);
    public native void drawScaled(Applet applet, float x, float y, float scale, Tint tint);
    public native void drawResized(Applet applet, float x, float y, int width, int height, Tint tint);

    private native void drawFlipped(Applet applet, float x, float y, int orientation, Tint tint);
    private native void drawFlippedScaled(Applet applet, float x, float y, float scale, int orientation, Tint tint);
    private native void drawFlippedResized(Applet applet, float x, float y, int width, int height, int orientation, Tint tint);

    public native void drawRotated(Applet applet, float x, float y, float rotation, Tint tint);
    public native void drawRotatedScaled(Applet applet, float x, float y, float scale, float rotation, Tint tint);
    public native void drawRotatedResized(Applet applet, float x, float y, int width, int height, float rotation, Tint tint);

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
