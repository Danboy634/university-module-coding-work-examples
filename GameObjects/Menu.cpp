#include "Menu.h"

Menu::Menu()
	:m_EMenuOption(E_StartGame_Initialise),
	 options(false)
{
}

Menu::~Menu()
{
	SAFE_DELETE_PTR(pAudioManager); //Unsure if necessary, the Update call takes care of this but it works with it - So better safe, ay
}

void Menu::InitialiseText(const char* filename, const char* text, int textSize, sf::Color textColour, const int x, const int y, sf::Color textOutlineColour, float textOutlineThickness)
{
}

void Menu::InitialiseSprite(const char* filename, const int x, const int y, const int sizeX, const int sizeY)
{
}

void Menu::GetPosition(int & x, int & y)
{
}

void Menu::Initialise()
{
	// Initialises the window view
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	const sf::View view = pWindow->getView();

	// Initialises the mouse position relative to the window
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);
	sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

	// Initialises audio
	pAudioManager = C_SysContext::Get<AudioManager>();

	// Initialises switch
	switch (m_EMenuOption)
	{
	default:

		break;

	case E_StartGame_Initialise: // Main Menu
	
		Background_Sprite_Image.Initialise("Sprites/bg_menu_main.png", 0, 0, 1024, 768); // Creates menu background 
		Background_Box_Image.Initialise("Sprites/spr_menu_buttonMain_1.png", 0, 200, 50, 50);// Creates menu button
		Background_Box_Image_2.Initialise("Sprites/spr_menu_buttonMain_1.png", 0, 200, 50, 50); // Creates second menu button
		Background_Box_Image_3.Initialise("Sprites/spr_menu_buttonMain_1.png", 0, 200, 50, 50); // Creates third menu button

		Background_Box_Image.setPosition(0, 450); // Sets position of top menu button
		Background_Box_Image_2.setPosition(0, 550); // Sets position of middle menu button 
		Background_Box_Image_3.setPosition(0, 660); // Sets position of bottom menu button

		StartGame_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "Start Game", 40, sf::Color::Blue, 10, 453, sf::Color::White, 3); // Displays "Start Game" text
		Options_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "Options", 40, sf::Color::Blue, 10, 553, sf::Color::White, 3); // Displays the "Options" text
		QuitGame_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "Quit Game", 40, sf::Color::Blue, 10, 663, sf::Color::White, 3); // Displays the "Quit Game" text

		m_EMenuOption = E_StartGame_Update; // Goes to the start game update switch option

		break;

	case E_Quit: // Quit

		//exit game
		return exit(0);
		break;
	}
}

