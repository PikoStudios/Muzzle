package dev.pikostudios.muzzle.bridge;

import dev.pikostudios.muzzle.bridge.utils.NativeStruct;

public class Applet extends NativeStruct
{
	public interface DispatchCallback
	{
		void invoke(Applet applet);
	}

	public static final int APPLET_FLAG_RESIZABLE = 1 << 0;
	public static final int APPLET_FLAG_VSYNC = 1 << 1;
	public static final int APPLET_FLAG_TRACK_DELTA_TIME = 1 << 2;

	private Applet(long nativePointer)
	{
		super(nativePointer);
	}

	public static native Applet initialize(String windowTitle, int width, int height, int flags);

	public native void start(DispatchCallback callback);
	public native boolean keepRunning();
	public native void terminate();
	public native void updateWindowTitle(String title);

	public native int getWidth();
	public native int getHeight();
	public native double getDeltaTime();
}
