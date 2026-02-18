package dev.pikostudios.muzzle.bridge;

public class VertexBuffer extends NativeStruct
{
	public static record AttributeDescriptor(byte size, AttributeType type)
	{
		public enum AttributeType
		{
			BYTE,
			UNSIGNED_BYTE,
			SHORT,
			UNSIGNED_SHORT,
			INT,
			UNISGNED_INT,
			HALF_FLOAT,
			FLOAT,
			DOUBLE
		}

		public AttributeDescriptor
		{
			if (size < 1 || size > 4)
			{
				throw new IllegalArgumentException("Attribute size can only be 1 through 4");
			}
		}
	}
	
	public enum TopologyType
	{
		TRIANGLE,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		POINT,
		LINES
	}
	
	private VertexBuffer(long nativePointer)
	{
		super(nativePointer);
	}

	public static VertexBuffer create(TopologyType topologyType, AttributeDescriptor... attributes)
	{
		return create(topologyType.ordinal(), attributes);
	}

	private static native VertexBuffer create(int topologyType, AttributeDescriptor[] attributes);

	public native long getSize();
	public native long getStride();
	public native int getVAO();
	public native int getVBO();
	public native TopologyType getTopologyType();

	public native void unload();
}
