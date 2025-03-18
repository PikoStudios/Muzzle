package dev.pikostudios.muzzle.bridge;

public class Circle
{
    private float x;
    private float y;
    private float radius;

    public Circle(float x, float y, float radius)
    {
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    public static native void draw(Applet applet, float x, float y, float radius, Tint tint);

    public void draw(Applet applet, Tint tint)
    {
        Circle.draw(applet, this.x, this.y, this.radius, tint);
    }

    public float getX()
    {
        return this.x;
    }

    public float getY()
    {
        return this.y;
    }

    public float getRadius()
    {
        return this.radius;
    }

    public void setX(float x)
    {
        this.x = x;
    }

    public void setY(float y)
    {
        this.y = y;
    }

    public void setRadius(float radius)
    {
        this.radius = radius;
    }
}