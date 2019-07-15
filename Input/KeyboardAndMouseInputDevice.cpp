#include "KeyboardAndMouseInputDevice.h"
#include "SFML/Graphics.hpp"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/Core/MathHelpers.h"

KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{
	m_DeviceType = E_INPUT_KEYBOARD;
}

KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{
}

void KeyboardAndMouseInputDevice::ProcessInputs()
{
	//Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(false);
	}

	//Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(false);
	}

	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(false);
	}

	//Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(false);
	}

	//Shift-Thumbstick
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		this->m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(false);
	}

	//Y Button
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->m_DigitalInputs[E_DigitalInput_X].SetPressed(true);
	}
	else
	{
		this->m_DigitalInputs[E_DigitalInput_X].SetPressed(false);
	}

	//RightTrigger
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(1.f);
	}
	else
	{
		this->m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(0.f);
	}

	m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0.0f);
	m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0.0f);

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	GameObject* pPlayerObject = pGameState->GetPlayer();
	if (pPlayerObject)
	{
		int playerPosX = 0;
		int playerPosY = 0;

		pPlayerObject->GetPosition(playerPosX, playerPosY);

		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		sf::RenderWindow* pWindow = pWindowManager->GetWindow();

		const sf::View view = pWindow->getView();

		//get the mouse position relative to the window
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);

		//get the mouse world position
		sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

		sf::Vector2f distance((float)mouseWorldPos.x - (float)playerPosX, (float)mouseWorldPos.y - (float)playerPosY);

		distance = MathHelpers::Normalise(distance);

		m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(distance.x);
		m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(distance.y);
	}
	else
	{
		m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0.0f);
		m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0.0f);
	}

	m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(sf::Mouse::isButtonPressed(sf::Mouse::Left) ? 1.0f : 0.0f);
}