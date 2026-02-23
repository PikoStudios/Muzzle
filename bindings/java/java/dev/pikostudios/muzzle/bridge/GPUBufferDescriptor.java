package dev.pikostudios.muzzle.bridge;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import dev.pikostudios.muzzle.bridge.GPUTypeSizes;

public class GPUBufferDescriptor
{
    private static final int BUFFER_REALLOCATION_PADDING = 128;

    protected ByteBuffer buffer;
    protected boolean built;

    protected GPUBufferDescriptor()
    {
        this.buffer = ByteBuffer.allocateDirect(BUFFER_REALLOCATION_PADDING).order(ByteOrder.nativeOrder());
        this.built = false;
    }

    public static GPUBufferDescriptor create()
    {
    	return new GPUBufferDescriptor();
    }

    protected void ensureCapacity(int bytes)
    {
        if (this.buffer.remaining() < bytes)
        {
            ByteBuffer b = ByteBuffer.allocateDirect(this.buffer.position() + bytes + BUFFER_REALLOCATION_PADDING).order(ByteOrder.nativeOrder());
            this.buffer.flip();
            b.put(this.buffer);
            this.buffer = b;
        }
    }

    public GPUBufferDescriptor intValue(int value)
    {
        this.ensureCapacity(GPUTypeSizes.INT_SIZE);
        this.buffer.putInt(value);
        return this;
    }

    public GPUBufferDescriptor floatValue(float value)
    {
        this.ensureCapacity(GPUTypeSizes.FLOAT_SIZE);
        this.buffer.putFloat(value);
        return this;
    }

    public GPUBufferDescriptor intArray(int[] values)
    {
        this.ensureCapacity(GPUTypeSizes.INT_SIZE * values.length);
        
        for (int v : values)
        {
            this.buffer.putInt(v);
        }

        return this;
    }

    public GPUBufferDescriptor floatArray(float[] values)
    {
        this.ensureCapacity(GPUTypeSizes.FLOAT_SIZE * values.length);

        for (float v : values)
        {
            this.buffer.putFloat(v);
        }
        
        return this;
    }

    public GPUBufferDescriptor vec2(float x, float y)
    {
        this.ensureCapacity(GPUTypeSizes.VEC2_SIZE);
        this.buffer.putFloat(x).putFloat(y);
        return this;
    }

    public GPUBufferDescriptor vec3(float x, float y, float z)
    {
        this.ensureCapacity(GPUTypeSizes.VEC3_SIZE);
        this.buffer.putFloat(x).putFloat(y).putFloat(z);
        return this;
    }

    public GPUBufferDescriptor vec4(float x, float y, float z, float w)
    {
        this.ensureCapacity(GPUTypeSizes.VEC4_SIZE);
        this.buffer.putFloat(x).putFloat(y).putFloat(z).putFloat(w);
        return this;
    }

    public GPUBufferDescriptor mat3(float[] values) throws IllegalArgumentException
    {
        if (values.length != 9)
        {
            throw new IllegalArgumentException("Array passed into mat3 must be of length 9");
        }

        this.ensureCapacity(GPUTypeSizes.MAT3_SIZE);
        
        for (float v : values)
        {
            this.buffer.putFloat(v);
        }

        return this;
    }

    public GPUBufferDescriptor mat4(float[] values) throws IllegalArgumentException
    {
        if (values.length != 16)
        {
            throw new IllegalArgumentException("Array passed into mat4 must be of length 16");
        }

        this.ensureCapacity(GPUTypeSizes.MAT4_SIZE);

        for (float v : values)
        {
            this.buffer.putFloat(v);
        }

        return this;
    }

    protected ByteBuffer buildBuffer() throws IllegalStateException
    {
        if (this.built)
        {
            throw new IllegalStateException("Can only call build() once");
        }

        this.buffer.flip();
        this.built = true;

        return this.buffer;
    }

    protected ByteBuffer getBuffer() throws IllegalStateException
    {
        if (!this.built)
        {
            throw new IllegalStateException("Can only call getBuffer() after calling build()");
        }

        return this.buffer;
    }
}
