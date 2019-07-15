#ifndef _CONTROLLER_INPUT_DEVICE_H
#define _CONTROLLER_INPUT_DEVICE_H

#include "../../Engine/Input/InputDevice.h"
#include "SFML/Graphics.hpp"

class ControllerInputDevice :
	public InputDevice
{
public:
	ControllerInputDevice();
	~ControllerInputDevice();

	void ProcessInputs();

private:

};

#endif