package dev.pikostudios.muzzle.bridge;

public class Drawing
{
    public static native void beginDrawing(Applet applet);
    public static native void endDrawing(Applet applet);
    public static native void clearScreen(Tint tint);
}
