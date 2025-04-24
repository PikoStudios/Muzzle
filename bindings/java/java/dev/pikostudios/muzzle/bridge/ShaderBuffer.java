package dev.pikostudios.muzzle.bridge;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ShaderBuffer
{
    public static final int INT_SIZE = 4;
    public static final int FLOAT_SIZE = 4;
    public static final int VEC2_SIZE = FLOAT_SIZE * 2;
    public static final int VEC3_SIZE = FLOAT_SIZE * 3;
    public static final int VEC4_SIZE = FLOAT_SIZE * 4;
    public static final int MAT3_SIZE = FLOAT_SIZE * 3 * 3;
    public static final int MAT4_SIZE = FLOAT_SIZE * 4 * 4;

    public static class Builder
    {
        private static final int BUFFER_REALLOCATION_PADDING = 128;

        private int index;
        private ByteBuffer buffer;
        private boolean built;

        private Builder(int index)
        {
            this.index = index;
            this.buffer = ByteBuffer.allocateDirect(0).order(ByteOrder.nativeOrder());
            this.built = false;
        }

        private void ensureCapacity(int bytes)
        {
            if (this.buffer.remaining() < bytes)
            {
                ByteBuffer b = ByteBuffer.allocateDirect(this.buffer.position() + bytes + BUFFER_REALLOCATION_PADDING).order(ByteOrder.nativeOrder());
                this.buffer.flip();
                b.put(this.buffer);
                this.buffer = b;
            }
        }

        public Builder intValue(int value)
        {
            this.ensureCapacity(INT_SIZE);
            this.buffer.putInt(value);
            return this;
        }

        public Builder floatValue(float value)
        {
            this.ensureCapacity(FLOAT_SIZE);
            this.buffer.putFloat(value);
            return this;
        }

        public Builder intArray(int[] values)
        {
            this.ensureCapacity(INT_SIZE * values.length);

            for (int v : values)
            {
                this.buffer.putInt(v);
            }

            return this;
        }

        public Builder floatArray(float[] values)
        {
            this.ensureCapacity(FLOAT_SIZE * values.length);

            for (float v : values)
            {
                this.buffer.putFloat(v);
            }

            return this;
        }

        public Builder vec2(float x, float y)
        {
            this.ensureCapacity(VEC2_SIZE);
            this.buffer.putFloat(x).putFloat(y);
            return this;
        }

        public Builder vec3(float x, float y, float z)
        {
            this.ensureCapacity(VEC3_SIZE);
            this.buffer.putFloat(x).putFloat(y).putFloat(z);
            return this;
        }

        public Builder vec4(float x, float y, float z, float w)
        {
            this.ensureCapacity(VEC4_SIZE);
            this.buffer.putFloat(x).putFloat(y).putFloat(z).putFloat(w);
            return this;
        }

        public Builder mat3(float[] values)
        {
            if (values.length != 9)
            {
                throw new IllegalArgumentException("Array passed into mat3 must be of length 9");
            }

            this.ensureCapacity(MAT3_SIZE);

            for (float v : values)
            {
                this.buffer.putFloat(v);
            }

            return this;
        }

        public Builder mat4(float[] values)
        {
            if (values.length != 16)
            {
                throw new IllegalArgumentException("Array passed into mat4 must be of length 16");
            }

            this.ensureCapacity(MAT4_SIZE);

            for (float v : values)
            {
                this.buffer.putFloat(v);
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
