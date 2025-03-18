package dev.pikostudios.muzzle.bridge;

public class Font extends NativeStruct
{
    private Font(long nativePointer)
    {
        super(nativePointer);
    }

    public static native void load(Applet applet, String filepath);
    public static native void unload(Font font);
}