#include "WeaponCrosshair.h"
#include "SFML/Graphics.hpp"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Renderer/WindowManager.h"

#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Core/MathHelpers.h"

WeaponCrosshair::WeaponCrosshair()
{
}

WeaponCrosshair::~WeaponCrosshair()
{
}

void WeaponCrosshair::Initialise()
{

}

void WeaponCrosshair::Initialise(char* filename)
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	GameObject* pPlayerObject = pGameState->GetPlayer();

	if (pInputDevice->GetInputDeviceType() == E_INPUT_CONTROLLER)
	{
		float thumbXPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();
		float thumbYPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue();

		sf::Vector2f forwards(thumbXPos, thumbYPos);
		forwards = MathHelpers::Normalise(forwards);

		forwards *= 300.f;
		int posX = 0;
		int posY = 0;
		pPlayerObject->GetPosition(posX, posY);

		sf::Vector2f aimingVector((float)posX, (float)posY);
		aimingVector += forwards;

		m_Sprite.Initialise(filename, (int)aimingVector.x, (int)aimingVector.y, 2, 2);
	}
	else if (pInputDevice->GetInputDeviceType() == E_INPUT_KEYBOARD)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		sf::RenderWindow* pWindow = pWindowManager->GetWindow();
		const sf::View view = pWindow->getView();

		sf::Vector2i mousePos = sf::Mouse::getPosition(*pWindow);

		//get mouse world position relative to the screen game world
		sf::Vector2f mouseWorldPos(mousePos.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePos.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

		//create crosshair sprite at mouse position
		m_Sprite.Initialise(filename, (int)mouseWorldPos.x, (int)mouseWorldPos.y, 2, 2);
	}
}

void WeaponCrosshair::Update()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pGameState = pGameStateManager->GetCurrentGameState();

	GameObject* pPlayerObject = pGameState->GetPlayer();

	if (pInputDevice->GetInputDeviceType() == E_INPUT_CONTROLLER)
	{
		float thumbXPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();
		float thumbYPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue();

		sf::Vector2f forwards(thumbXPos, thumbYPos);
		forwards = MathHelpers::Normalise(forwards);

		forwards *= 300.f;
		int posX = 0;
		int posY = 0;
		pPlayerObject->GetPosition(posX, posY);

		sf::Vector2f aimingVector((float)posX, (float)posY);
		aimingVector += forwards;

		m_Sprite.setPosition(aimingVector.x, aimingVector.y);
	}
	else if (pInputDevice->GetInputDeviceType() == E_INPUT_KEYBOARD)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		sf::RenderWindow* pWindow = pWindowManager->GetWindow();
		const sf::View view = pWindow->getView();

		sf::Vector2i mousePos = sf::Mouse::getPosition(*pWindow);

		//get mouse world position relative to the screen game world
		sf::Vector2f mouseWorldPos(mousePos.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePos.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

		//create crosshair sprite at mouse position
		m_Sprite.setPosition(mouseWorldPos.x, mouseWorldPos.y);
	}
}

void WeaponCrosshair::GetPosition(int& x, int& y)
{
	x = (int)m_Sprite.getPosition().x;
	y = (int)m_Sprite.getPosition().y;
}