package dev.pikostudios.muzzle.bridge;

public class Tint
{
    public static final Tint WHITE = new Tint(255, 255, 255, 255);
    public static final Tint GRAY = new Tint(84, 84, 84, 255);
    public static final Tint RED = new Tint(255, 0, 0, 255);
    public static final Tint ORANGE = new Tint(255, 153, 51, 255);
    public static final Tint GREEN = new Tint(102, 255, 102, 255);
    public static final Tint BLUE = new Tint(0, 128, 255, 255);
    public static final Tint PURPLE = new Tint(178, 102, 255, 255);
    public static final Tint PINK = new Tint(255, 204, 255, 255);
    public static final Tint MAGENTA = new Tint(255, 102, 255, 255);
    public static final Tint YELLOW = new Tint(255, 255, 51, 255);
    public static final Tint USAF_BLUE = new Tint(0, 48, 143, 255);
    public static final Tint BLACK = new Tint(0, 0, 0, 255);
    public static final Tint MIDNIGHT_BLUE = new Tint(0, 12, 25, 255);

    private final int r;
    private final int g;
    private final int b;
    private final int a;

    public Tint(int r, int g, int b, int a)
    {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }

    public int getRed()
    {
        return this.r;
    }

    public int getGreen()
    {
        return this.g;
    }

    public int getBlue()
    {
        return this.b;
    }

    public int getAlpha()
    {
        return this.a;
    }

    public Tint darker(float scale)
    {
        float s = 1.0f - scale;

        return new Tint((int)(this.r * s), (int)(this.g * s), (int)(this.b * s), this.a);
    }
}
