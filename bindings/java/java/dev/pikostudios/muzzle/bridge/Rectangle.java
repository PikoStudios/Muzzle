package dev.pikostudios.muzzle.bridge;

public class Rectangle
{
    private float x;
    private float y;
    private float width;
    private float height;

    public Rectangle(float x, float y, float width, float height)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    public static native void draw(Applet applet, float x, float y, float width, float height, Tint tint);

    public void draw(Applet applet, Tint tint)
    {
        Rectangle.draw(applet, this.x, this.y, this.width, this.height, tint);
    }

    public float getX()
    {
        return this.x;
    }

    public float getY()
    {
        return this.y;
    }

    public float getWidth()
    {
        return this.width;
    }

    public float getHeight()
    {
        return this.height;
    }

    public void setX(float x)
    {
        this.x = x;
    }

    public void setY(float y)
    {
        this.y = y;
    }

    public void setWidth(float width)
    {
        this.width = width;
    }

    public void setHeight(float height)
    {
        this.height = height;
    }
}