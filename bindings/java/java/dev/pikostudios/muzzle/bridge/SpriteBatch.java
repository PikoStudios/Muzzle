package dev.pikostudios.muzzle.bridge;

public class SpriteBatch
{
    private int width;
    private int height;
    private int size;
    private int id;

    private SpriteBatch(int width, int height, int size, int id)
    {
        this.width = width;
        this.height = height;
        this.size = size;
        this.id = id;
    }

    public static native SpriteBatch load(String[] filepaths);

    public native bind();
    public native unload();

    public int getWidth()
    {
        return this.width;
    }

    public int getHeight()
    {
        return this.height;
    }

    public int getSize()
    {
        return this.size;
    }

    public int getID()
    {
        return this.id;
    }
}