void Menu::Update()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	// Updates the window view
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	const sf::View view = pWindow->getView();

	// Updates the mouse position relative to the window
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);
	sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

	// Updates the audio
	pAudioManager->Update();


	// Update switch
	switch (m_EMenuOption)
	{
	default:

		break;

	case E_StartGame_Update: 
	{
		////////////////
		// Start Game //
		////////////////
				
		//controller input
		if (pInputDevice->GetButtonInput(E_DigitalInput_Start).OnPressed())
		{
			pAudioManager->PlaySoundFX("sounds/sfx_menu_click.wav");

			// Queue first level
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameStateTest* pGameStateTest = new GameStateTest;
			pGameStateManager->QueueGameState(pGameStateTest);
		}
		
		// Gets the position of background box image sprite
		if (((mousePosition.y > Background_Box_Image.getGlobalBounds().top) && (mousePosition.y < (Background_Box_Image.getGlobalBounds().top + Background_Box_Image.getGlobalBounds().height))) && ((mousePosition.x > Background_Box_Image.getGlobalBounds().left) && (mousePosition.x < (Background_Box_Image.getGlobalBounds().left + Background_Box_Image.getGlobalBounds().width))))
		{
			StartGame_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "Start Game", 40, sf::Color::Blue, 10, 453, sf::Color::White, 3); // Displays "Start Game" text

			// When the mouse is in sprite bounds and clicked...
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Clicking the mouse starts the game
			{
				pAudioManager->PlaySoundFX("sounds/sfx_menu_click.wav"); // Play Sound effect
				
				// Queue GameStateTest
				GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
				GameStateTest* pGameStateTest = new GameStateTest;
				pGameStateManager->QueueGameState(pGameStateTest);
			}

		}

		/////////////
		// Options //
		/////////////

		//controller input
		if (pInputDevice->GetButtonInput(E_DigitalInput_Back).OnPressed())
		{
			Background_Box_Image.RemoveSprite(); // Removes top menu button
			Background_Box_Image_2.RemoveSprite(); // Removes middle menu button
			Background_Box_Image_3.RemoveSprite(); // Removes bottom menu button
			Background_Sprite_Image.RemoveSprite();
			StartGame_Text.RemoveText(); // Removes "Start Game" text
			Options_Text.RemoveText(); // Removes "Options" text
			QuitGame_Text.RemoveText(); // Removes "Quit Game" text

			Background_Sprite_Image2.Initialise("sprites/bg_menu_settings.png", 0, 0, 1024, 768); //Initialises options menu background
			Background_Box_Options.Initialise("Sprites/spr_menu_button_small_0.png", 0, 200, 50, 50);
			Options_Return_Text.InitialiseMenu("fonts/Grand9K Pixel_0.TTF", "Return \t\t\t\t\t\t\t\t\t\t\t Controls", 40, sf::Color::Black, 10, 63, sf::Color::White, 3); // Initialises return text 
			background_Sprite_Image3.Initialise("Sprites/controls1.png", 0, 0, 1024, 768);
			Background_Box_Options.setPosition(0, 60);
			background_Sprite_Image3.setPosition(70, 150);
			pAudioManager->PlaySoundFX("sounds/sfx_menu_pause.wav"); // Play sound effect

			m_EMenuOption = E_Options_Update; // goes to options state

		}

		// Gets the position of background box image sprite
		if (((mousePosition.y > Background_Box_Image_2.getGlobalBounds().top) && (mousePosition.y < (Background_Box_Image_2.getGlobalBounds().top + Background_Box_Image_2.getGlobalBounds().height))) && ((mousePosition.x > Background_Box_Image_2.getGlobalBounds().left) && (mousePosition.x < (Background_Box_Image_2.getGlobalBounds().left + Background_Box_Image_2.getGlobalBounds().width))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Clicking mouse goes to options
			{
				Background_Sprite_Image.RemoveSprite();
				Background_Box_Image.RemoveSprite(); // Removes top menu button
				Background_Box_Image_2.RemoveSprite(); // Removes middle menu button
				Background_Box_Image_3.RemoveSprite(); // Removes bottom menu button
				StartGame_Text.RemoveText(); // Removes "Start Game" text
				Options_Text.RemoveText(); // Removes "Options" text
				QuitGame_Text.RemoveText(); // Removes "Quit Game" text

				Background_Sprite_Image2.Initialise("sprites/bg_menu_settings.png", 0, 0, 1024, 768); //Initialises options menu background
				Background_Box_Options.Initialise("Sprites/spr_menu_button_small_0.png", 0, 200, 50, 50);
				Options_Return_Text.InitialiseMenu("fonts/Grand9K Pixel_0.TTF", "Return \t\t\t\t\t\t\t\t\t\t\t Controls", 40, sf::Color::Black, 10, 63, sf::Color::White, 3); // Initialises return text 
				background_Sprite_Image3.Initialise("Sprites/controls1.png", 0, 0, 1024, 768);
				Background_Box_Options.setPosition(0, 60);
				background_Sprite_Image3.setPosition(70, 150);
				pAudioManager->PlaySoundFX("sounds/sfx_menu_pause.wav"); // Play sound effect

				m_EMenuOption = E_Options_Update; // goes to options state
			}
		}

		///////////////
		// Exit Game //
		///////////////

		//controller input
		if (pInputDevice->GetButtonInput(E_DigitalInput_B).OnPressed())
		{
			m_EMenuOption = E_Quit;
		}

		// Gets the position of background box image sprite
		if (((mousePosition.y > Background_Box_Image_3.getGlobalBounds().top) && (mousePosition.y < (Background_Box_Image_3.getGlobalBounds().top + Background_Box_Image_3.getGlobalBounds().height))) && ((mousePosition.x > Background_Box_Image_3.getGlobalBounds().left) && (mousePosition.x < (Background_Box_Image_3.getGlobalBounds().left + Background_Box_Image_3.getGlobalBounds().width))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Clicking mouse quits game
			{
				pAudioManager->PlaySoundFX("sounds/sfx_coin1.wav"); // Play sound effect
				m_EMenuOption = E_Quit; // Quit game state
			}
		}

	}
	break;

	case E_Options_Update: // Options update

	//	InitialiseOptions(); // calls function

		//controller input
		if (pInputDevice->GetButtonInput(E_DigitalInput_Back).OnPressed()) //Goes back to Main Menu when pressed
		{
			pAudioManager->PlaySoundFX("sounds/sfx_menu_click.wav"); // Play sound effect

			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameStateMenu* pGameStateMenu = new GameStateMenu;
			pGameStateManager->QueueGameState(pGameStateMenu);
		}

		// Gets the position of background box image sprite
		if (((mousePosition.y > Background_Box_Options.getGlobalBounds().top) && (mousePosition.y < (Background_Box_Options.getGlobalBounds().top + Background_Box_Options.getGlobalBounds().height))) && ((mousePosition.x > Background_Box_Options.getGlobalBounds().left) && (mousePosition.x < (Background_Box_Options.getGlobalBounds().left + Background_Box_Options.getGlobalBounds().width))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Goes back to Main Menu when clicked
			{
				pAudioManager->PlaySoundFX("sounds/sfx_menu_click.wav"); // Play sound effect
				
				GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
				GameStateMenu* pGameStateMenu = new GameStateMenu;
				pGameStateManager->QueueGameState(pGameStateMenu);
			}
		}
	break;

	case E_Quit:

		//exits game
		return exit(0);

		break;
	}
}

void Menu::OnCollision(Collider2D* pCollider2D)
{
}