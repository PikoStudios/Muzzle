package dev.pikostudios.muzzle.bridge;

import java.nio.ByteBuffer;

import dev.pikostudios.muzzle.bridge.GPUBufferDescriptor;

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
		LINES;

		public static TopologyType fromOrdinal(int ordinal)
		{
			return switch (ordinal)
			{
				case 0 -> TRIANGLE;
				case 1 -> TRIANGLE_STRIP;
				case 2 -> TRIANGLE_FAN;
				case 3 -> POINT;
				case 4 -> LINES;
				default -> throw new IllegalArgumentException("Unknown TopologyType ordinal of " + ordinal);
			};
		}
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

	public final TopologyType getTopologyType()
	{
		return TopologyType.fromOrdinal(this._getTopologyType());
	}

	public final void allocate(GPUBufferDescriptor bufferDescriptor)
	{
		ByteBuffer buffer = bufferDescriptor.buildBuffer();
		this.allocate(buffer, buffer.limit());
	}

	public final void write(GPUBufferDescriptor bufferDescriptor, long offset)
	{
		ByteBuffer buffer = bufferDescriptor.buildBuffer();
		this.write(buffer, buffer.limit(), offset);
	}

	public final native long getSize();
	public final native long getStride();
	public final native int getVAO();
	public final native int getVBO();
	
	public final native void allocate(long sizeInBytes);
	
	public final native void unload();

	private final native int _getTopologyType();
	private final native void allocate(ByteBuffer data, long size);
	private final native void write(ByteBuffer data, long size, long offset);
}
