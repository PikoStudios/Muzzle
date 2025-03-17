package dev.pikostudios.muzzle.bridge.utils;

public abstract class Struct
{
	private final long nativePointer;
	
	public Struct(long nativePointer)
	{
		this.nativePointer = nativePointer;
	}

	public long getNativePointer()
	{
		return this.nativePointer;
	}
}
