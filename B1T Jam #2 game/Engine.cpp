#include "Engine.h"
#include "Player.h"
#include "Text.h"
#include "ScrollingCredits.h"
#include "Plant.h"
#include "Alien.h"
#include "Item.h"
#include "AnimatedObject.h"
#include "StaticObject.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <map>
#include <vector>


std::map<std::string, Text> gameTexts;
std::map<std::string, ScrollingCredits> scrollingCreditsTexts;
std::map<std::string, AnimatedObject> animatedObjects;
std::map<std::string, Text> playerHUD;
std::map<std::string, StaticObject> staticObjects;

std::vector<Plant> plantsEntities;
std::vector<Alien> aliensEntities;
std::vector<Item> itemsEntities;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::RunEngine()
{
	Window::InitializeWindow();
	Player::InitializePlayer("./Textures/character.png"); // just to mock the player with a texture

	InitializeGameTexts();
	InitializeScrollingCreditsTexts();
	InitializeGameEntities();
	InitializeAnimatedObjects();
	InitializePlayerHUD();
	InitializeShopMenu();

	while (Window::GetIsRunning())
	{
		switch (Window::gameState)
		{
		case GameState::MainMenu:
			Window::RenderBeginFrame();

			Player::UpdatePlayer(); // Only for handling menu input

			gameTexts["mainMenuTitle"].RenderText();
			gameTexts["mainMenuContinue"].RenderText();
			gameTexts["mainMenuCredits"].RenderText();
			gameTexts["mainMenuQuit"].RenderText();

			Window::RenderEndFrame();
			break;

		case GameState::CreditsMenu:
			Window::RenderBeginFrame();

			Player::UpdatePlayer(); // Only for handling menu input

			gameTexts["creditsMenuTitle"].RenderText();

			scrollingCreditsTexts["ProgrammersText"].UpdateScrollingCredits();
			scrollingCreditsTexts["ProgrammersText"].RenderScrollingCredits();

			scrollingCreditsTexts["ProgrammersNamesText"].UpdateScrollingCredits();
			scrollingCreditsTexts["ProgrammersNamesText"].RenderScrollingCredits();

			scrollingCreditsTexts["AudioComposerText"].UpdateScrollingCredits();
			scrollingCreditsTexts["AudioComposerText"].RenderScrollingCredits();

			scrollingCreditsTexts["AudioComposerNameText"].UpdateScrollingCredits();
			scrollingCreditsTexts["AudioComposerNameText"].RenderScrollingCredits();

			scrollingCreditsTexts["ArtistText"].UpdateScrollingCredits();
			scrollingCreditsTexts["ArtistText"].RenderScrollingCredits();

			scrollingCreditsTexts["ArtistNameText"].UpdateScrollingCredits();
			scrollingCreditsTexts["ArtistNameText"].RenderScrollingCredits();

			CheckIfScrollingCreditsFinished();

			gameTexts["creditsMenuBack"].RenderText();

			Window::RenderEndFrame();
			break;

		case GameState::GameIntro:
			Window::RenderBeginFrame();

			Player::UpdatePlayer();
			// Player::RenderPlayer();

			gameTexts["gameIntro"].RenderText();
			gameTexts["gameEndIntro"].RenderText();

			Window::RenderEndFrame();
			break;

		case GameState::Playing:
			Window::RenderBeginFrame();

			Player::UpdatePlayer();
			//Player::RenderPlayer();

			if (Player::GetWaveFinishedChanging() && Player::GetLevelFinishedChanging())
			{
				// Render player HUD texts
				for (std::pair<std::string, Text> HUD_Map : playerHUD) HUD_Map.second.RenderText();

				if (!aliensEntities.empty())
				{
					// Loop through all the alien entities
					for (int i = 0; i < aliensEntities.size(); i++)
					{
						// Update and render all alien entities
						aliensEntities[i].update();
						aliensEntities[i].render();
					}
				}
				
				// Iterate through the alien elements
				for (std::vector<Alien>::iterator it = aliensEntities.begin(); it != aliensEntities.end();)
				{
					Alien alien = *it;

					// Destroy alien when health reaches 0 and delete them from the vector
					if (alien.GetAlienHealth() <= 0.0f)
					{
						alien.DestroyAlien();
						it = aliensEntities.erase(it);
					}
					else
					{
						++it;
					}
				}
			}

			Window::RenderEndFrame();
			break;

		case GameState::Paused:
			Window::RenderBeginFrame();

			Player::UpdatePlayer();

			gameTexts["pauseMenuTitle"].RenderText();
			gameTexts["pauseMenuResume"].RenderText();
			gameTexts["pauseMenuQuit"].RenderText();

			Window::RenderEndFrame();
			break;

		case GameState::Shopping:
			Window::RenderBeginFrame();

			Player::UpdatePlayer();

			IsMouseHovered();

			animatedObjects["BuyFlowerButton"].RenderAnimation();

			staticObjects["FlowerShopUI"].RenderStaticObject();
			gameTexts["playerCurrencyAmount"].RenderText();

			Window::RenderEndFrame();
			break;

		default:
			break;
		}
	}

	Window::DestroyWindow();
	Player::DestroyPlayer();

	// Destroy all mapped texts and clear all mapped elements as well
	for (std::pair<std::string, Text> textMap : gameTexts)
	{
		textMap.second.DestroyText();
		textMap.first.clear();
	}

	for (std::pair<std::string, ScrollingCredits> scrollingCreditsTextMap : scrollingCreditsTexts)
	{
		scrollingCreditsTextMap.second.DestroyScrollingCredits();
		scrollingCreditsTextMap.first.clear();
	}

	for (std::pair<std::string, AnimatedObject> animatedObjectMap : animatedObjects)
	{
		animatedObjectMap.second.~AnimatedObject();
		animatedObjectMap.first.clear();
	}

	for (std::pair<std::string, Text> HUD_Map : playerHUD)
	{
		HUD_Map.second.DestroyText();
		HUD_Map.first.clear();
	}

	// Destroy all alien entities
	for (int i = 0; i < aliensEntities.size(); i++)
	{
		aliensEntities[i].DestroyAlien();
	}

	// Clear all entities
	if (!aliensEntities.empty()) aliensEntities.clear();
	if (!plantsEntities.empty()) plantsEntities.clear();
	if (!itemsEntities.empty()) itemsEntities.clear();

	// Quit all SDL subsystems including SDL_TTF
	TTF_Quit();
	SDL_Quit();
}

