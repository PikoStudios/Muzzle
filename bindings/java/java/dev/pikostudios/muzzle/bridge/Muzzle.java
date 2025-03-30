package dev.pikostudios.muzzle.bridge;

public class Muzzle
{
    private Muzzle() {}

    public static void initialize()
    {
        initialize("muzzlejni");
    }

    public static void initialize(String libraryName)
    {
        System.loadLibrary(libraryName);
    }
}
