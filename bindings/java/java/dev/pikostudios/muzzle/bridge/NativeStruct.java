package dev.pikostudios.muzzle.bridge;

public abstract class NativeStruct
{
	private final long nativePointer;
	
	public NativeStruct(long nativePointer)
	{
		this.nativePointer = nativePointer;
	}

	public long getNativePointer()
	{
		return this.nativePointer;
	}
}