void Engine::InitializeGameTexts()
{
	// Create main menu texts
	gameTexts["mainMenuTitle"].InitializeText("Veggie Vanguard",
		40.0f, { static_cast<float>(Window::GetWindowWidth() / 4.5f),
		static_cast<float>(Window::GetWindowHeight() / 30.0f) });

	gameTexts["mainMenuContinue"].InitializeText("Press SPACE to continue!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.75f),
		static_cast<float>(Window::GetWindowHeight() / 1.6f) });

	gameTexts["mainMenuCredits"].InitializeText("Press ENTER for credits!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.75f),
		static_cast<float>(Window::GetWindowHeight() / 1.4f) });

	gameTexts["mainMenuQuit"].InitializeText("Press ESCAPE to quit!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.75f),
		static_cast<float>(Window::GetWindowHeight() / 1.25f) });

	// Create game intro texts
	gameTexts["gameIntro"].InitializeText("Aliens from Planet Zog have discovered Earth's livestock and \ndecided they're"
		" the perfect energy source for their interstellar \nBBQ. Unfortunately for them, the local farmer has some friends"
		" \nin the garden... genetically engineered plants with unique \ncombat abilities, ready to defend the farm!",
		20.0f, { static_cast<float>(Window::GetWindowWidth() / 30.0f),
		static_cast<float>(Window::GetWindowHeight() / 3.0f) });

	gameTexts["gameEndIntro"].InitializeText("Press ENTER to continue!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 3.0f),
		static_cast<float>(Window::GetWindowHeight() / 1.2f) });

	// Create paused game texts
	gameTexts["pauseMenuTitle"].InitializeText("Pause Menu",
		40.0f, { static_cast<float>(Window::GetWindowWidth() / 3.1f),
		static_cast<float>(Window::GetWindowHeight() / 30.0f) });

	gameTexts["pauseMenuResume"].InitializeText("Press ESCAPE to resume!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.75f),
		static_cast<float>(Window::GetWindowHeight() / 1.4f) });

	gameTexts["pauseMenuQuit"].InitializeText("Press ENTER to quit!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.75f),
		static_cast<float>(Window::GetWindowHeight() / 1.2f) });

	// Create credits menu texts
	gameTexts["creditsMenuTitle"].InitializeText("Credits Menu",
		40.0f, { static_cast<float>(Window::GetWindowWidth() / 3.0f),
		static_cast<float>(Window::GetWindowHeight() / 30.0f) });

	gameTexts["creditsMenuBack"].InitializeText("Press ESCAPE to go back!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.75f),
		static_cast<float>(Window::GetWindowHeight() / 1.1f) });

	// Shop menu texts
	gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
		{ static_cast<float>(Window::GetWindowWidth() / 2.05f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
}

void Engine::InitializeScrollingCreditsTexts()
{
	scrollingCreditsTexts["ProgrammersText"].InitializeScrollingCredits("Programmers",
		20.0f, { static_cast<float>(Window::GetWindowWidth() / 2.5f),
		static_cast<float>(Window::GetWindowHeight() / 3.25f) });

	scrollingCreditsTexts["ProgrammersNamesText"].InitializeScrollingCredits("Osama Hussein\nSebastian Calabro",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.45f),
		static_cast<float>(Window::GetWindowHeight() / 2.5f) });

	scrollingCreditsTexts["AudioComposerText"].InitializeScrollingCredits("Sound/Music Composer",
		20.0f, { static_cast<float>(Window::GetWindowWidth() / 3.0f),
		static_cast<float>(Window::GetWindowHeight() / 1.75f) });

	scrollingCreditsTexts["AudioComposerNameText"].InitializeScrollingCredits("JaidenTfs",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.25f),
		static_cast<float>(Window::GetWindowHeight() / 1.5f) });

	scrollingCreditsTexts["ArtistText"].InitializeScrollingCredits("Pixel Artist",
		20.0f, { static_cast<float>(Window::GetWindowWidth() / 2.4f),
		static_cast<float>(Window::GetWindowHeight() * 0.85f) });

	scrollingCreditsTexts["ArtistNameText"].InitializeScrollingCredits("Space Frog \nMantis",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 2.3f),
		static_cast<float>(Window::GetWindowHeight() * 0.95f) });
}


