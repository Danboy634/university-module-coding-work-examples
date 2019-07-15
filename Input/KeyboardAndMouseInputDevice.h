#ifndef _KEYBOARD_AND_MOUSE_INPUT_DEVICE_H
#define _KEYBOARD_AND_MOUSE_INPUT_DEVICE_H

#include "../../Engine/Input/InputDevice.h"
#include "SFML/Graphics.hpp"

class KeyboardAndMouseInputDevice :
	public InputDevice
{
public:
	KeyboardAndMouseInputDevice();
	~KeyboardAndMouseInputDevice();

	void ProcessInputs();

private:

};
#endif 