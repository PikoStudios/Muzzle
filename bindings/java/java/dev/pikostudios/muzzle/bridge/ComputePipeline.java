package dev.pikostudios.muzzle.bridge;

public class ComputePipeline
{
	private Shader shader;
	private Sprite texture;
	private byte textureUnit;

	private ComputePipeline(int shaderID, int textureID, int textureWidth, int textureHeight, byte textureUnit)
	{
		this.shader = Shader.fromComputePipeline(shaderID);
		this.texture = new Sprite(textureID, textureWidth, textureHeight);
		this.textureUnit = textureUnit;
	}

	public static native ComputePipeline create(String computeShader, boolean isFilepath, Sprite sprite, byte textureUnit);

	public native void dispatch(int workGroupsX, int workGroupsY, int workGroupsZ);
	
	public void unload()
	{
		this.shader.unload();
		this.textureUnit = 0;
	}

	public Shader getShader()
	{
		return this.shader;
	}

	public Sprite getSprite()
	{
		return this.texture;
	}
}
