#include "Engine.h"
#include "Player.h"
#include "Text.h"
#include "ScrollingCredits.h"
#include "PlantTower.h"
#include "Alien.h"
#include "GruntZogling.h"
#include "ShieldDrone.h"
#include "BigZogling.h"
#include "StunSporeling.h"
#include "GoliathWalker.h"
#include "Item.h"
#include "AnimatedObject.h"
#include "StaticObject.h"
#include "Shovel.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <map>
#include <vector>


std::map<std::string, Text> gameTexts;
std::map<std::string, ScrollingCredits> scrollingCreditsTexts;
std::map<std::string, AnimatedObject> animatedObjects;
std::map<std::string, Text> playerHUD;
std::map<std::string, StaticObject> staticObjects;

// Plants
std::vector<PlantTower> plantsEntities;

// Aliens
std::vector<std::unique_ptr<Alien>> aliensEntities;


// Items
std::vector<Item> itemsEntities;

// Shovel
Shovel shovel;

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

				IterateAliens();

				shovel.update();

				/*for (int i = 0; i < aliensEntities.size(); i++)
				{
					shovel.collision(aliensEntities[i].get()); // test shovel collision with aliens
				}*/

				for (auto it = aliensEntities.begin(); it != aliensEntities.end();)
				{
					Alien* alien = it->get();

					// Destroy aliens for testing when shovel hovers on them
					if (shovel.shouldDestroyEntity(alien))
					{
						alien->DestroyAlien();
						it = aliensEntities.erase(it);
					}
					else
					{
						++it;
					}
				}

				shovel.render();
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
			SwitchFlowerUpgrades();

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
		aliensEntities[i].get()->DestroyAlien();
	}

	shovel.DestroyShovel();

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
	PlantTower plant1(PlantType::TomatoCannon);
	PlantTower plant2(PlantType::SunflowerShooter);

	GruntZogling alien1;
    ShieldDrone alien2;
    BigZogling alien3;
    StunSporeling alien4;
    GoliathWalker alien5;

	Item item1(ItemType::Seeds);
	Item item2(ItemType::Fertilizer);

	plantsEntities.push_back(plant1);
	plantsEntities.push_back(plant2);

	aliensEntities.push_back(std::make_unique<GruntZogling>());
	aliensEntities.push_back(std::make_unique<ShieldDrone>());
	// aliensEntities.push_back(std::make_unique<BigZogling>()); // they chrash because not having texture loaded, maybe we need some more validations 
	// aliensEntities.push_back(std::make_unique<StunSporeling>());
	// aliensEntities.push_back(std::make_unique<GoliathWalker>());

	itemsEntities.push_back(item1);
	itemsEntities.push_back(item2);

	// Shovel entity initialization
	shovel.InitializeShovel({ Window::GetWindowWidth() / 1.2f, Window::GetWindowHeight() / 100.0f });

#ifdef _DEBUG
	std::cout << "Entities Initialized " << std::endl;

	if (PlantType::TomatoCannon == plant1.getEntityID())
	{
		std::cout << "This plant is a Tomato cannon!: " << std::endl;
	}

	if (AlienType::GruntZogling == alien1.getAlienID())
	{
		std::cout << "This alien is an GruntZogling!: " << std::endl;
	}

	if (ItemType::Fertilizer == item2.getEntityID())
	{
		std::cout << "This item is a Fertilizer!: " << std::endl;
	}

	std::cout << "Plants count: " << plantsEntities.size() << std::endl;

	// Print different alien entities
	std::cout << "Aliens count: " << aliensEntities.size() << std::endl;
	// std::cout << "Grunt zogling aliens count: " << shieldDroneAliens.size() << std::endl;
	// std::cout << "Shield drone aliens count: " << shieldDroneAliens.size() << std::endl;
	// std::cout << "Big zogling aliens count: " << bigZoglingAliens.size() << std::endl;
	// std::cout << "Stun sporeling aliens count: " << stunSporelingAliens.size() << std::endl;
	// std::cout << "Goliath walker aliens count: " << goliathWalkerAliens.size() << std::endl;

	std::cout << "Items count: " << itemsEntities.size() << std::endl;
