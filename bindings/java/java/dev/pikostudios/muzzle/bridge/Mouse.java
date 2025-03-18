package dev.pikostudios.muzzle.bridge;

public class Mouse
{
    public static final int MOUSE_BUTTON_LEFT = 0;
    public static final int MOUSE_BUTTON_RIGHT = 1;
    public static final int MOUSE_BUTTON_MIDDLE = 2;

    public static native boolean mousePressed(Applet applet, int button);
    public static native boolean mouseReleased(Applet applet, int button);

    public static native double getMouseX(Applet applet);
    public static native double getMouseY(Applet applet);
}