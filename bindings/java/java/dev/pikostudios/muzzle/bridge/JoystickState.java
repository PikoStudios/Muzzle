package dev.pikostudios.muzzle.bridge;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class JoystickState implements AutoCloseable
{
    public enum HatState
    {
        CENTERED,
        UP,
        RIGHT,
        DOWN,
        LEFT,
        RIGHT_UP,
        RIGHT_DOWN,
        LEFT_UP,
        LEFT_DOWN;

        private static HatState of(byte value) throws IllegalArgumentException
        {
            return switch (value)
            {
                case 0 -> CENTERED;
                case 1 -> UP;
                case 2 -> RIGHT;
                case 4 -> DOWN;
                case 8 -> LEFT;
                case 2 | 1 -> RIGHT_UP;
                case 2 | 4 -> RIGHT_DOWN;
                case 8 | 1 -> LEFT_UP;
                case 8 | 4 -> LEFT_DOWN;
                default -> throw new IllegalArgumentException("Unknown hat state " + value);
            };
        }
    }
    
    private FloatBuffer axes;
    private ByteBuffer buttons;
    private ByteBuffer hats;
    private boolean closed;

    protected JoystickState()
    {
    }

    public float getAxis(int index) throws IllegalStateException, IndexOutOfBoundsException
    {
        this.throwOnClosed();
        return this.axes.get(index);
    }

    public boolean buttonPressed(int index) throws IllegalStateException, IndexOutOfBoundsException
    {
        this.throwOnClosed();
        return this.buttons.get(index) == 0 ? false : true;
    }

    public HatState getHatState(int index) throws IllegalStateException, IndexOutOfBoundsException
    {
        this.throwOnClosed();
        return HatState.of(this.hats.get(index));
    }

    public int getAxisCount() throws IllegalStateException
    {
        this.throwOnClosed();
        return this.axes.limit();
    }
    
    public int getButtonCount() throws IllegalStateException
    {
        this.throwOnClosed();
        return this.buttons.limit();
    }
    
    public int getHatCount() throws IllegalStateException
    {
        this.throwOnClosed();
        return this.hats.limit();
    }

    @Override
    public void close()
    {
        this.axes = null;
        this.buttons = null;
        this.hats = null;
        this.closed = true;
    }

    protected boolean isClosed()
    {
        return this.closed;
    }

    private void throwOnClosed() throws IllegalStateException
    {
        if (this.closed)
        {
            throw new IllegalStateException("Cannot use JoystickState object after it has been closed");
        }
    }

    private void open(ByteBuffer axesBuffer, ByteBuffer buttonsBuffer, ByteBuffer hatsBuffer)
    {
        this.axes = axesBuffer.order(ByteOrder.nativeOrder()).asFloatBuffer();
        this.buttons = buttonsBuffer.order(ByteOrder.nativeOrder());
        this.hats = hatsBuffer.order(ByteOrder.nativeOrder());
        this.closed = false;
    }
}
