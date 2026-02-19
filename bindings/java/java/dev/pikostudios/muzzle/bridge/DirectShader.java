package dev.pikostudios.muzzle.bridge;

import dev.pikostudios.muzzle.bridge.Applet;
import dev.pikostudios.muzzle.bridge.Shader;

public class DirectShader
{
	private final int target;
	private Shader shader;
	private int shaderIDCache;

	private DirectShader(Shader shader, int target)
	{
		this.target = target;
		this.shader = shader;
		this.shaderIDCache = shader.getID();
	}

	public static DirectShader create(Shader shader, Shader.ShaderTarget target)
	{
		return _create(shader, target.ordinal());
	}

	public final void unload()
	{
		this.shader = null;
		this.shaderIDCache = 0;
	}

	public final Shader getShader()
	{
		return this.shader;
	}

	public Shader.ShaderTarget getTarget()
	{
		return Shader.ShaderTarget.fromOrdinal(this.target);
	}

	public final native void begin(Applet applet);
	public final native void end(Applet applet);

	private static final native DirectShader _create(Shader shader, int target);
}