void Engine::InitializeGameEntities()
{
	Plant plant1(PlantType::TomatoCannon);
	Plant plant2(PlantType::SunflowerShooter);

	Alien alien1(AlienType::GruntZogling);
	Alien alien2(AlienType::ShieldDrone);

	Item item1(ItemType::Seeds);
	Item item2(ItemType::Fertilizer);

	plantsEntities.push_back(plant1);
	plantsEntities.push_back(plant2);

	aliensEntities.push_back(alien1);
	aliensEntities.push_back(alien2);

	itemsEntities.push_back(item1);
	itemsEntities.push_back(item2);

#ifdef _DEBUG
	std::cout << "Entities Initialized " << std::endl;

	if (PlantType::TomatoCannon == plant1.getEntityID())
	{
		std::cout << "This plant is a Tomato cannon!: " << std::endl;
	}

	if (AlienType::GruntZogling == alien1.getEntityID())
	{
		std::cout << "This alien is an GruntZogling!: " << std::endl;
	}

	if (ItemType::Fertilizer == item2.getEntityID())
	{
		std::cout << "This item is a Fertilizer!: " << std::endl;
	}

	std::cout << "Plants count: " << plantsEntities.size() << std::endl;
	std::cout << "Aliens count: " << aliensEntities.size() << std::endl;
	std::cout << "Items count: " << itemsEntities.size() << std::endl;
#endif

}
void Engine::InitializeAnimatedObjects()
{
	// Shop menu buttons
	animatedObjects["BuyFlowerButton"].InitializeAnimation("Textures/Flower_Menu_animated_X.png");
}

void Engine::InitializePlayerHUD()
{
	playerHUD["PlayerScore"].InitializeText("Score: " + std::to_string(Player::currentPlayerScore), 20,
		{ Window::GetWindowWidth() / 160.0f, Window::GetWindowHeight() / 120.0f });

	playerHUD["LevelNumber"].InitializeText("Level: " + std::to_string(Player::GetLevelNumber()), 20, 
		{ Window::GetWindowWidth() / 160.0f, Window::GetWindowHeight() / 15.0f });

	playerHUD["WaveNumber"].InitializeText("Wave: " + std::to_string(Player::GetWaveNumber()), 20,
		{ Window::GetWindowWidth() / 160.0f, Window::GetWindowHeight() / 8.0f });
}

void Engine::InitializeShopMenu()
{
	// Shop menu UI
	staticObjects["FlowerShopUI"].InitializeStaticObject("Textures/Flower_ShopX.png",
		{ Window::GetWindowWidth() / 8.0f, Window::GetWindowHeight() / 600.0f }, { 3.5f, 3.0f });
}

