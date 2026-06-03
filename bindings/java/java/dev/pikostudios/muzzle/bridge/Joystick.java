package dev.pikostudios.muzzle.bridge;

import java.io.IOException;
import java.util.Optional;

public final class Joystick
{
    private final JoystickState state;
    private final int slot;
    private final boolean isGamepad;
    private final String name;
    private final String guid;
    
    private Joystick(int slot, boolean isGamepad, String name, String guid)
    {
        this.state = new JoystickState();
        this.slot = slot;
        this.isGamepad = isGamepad;
        this.name = name;
        this.guid = guid;
    }

    public static Optional<Joystick> open(int slot) throws IllegalArgumentException
    {
        if (slot > 15)
        {
            throw new IllegalArgumentException("Invalid slot (valid slots are 0-15)");
        }

        return Optional.ofNullable(_open(slot));
    }

    public static native boolean exists(int slot);

    private static native Joystick _open(int slot);

    public int getSlot()
    {
        return this.slot;
    }

    public boolean isGamepad()
    {
        return this.isGamepad;
    }

    public String getName()
    {
        return this.name;
    }

    public String getGUID()
    {
        return this.guid;
    }

    public boolean exists()
    {
        return exists(this.slot);
    }

    public JoystickState queryState() throws IOException
    {
        if (!this._queryState(this.state))
        {
            throw new IOException("Joystick no longer valid (likely disconnected)");
        }
        
        return this.state;
    }

    private native boolean _queryState(JoystickState state);
}
