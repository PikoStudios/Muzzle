package dev.pikostudios.muzzle.bridge;

public class Text
{
    public static native float measureWidth(String text, float fontSize, Font font);
    public static native float measureHeight(String text, float fontSize, Font font);
    
    public static native void draw(Applet applet, String text, float x, float y, float fontSize, Font font, Tint tint);
    public static native void drawCentered(Applet applet, String text, float x, float y, float fontSize, Font font, Tint tint);
}
