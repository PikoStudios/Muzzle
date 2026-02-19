package dev.pikostudios.muzzle.bridge;

import dev.pikostudios.muzzle.bridge.Applet;
import dev.pikostudios.muzzle.bridge.NativeStruct;
import dev.pikostudios.muzzle.bridge.Shader;

public class ShaderPass
{
	// TODO: Profile if having this in java-land is a bottleneck and i should switch it to a NativeStruct
	
	private Shader shader;
	private int shaderIDCache;
	private int depthTextureUniformLocation;
	private int screenTextureUniformLocation;
	private int resolutionUniformLocation;

	private ShaderPass(Shader shader, int depth, int texture, int resolution)
	{
		this.shader = shader;
		this.shaderIDCache = shader.getID();
		this.depthTextureUniformLocation = depth;
		this.screenTextureUniformLocation = texture;
		this.resolutionUniformLocation = resolution;
	}

	public static native ShaderPass create(Shader shader);

	public Shader getShader()
	{
		return this.shader;
	}

	public int getDepthTextureUniformLocation()
	{
		return this.depthTextureUniformLocation;
	}
	
	public int getScreenTextureUniformLocation()
	{
		return this.screenTextureUniformLocation;
	}
	
	public int getResolutionUniformLocation()
	{
		return this.resolutionUniformLocation;
	}

	public void unload()
	{
		this.shader = null;
		this.shaderIDCache = 0;
		this.depthTextureUniformLocation = -1;
		this.screenTextureUniformLocation = -1;
		this.resolutionUniformLocation = -1;
	}
	
	public final native void use(Applet applet);
}
