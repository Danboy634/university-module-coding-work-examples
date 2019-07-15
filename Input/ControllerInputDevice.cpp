#include "ControllerInputDevice.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Core/MathHelpers.h"

ControllerInputDevice::ControllerInputDevice()
{
	m_DeviceType = E_INPUT_CONTROLLER;
}

ControllerInputDevice::~ControllerInputDevice()
{
}

void ControllerInputDevice::ProcessInputs()
{
	sf::Vector2f leftSticksPos((sf::Joystick::getAxisPosition(0, sf::Joystick::X)), (sf::Joystick::getAxisPosition(0, sf::Joystick::Y)));
	sf::Vector2f RightSticksPos((sf::Joystick::getAxisPosition(0, sf::Joystick::U)), (sf::Joystick::getAxisPosition(0, sf::Joystick::R)));

	//move Down
	if (leftSticksPos.y > 25)
	{
		this->m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(false);
	}

	//move Up
	if (leftSticksPos.y < -25)
	{
		this->m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(false);
	}

	//move Left
	if (leftSticksPos.x < -25)
	{
		this->m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(false);
	}

	//move Right
	if (leftSticksPos.x > 25)
	{
		this->m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(false);
	}

	//'a' button - Sprint
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::X))
	{
		this->m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(false);
	}

	//'x' button - reload
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::Z))
	{
		this->m_DigitalInputs[E_DigitalInput_X].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_X].SetPressed(false);
	}

	//triggers - shooting
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) > 15 || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) < -15)
	{
		this->m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(1.f);
	}
	else
	{
		this->m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(0.f);
	}

	//'y' button - switch between weapons
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::R))
	{
		this->m_DigitalInputs[E_DigitalInput_Y].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_Y].SetPressed(false);
	}

	//start button - start game/pause game
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::PovY))
	{
		this->m_DigitalInputs[E_DigitalInput_Start].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_Start].SetPressed(false);
	}

	//back button - show instructions in the menu
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::PovX))
	{
		this->m_DigitalInputs[E_DigitalInput_Back].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_Back].SetPressed(false);
	}

	//'b' button - exit game/interaction
	if (sf::Joystick::isButtonPressed(0, sf::Joystick::Y))
	{
		this->m_DigitalInputs[E_DigitalInput_B].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_B].SetPressed(false);
	}

	m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(RightSticksPos.x);
	m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(RightSticksPos.y);
}
