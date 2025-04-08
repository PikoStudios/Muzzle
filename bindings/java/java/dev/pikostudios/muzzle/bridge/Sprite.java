package dev.pikostudios.muzzle.bridge;

public class Sprite
{
    private final int width;
    private final int height;
    private int id;

    private Sprite(int width, int height, int id)
    {
        this.width = width;
        this.height = height;
        this.id = id;
    }

    public static native Sprite load(String filepath);
    public static native void unload(Sprite sprite);

    public native void draw(Applet applet, float x, float y, Tint tint);

    public int getWidth()
    {
        return this.width;
    }

    public int getHeight()
    {
        return this.height;
    }
}
