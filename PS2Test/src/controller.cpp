#include <Arduino.h>
#include <PS2X_lib.h>

class ControllerState {
public:
    byte LY;
    byte LX;
    byte RY;
    byte RX;
};

class Controller {
private:
    PS2X ps2 = PS2X();
public:
    void Setup()
    {
        //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
        byte error = ps2.config_gamepad(13, 11, 10, 12, true, true);
        byte type = ps2.readType();
        //Serial.print("error:");
        //Serial.println(error);
        //Serial.print("type:");
        //Serial.println(type);
    }
    
    ControllerState Read()
    {
        ps2.read_gamepad(false, true);

        ControllerState state;

        state.LY = ps2.Analog(PSS_LY);
        state.LX = ps2.Analog(PSS_LX);
        state.RY = ps2.Analog(PSS_RY);
        state.RX = ps2.Analog(PSS_RX);

        if (state.LY == 255 && state.LX == 255 
            && state.RY == 255 && state.RX == 255)
        {
            state.LY = 128;
            state.LX = 128;
            state.RY = 128;
            state.RX = 128;        
        }
        
        return state;
    } 
};
