package dev.pikostudios.muzzle.bridge;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import dev.pikostudios.muzzle.bridge.GPUBufferDescriptor;

public class ShaderBuffer
{
    public static class Builder extends GPUBufferDescriptor
    {
        private int index;

        private Builder(int index)
        {
            super();
            this.index = index;
        }

        @Override
        public GPUBufferDescriptor vec3(float x, float y, float z)
        {
            // Shader Buffers in Muzzle are assumed to be std430
            this.ensureCapacity(GPUTypeSizes.VEC3_STD430_SIZE);
            this.buffer.putFloat(x).putFloat(y).putFloat(z).putFloat(0f); // 0 for padding
            return this;
        }

        @Override
        public GPUBufferDescriptor mat3(float[] values) throws IllegalArgumentException
        {
            if (values.length != 9)
            {
                throw new IllegalArgumentException("Array passed into mat3 must be of length 9");
            }

            this.ensureCapacity(GPUTypeSizes.MAT3_STD430_SIZE);

            for (int i = 0; i < values.length; i += 3)
            {
                this.buffer.putFloat(values[i+0]);
                this.buffer.putFloat(values[i+1]);
                this.buffer.putFloat(values[i+2]);
                this.buffer.putFloat(0); // Padding
            }

            return this;
        }

        public ShaderBuffer build() throws IllegalArgumentException, IllegalStateException
        {
            if (this.built)
            {
                throw new IllegalStateException("Can only call getData() or build() once");
            }

            if (this.index == -1)
            {
                throw new IllegalArgumentException("Cannot call build() on a Builder created from ShaderBuffer.builder()");
            }

            this.buffer.flip();
            this.built = true;

            return ShaderBuffer.create(this.index, this.buffer, this.buffer.limit());
        }

        private ByteBuffer getData() throws IllegalStateException
        {
            if (this.built)
            {
                throw new IllegalStateException("Can only call getData() or build() once");
            }

            this.buffer.flip();
            this.built = true;

            return this.buffer;
        }
    }

    private int id;
    private int index;

    private ShaderBuffer(int id, int index)
    {
        this.id = id;
        this.index = index;
    }

    private static native ShaderBuffer create(int index, ByteBuffer data, long size);

    public static native ShaderBuffer createEmpty(int index);

    public static Builder create(int index)
    {
        return new Builder(index);
    }

    public static Builder builder()
    {
        return new Builder(-1);
    }

    public void upload(Builder dataBuilder, long offset)
    {
        ByteBuffer b = dataBuilder.getData();
        this.upload(b, b.limit(), offset);
    }

    public native void unload();
    public native void resize(long size);

    private native void upload(ByteBuffer data, long size, long offset);
}
