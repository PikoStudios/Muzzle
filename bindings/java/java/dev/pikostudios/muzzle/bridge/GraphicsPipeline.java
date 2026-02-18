package dev.pikostudios.muzzle.bridge;

import java.util.Objects;
import java.util.Optional;

public class GraphicsPipeline extends NativeStruct
{
	public enum DepthBufferType
	{
		RENDERBUFFER,
		TEXTURE;

		public static DepthBufferType fromOrdinal(int ordinal)
		{
			return switch (ordinal)
			{
				case 0 -> RENDERBUFFER;
				case 1 -> TEXTURE;
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

		public void shader(Shader shader)
		{
			this.shader = Objects.requireNonNull(shader);
		}

		public void framebufferDimensions(int width, int height)
		{
			assert width >= 0 && width <= 0xFFFFL	: "width is out of uint16 range";
			assert height >= 0 && height <= 0xFFFFL : "height is out of uint16 range";
			
			this.width = width;
			this.height = height;
		}

		public void colorAttachments(Sprite.Format... formats)
		{
			this.colorAttachmentFormats = formats;
		}

		public void depthBuffer(DepthBufferType type)
		{
			this.depthBufferType = Optional.of(type);
		}

		public GraphicsPipeline build()
		{
			int[] colorAttachmentFormatsInt = /* TODO */;

			return GraphicsPipeline.create(this.shader, colorAttachmentFormatsInt, this.width, this.height, this.depthBufferType.isPresent(), this.depthBufferType.orElse(0));
		}
	}
	
	private GraphicsPipeline(long nativePointer)
	{
		super(nativePointer);
	}

	public static Factory factory()
	{
		return new Factory();
	}

	private static GraphicsPipeline create(Shader shader, int[] colorAttachmentFormats, int framebufferWidth, int framebufferHeight, boolean createDepthBuffer, int depthBufferType);

	public final void dispatch(GraphicsPipeline pipeline, VertexBuffer buffer, long start, long count)
	{
		assert start >= 0 && start <= 0xFFFFFFFFL : "start is out of uint32 range";
		assert count >= 0 && count <= 0xFFFFFFFFL : "end is out of uint32 range";

		this._dispatch(pipeline, buffer, start, count);
	}
	
	public final void clearColorAttachments(Tint clearColor)
	{
		this._clearColorAttachments(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), clearColor.getAlpha());
	}
	
	public final native void clearDepthBuffer(float clearValue);

	public final native Shader getShader();
	
	public final native int getFramebufferID();
	public final native int getFramebufferWidth();
	public final native int getFramebufferHeight();

	public final native int getColorAttachmentsCount();
	public final native Sprite getColorAttachmentTexture(int index);
	public final native int getColorAttachmentFormat(int index); // TODO: Should return a Sprite.Format
	public final native int getColorAttachmentID(int index);

	public final native Sprite getDepthBufferTexture();
	public final native int getDepthBufferID();
	
	public final DepthBufferType getDepthBufferType()
	{
		return DepthBufferType.fromOrdinal(this._getDepthBufferType());
	}

	public final native void unload();

	private final native int _getDepthBufferType();
	private final native void _clearColorAttachments(int r, int g, int b, int a);
	private final native void _dispatch(GraphicsPipeline pipeline, VertexBuffer buffer, long start, long end);
}