void Engine::IsMouseHovered()
{
	// Check if mouse is hovered on the but flower button
	if (Player::GetMouseX() >= animatedObjects["BuyFlowerButton"].GetAnimationPosition().x + 12.5f && 
		Player::GetMouseX() <= animatedObjects["BuyFlowerButton"].GetAnimationPosition().x + 
		animatedObjects["BuyFlowerButton"].GetAnimationPosition().w - 15.0f && 
		Player::GetMouseY() >= animatedObjects["BuyFlowerButton"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["BuyFlowerButton"].GetAnimationPosition().y +
		animatedObjects["BuyFlowerButton"].GetAnimationPosition().h - 60.0f)
	{
		// If so, update the animation
		animatedObjects["BuyFlowerButton"].UpdateAnimation(7, 1, { Window::GetWindowWidth() / 4.0f,
			Window::GetWindowHeight() / 6.0f }, { 1.3f, 1.3f }, 1.0f);
	}

	else
	{
		// Otherwise, freeze the animation
		animatedObjects["BuyFlowerButton"].FreezeAnimation(7, 1, { Window::GetWindowWidth() / 4.0f,
			Window::GetWindowHeight() / 6.0f }, { 1.3f, 1.3f });
	}
}

void Engine::HandleMousePressedEvents()
{
	// Check if the player presses the mouse while hovering on the buy flower button
	if (Player::GetMouseX() >= animatedObjects["BuyFlowerButton"].GetAnimationPosition().x + 12.5f &&
		Player::GetMouseX() <= animatedObjects["BuyFlowerButton"].GetAnimationPosition().x +
		animatedObjects["BuyFlowerButton"].GetAnimationPosition().w - 15.0f &&
		Player::GetMouseY() >= animatedObjects["BuyFlowerButton"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["BuyFlowerButton"].GetAnimationPosition().y +
		animatedObjects["BuyFlowerButton"].GetAnimationPosition().h - 60.0f && Window::gameState == GameState::Shopping
		&& Player::GetPlayerCurrency() >= 200)
	{
#ifdef _DEBUG
		std::cout << "Bought flower\n";
#endif

		Player::SpendPlayerCurrency(200);
		Player::GoToNextLevel();

		Window::gameState = GameState::Playing;
	}

	// Otherwise if the player presses the mouse while hovering on the buy flower button, but don't have enough currency
	else if (Player::GetMouseX() >= animatedObjects["BuyFlowerButton"].GetAnimationPosition().x + 12.5f &&
		Player::GetMouseX() <= animatedObjects["BuyFlowerButton"].GetAnimationPosition().x +
		animatedObjects["BuyFlowerButton"].GetAnimationPosition().w - 15.0f &&
		Player::GetMouseY() >= animatedObjects["BuyFlowerButton"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["BuyFlowerButton"].GetAnimationPosition().y +
		animatedObjects["BuyFlowerButton"].GetAnimationPosition().h - 60.0f && Window::gameState == GameState::Shopping)
	{
		// TODO: Player doesn't have enough currency to buy flower
	}
}

void Engine::UpdatePlayerScore()
{
	playerHUD["PlayerScore"].InitializeText("Score: " + std::to_string(Player::currentPlayerScore),
		20, { Window::GetWindowWidth() / 160.0f, Window::GetWindowHeight() / 120.0f });
}

void Engine::UpdateCurrentLevelText()
{
	playerHUD["LevelNumber"].InitializeText("Level: " + std::to_string(Player::GetLevelNumber()), 20,
		{ Window::GetWindowWidth() / 160.0f, Window::GetWindowHeight() / 15.0f });
}

void Engine::UpdateCurrentWaveText()
{
	playerHUD["WaveNumber"].InitializeText("Wave: " + std::to_string(Player::GetWaveNumber()), 20,
		{ Window::GetWindowWidth() / 160.0f, Window::GetWindowHeight() / 8.0f });
}

void Engine::CheckIfScrollingCreditsFinished()
{
	// Reset scrolling credits texts once they reach above the screen
	if (scrollingCreditsTexts["ProgrammersText"].GetPositionY() < 0.0f &&
		scrollingCreditsTexts["ProgrammersNamesText"].GetPositionY() < 0.0f &&
		scrollingCreditsTexts["AudioComposerText"].GetPositionY() < 0.0f &&
		scrollingCreditsTexts["AudioComposerNameText"].GetPositionY() < 0.0f &&
		scrollingCreditsTexts["ArtistText"].GetPositionY() < 0.0f &&
		scrollingCreditsTexts["ArtistNameText"].GetPositionY() < 0.0f)
	{
		scrollingCreditsTexts["ProgrammersText"].ResetScrollingCredits();
		scrollingCreditsTexts["ProgrammersNamesText"].ResetScrollingCredits();
		scrollingCreditsTexts["AudioComposerText"].ResetScrollingCredits();
		scrollingCreditsTexts["AudioComposerNameText"].ResetScrollingCredits();
		scrollingCreditsTexts["ArtistText"].ResetScrollingCredits();
		scrollingCreditsTexts["ArtistNameText"].ResetScrollingCredits();
	}
}


void Engine::RestartCreditsMenu()
{
	scrollingCreditsTexts["ProgrammersText"].StartScrollingCredits();
	scrollingCreditsTexts["ProgrammersNamesText"].StartScrollingCredits();
	scrollingCreditsTexts["AudioComposerText"].StartScrollingCredits();
	scrollingCreditsTexts["AudioComposerNameText"].StartScrollingCredits();
	scrollingCreditsTexts["ArtistText"].StartScrollingCredits();
	scrollingCreditsTexts["ArtistNameText"].StartScrollingCredits();
}