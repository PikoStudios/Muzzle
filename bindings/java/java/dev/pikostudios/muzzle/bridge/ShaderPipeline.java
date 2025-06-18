package dev.pikostudios.muzzle.bridge;

import java.util.Objects;

public class ShaderPipeline
{
	public static record Attribute(int index, int size, boolean normalized, int stride, int offset)
	{
	}
	
	public static class Factory
	{
		// Vertex
		private int vPrimitiveType;
		private Attribute[] vAttributes;
		private float[] vVertices;
		private String vSource;
		private boolean vIsSourceFilepath;

		// Fragment
		private String fSource;
		private boolean fIsSourceFilepath;

		// Geometry
		private String gSource;
		private boolean gIsSourceFilepath;

		private Factory()
		{
		}

		public Factory vertex(int primitiveType, float[] vertices, String source, boolean isSourceFilepath, Attribute... attrs)
		{
			this.vPrimitiveType = primitiveType;
			this.vVertices = vertices;
			this.vSource = source;
			this.vIsSourceFilepath = isSourceFilepath;
			this.vAttributes = attrs;

			return this;
		}

		public Factory fragment(String source, boolean isSourceFilepath)
		{
			this.fSource = source;
			this.fIsSourceFilepath = isSourceFilepath;

			return this;
		}
		
		public Factory geometry(String source, boolean isSourceFilepath)
		{
			this.gSource = source;
			this.gIsSourceFilepath = isSourceFilepath;

			return this;
		}

		public ShaderPipeline build()
		{
			Objects.requireNonNull(this.vVertices);
			
			return ShaderPipeline.create(
				this.vPrimitiveType, this.vVertices, this.vSource, this.vIsSourceFilepath, this.vAttributes,
				this.fSource, this.fIsSourceFilepath,
				this.gSource, this.gIsSourceFilepath
			);
		}
	}

	public final static int PRIMITIVE_TYPE_TRIANGLE = 0;
	public final static int PRIMITIVE_TYPE_TRIANGLE_STRIP = 1;
	public final static int PRIMITIVE_TYPE_POINT = 2;
	
	private int pid;
	private int vao;
	private int vbo;
	private int primitiveType;
	
	private ShaderPipeline(int pid, int vao, int vbo, int primitiveType)
	{
		this.pid = pid;
		this.vao = vao;
		this.vbo = vbo;
		this.primitiveType = primitiveType;
	}

	public static Factory factory()
	{
		return new Factory();
	}

	private static native ShaderPipeline create(
		int vPrimitiveType, float[] vVertices, String vSource, boolean vIsSourceFilepath, Attribute[] vAttributes,
		String fSource, boolean fIsSourceFilepath,
		String gSource, boolean gIsSourceFilepath
	);

	public int getID()
	{
		return this.pid;
	}

	public Shader getShader()
	{
		return Shader.fromShaderPipeline(this.pid);
	}

	public void draw(int start, int end)
	{
		this.draw(null, start, end);
	}
	
	public native void draw(float[] vertices, int start, int end);
	public native void unload();
}
