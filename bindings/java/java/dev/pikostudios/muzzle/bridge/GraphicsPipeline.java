package dev.pikostudios.muzzle.bridge;

import java.util.Objects;
import java.util.Optional;

public class GraphicsPipeline extends NativeStruct
{
	public enum DepthBufferType
	{
		NONE,
		RENDERBUFFER,
		TEXTURE;

		public static DepthBufferType fromOrdinal(int ordinal)
		{
			return switch (ordinal)
			{
				case 0 -> NONE;
				case 1 -> RENDERBUFFER;
				case 2 -> TEXTURE;
				default -> throw new IllegalArgumentException("Unknown DepthBufferType ordinal " + ordinal);
			};
		}
	}

	public static final class Factory
	{
		private Shader shader;
		private Sprite.Format[] colorAttachmentFormats;
		private int width;
		private int height;
		private Optional<DepthBufferType> depthBufferType;

		private Factory()
		{
			this.depthBufferType = Optional.empty();
		}

		public Factory shader(Shader shader)
		{
			this.shader = Objects.requireNonNull(shader);
			return this;
		}

		public Factory framebufferDimensions(int width, int height)
		{
			assert width >= 0 && width <= 0xFFFFL	: "width is out of uint16 range";
			assert height >= 0 && height <= 0xFFFFL : "height is out of uint16 range";
			
			this.width = width;
			this.height = height;

			return this;
		}

		public Factory colorAttachments(Sprite.Format... formats)
		{
			this.colorAttachmentFormats = formats;
			return this;
		}

		public Factory depthBuffer(DepthBufferType type)
		{
			if (type == DepthBufferType.NONE)
			{
				throw new IllegalArgumentException("Cannot use depth buffer type \"NONE\"");
			}
			
			this.depthBufferType = Optional.of(type);

			return this;
		}

		public GraphicsPipeline build()
		{
			int[] colorAttachmentFormatsInt = new int[this.colorAttachmentFormats.length];

			for (int i = 0; i < this.colorAttachmentFormats.length; i++)
			{
				colorAttachmentFormatsInt[i] = this.colorAttachmentFormats[i].ordinal();
			}

			return GraphicsPipeline.create(this.shader, colorAttachmentFormatsInt, this.width, this.height, this.depthBufferType.isPresent(), this.depthBufferType.orElse(DepthBufferType.NONE).ordinal());
		}
	}
	
	private final Shader shader;

	private GraphicsPipeline(long nativePointer, Shader shader)
	{
		super(nativePointer);
		this.shader = shader;
	}

	public final static Factory factory()
	{
		return new Factory();
	}

	private final static native GraphicsPipeline create(Shader shader, int[] colorAttachmentFormats, int framebufferWidth, int framebufferHeight, boolean createDepthBuffer, int depthBufferType);

	public final void dispatch(VertexBuffer buffer, long start, long count)
	{
		assert start >= 0 && start <= 0xFFFFFFFFL : "start is out of uint32 range";
		assert count >= 0 && count <= 0xFFFFFFFFL : "end is out of uint32 range";

		this._dispatch(buffer, start, count);
	}
	
	public final void clearColorAttachments(Tint clearColor)
	{
		this._clearColorAttachments(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), clearColor.getAlpha());
	}

	public final Shader getShader()
	{
		return this.shader;
	}
	
	public final native void clearDepthBuffer(float clearValue);
	
	public final native int getFramebufferID();
	public final native int getFramebufferWidth();
	public final native int getFramebufferHeight();

	public final native int getColorAttachmentsCount();
	public final native Sprite getColorAttachmentTexture(int index);
	public final native int getColorAttachmentID(int index);
	
	public final Sprite.Format getColorAttachmentFormat(int index)
	{
		return Sprite.Format.fromOrdinal(this._getColorAttachmentFormat(index));
	}

	public final native Sprite getDepthBufferTexture();
	public final native int getDepthBufferID();
	
	public final DepthBufferType getDepthBufferType()
	{
		return DepthBufferType.fromOrdinal(this._getDepthBufferType());
	}

	public final native void unload();

	private final native int _getDepthBufferType();
	private final native int _getColorAttachmentFormat(int index);
	private final native void _clearColorAttachments(int r, int g, int b, int a);
	private final native void _dispatch(VertexBuffer buffer, long start, long count);
}