#endif

}
void Engine::InitializeAnimatedObjects()
{
	// Shop menu buttons
	animatedObjects["BuyFlowerButton1"].InitializeAnimation("Textures/Flower_Menu_animated_X.png");
	animatedObjects["SellFlowerButton1"].InitializeAnimation("Textures/Flower_Menu_animated_X.png");
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
	if (Player::GetMouseX() >= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().x + 12.5f && 
		Player::GetMouseX() <= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().x + 
		animatedObjects["BuyFlowerButton1"].GetAnimationPosition().w - 15.0f && 
		Player::GetMouseY() >= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().y +
		animatedObjects["BuyFlowerButton1"].GetAnimationPosition().h - 60.0f && Player::flowerUpgrade == 0)
	{
		// If so, update the animation
		animatedObjects["BuyFlowerButton1"].UpdateAnimation(7, 1, { Window::GetWindowWidth() / 4.0f,
			Window::GetWindowHeight() / 6.0f }, { 1.3f, 1.3f }, 1.0f);
	}

	else
	{
		// Otherwise, freeze the animation
		animatedObjects["BuyFlowerButton1"].FreezeAnimation(7, 1, { Window::GetWindowWidth() / 4.0f,
			Window::GetWindowHeight() / 6.0f }, { 1.3f, 1.3f });
	}

	// Sell flower logic
	if (Player::GetMouseX() >= animatedObjects["SellFlowerButton1"].GetAnimationPosition().x + 12.5f &&
		Player::GetMouseX() <= animatedObjects["SellFlowerButton1"].GetAnimationPosition().x +
		animatedObjects["SellFlowerButton1"].GetAnimationPosition().w - 15.0f &&
		Player::GetMouseY() >= animatedObjects["SellFlowerButton1"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["SellFlowerButton1"].GetAnimationPosition().y +
		animatedObjects["SellFlowerButton1"].GetAnimationPosition().h - 60.0f && Player::flowerUpgrade == 1)
	{
		// If so, update the animation
		animatedObjects["SellFlowerButton1"].UpdateAnimation(7, 1, { Window::GetWindowWidth() / 2.0f,
			Window::GetWindowHeight() / 6.0f }, { 1.3f, 1.3f }, 1.0f);
	}

	else
	{
		// Otherwise, freeze the animation
		animatedObjects["SellFlowerButton1"].FreezeAnimation(7, 1, { Window::GetWindowWidth() / 2.0f,
			Window::GetWindowHeight() / 6.0f }, { 1.3f, 1.3f });
	}
}

void Engine::HandleMousePressedEvents()
{
	// Check if the player presses the mouse while hovering on the buy flower button
	if (Player::GetMouseX() >= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().x + 12.5f &&
		Player::GetMouseX() <= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().x +
		animatedObjects["BuyFlowerButton1"].GetAnimationPosition().w - 15.0f &&
		Player::GetMouseY() >= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().y +
		animatedObjects["BuyFlowerButton1"].GetAnimationPosition().h - 60.0f && Window::gameState == GameState::Shopping
		&& Player::GetPlayerCurrency() >= 200 && Player::flowerUpgrade == 0)
	{
#ifdef _DEBUG
		std::cout << "Bought flower\n";
#endif

		Player::flowerUpgrade = 1;

		Player::SpendPlayerCurrency(200);
		UpdatePlayerCurrencyText();

		//Player::GoToNextLevel();

		//Window::gameState = GameState::Playing;
	}

	// Otherwise if the player presses the mouse while hovering on the buy flower button, but don't have enough currency
	else if (Player::GetMouseX() >= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().x + 12.5f &&
		Player::GetMouseX() <= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().x +
		animatedObjects["BuyFlowerButton1"].GetAnimationPosition().w - 15.0f &&
		Player::GetMouseY() >= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["BuyFlowerButton1"].GetAnimationPosition().y +
		animatedObjects["BuyFlowerButton1"].GetAnimationPosition().h - 60.0f && Window::gameState == GameState::Shopping)
	{
		// TODO: Player doesn't have enough currency to buy flower
	}

	// Check if the player presses the mouse while hovering on the sell flower button
	if (Player::GetMouseX() >= animatedObjects["SellFlowerButton1"].GetAnimationPosition().x + 12.5f &&
		Player::GetMouseX() <= animatedObjects["SellFlowerButton1"].GetAnimationPosition().x +
		animatedObjects["SellFlowerButton1"].GetAnimationPosition().w - 15.0f &&
		Player::GetMouseY() >= animatedObjects["SellFlowerButton1"].GetAnimationPosition().y + 25.0f &&
		Player::GetMouseY() <= animatedObjects["SellFlowerButton1"].GetAnimationPosition().y +
		animatedObjects["SellFlowerButton1"].GetAnimationPosition().h - 60.0f && Window::gameState == GameState::Shopping
		&& Player::flowerUpgrade == 1)
	{
#ifdef _DEBUG
		std::cout << "Sold flower\n";
#endif

		Player::flowerUpgrade = 0;

		Player::EarnPlayerCurrency(200);

		UpdatePlayerCurrencyText();
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

void Engine::UpdatePlayerCurrencyText()
{
	if (Player::GetPlayerCurrency() < 10)
	{
		gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
			{ static_cast<float>(Window::GetWindowWidth() / 2.05f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
	}

	else if (Player::GetPlayerCurrency() >= 10 && Player::GetPlayerCurrency() < 100)
	{
		gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
			{ static_cast<float>(Window::GetWindowWidth() / 2.08f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
	}

	else if (Player::GetPlayerCurrency() >= 100 && Player::GetPlayerCurrency() < 1000)
	{
		gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
			{ static_cast<float>(Window::GetWindowWidth() / 2.11f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
	}

	else if (Player::GetPlayerCurrency() >= 1000 && Player::GetPlayerCurrency() < 10000)
	{
		gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
			{ static_cast<float>(Window::GetWindowWidth() / 2.14f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
	}

	else if (Player::GetPlayerCurrency() >= 10000 && Player::GetPlayerCurrency() < 100000)
	{
		gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
			{ static_cast<float>(Window::GetWindowWidth() / 2.17f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
	}

	else if (Player::GetPlayerCurrency() >= 100000 && Player::GetPlayerCurrency() < 1000000)
	{
		gameTexts["playerCurrencyAmount"].InitializeText("$" + std::to_string(Player::GetPlayerCurrency()), 25.0f,
			{ static_cast<float>(Window::GetWindowWidth() / 2.2f), static_cast<float>(Window::GetWindowHeight() / 1.2f) });
	}
}

void Engine::HasShovel()
{
	shovel.HandleShovel();
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

void Engine::SwitchFlowerUpgrades()
{
	switch (Player::flowerUpgrade)
	{
	case 0:
		animatedObjects["BuyFlowerButton1"].RenderAnimation(false);
		animatedObjects["SellFlowerButton1"].RenderAnimation(true);

		break;

	case 1:
		animatedObjects["BuyFlowerButton1"].RenderAnimation(true);
		animatedObjects["SellFlowerButton1"].RenderAnimation(false);

		break;

	default:
		break;
	}
}

void Engine::IterateAliens()
{

	if (!aliensEntities.empty())
	{
		// Loop through all the alien entities
		for (int i = 0; i < aliensEntities.size(); i++)
		{
			// Update and render all alien entities
			aliensEntities[i].get()->update();
			
			switch (aliensEntities[i].get()->GetCurrentDirectionIndex())
			{
			case 0:
				aliensEntities[i].get()->moveEntity(
					{ Window::GetWindowWidth() / 5.555f, Window::GetWindowHeight() / 1.875f }, 
					{ Window::GetWindowWidth() / 5.555f, Window::GetWindowHeight() / 9.375f });

				break;

			case 1:
				aliensEntities[i].get()->moveEntity(
					{ Window::GetWindowWidth() / 2.622f, Window::GetWindowHeight() / 1.875f }, 
					{ Window::GetWindowWidth() / 5.555f, Window::GetWindowHeight() / 1.875f });

				break;

			default:
				break;
			}

			aliensEntities[i].get()->render();
		}
	}

	// Iterate through the alien elements
	for (auto it = aliensEntities.begin(); it != aliensEntities.end();)
	{
		Alien* alien = it->get();

		// Destroy grunt zogling alien when they're dead and delete them from the vector
		if (alien->getIsDead() && alien->getAlienID() == AlienType::GruntZogling && 
			alien->getDeathAnimationTime() >= 8.0f)
		{
			alien->DestroyAlien();
			it = aliensEntities.erase(it);
		}
		else
		{
			++it;
		}
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