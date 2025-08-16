#include "Player.h"
#include "Window.h"
#include "Engine.h"

#include <fstream>
#include <algorithm>

int Player::waveNumber = 1;

bool Player::waveChanged = true;

std::map<std::string, FadingText> Player::fadingTexts;

bool Player::waveFinishedChanging = false;

float Player::mouseX = 0.0f;
float Player::mouseY = 0.0f;

bool Player::scoreChanged = false;

int Player::levelNumber = 1;

bool Player::levelChanged = true;
bool Player::levelFinishedChanging = false;

ScoringSystem Player::scoring;

bool Player::canSaveProgress = false;

int Player::currentPlayerScore = 0;

unsigned int Player::playerCurrency = 0;

unsigned int Player::flowerUpgrade = 0;

bool Player::toggleMouseInput = false;

int Player::currentSeedAmount = 100;

int Player::enemiesKilled = 0;
float Player::enemySpawnTime = 0.0f;

// Initialize non-static variables
bool pressed = false;

Player::Player()
{
}

Player::~Player()
{
}

void Player::LoadPlayerStats()
{
	// Read the save file
	std::ifstream getFile("Player Save/SaveGame.txt");

	if (getFile.is_open())
	{
		// Ignore string will detect any whitespace found in the file and skip it entirely
		std::string ignore;

		// Since there are n whitespaces in the file for found strings, we must use ignore n times
		getFile >> ignore >> ignore >> ignore >> waveNumber;
		getFile >> ignore >> ignore >> ignore >> levelNumber;
		getFile >> ignore >> ignore >> ignore >> currentPlayerScore;
		getFile >> ignore >> ignore >> ignore >> playerCurrency;
		getFile >> ignore >> ignore >> flowerUpgrade;
		getFile >> ignore >> ignore >> ignore >> currentSeedAmount;
		getFile.close();

		Engine::UpdateCurrentWaveText();

		if (waveChanged != false) waveChanged = false;
		if (waveFinishedChanging != false) waveFinishedChanging = false;

		if (levelChanged != true) levelChanged = true;
		if (levelFinishedChanging != false) levelFinishedChanging = false;

		if (canSaveProgress != false) canSaveProgress = false;

		if (scoreChanged != true) scoreChanged = true;

		if (fadingTexts["levelText"].GetAlpha() != 0.0f) fadingTexts["levelText"].SetAlpha(0.0f);
		if (fadingTexts["levelText"].GetAlphaStateChanged() != false) fadingTexts["levelText"].SetAlphaStateChanged(false);

		Engine::UpdatePlayerCurrencyText();
		Engine::UpdateSeedAmountText();

		if (playerCurrency >= 999999) playerCurrency = 999999;

		if (waveNumber == 1)
		{
			// Reset the score and make sure the score changed bool is true to show the actual score on HUD
			if (currentPlayerScore != 0) currentPlayerScore = 0;
			if (currentSeedAmount != 100) currentSeedAmount = 100;
			scoreChanged = true;
		}

		if (enemiesKilled != 0) enemiesKilled = 0;
		if (enemySpawnTime != 0.0f) enemySpawnTime = 0.0f;

#ifdef _DEBUG
		std::cout << "Loaded wave number: " << waveNumber << std::endl;
		std::cout << "Loaded level number: " << levelNumber << std::endl;
		std::cout << "Loaded player score: " << currentPlayerScore << std::endl;
		std::cout << "Loaded player currency: $" << playerCurrency << std::endl;
		std::cout << "Loaded flower upgrade: " << flowerUpgrade << std::endl;
		std::cout << "Loaded seed amount: " << currentSeedAmount << std::endl;
#endif
	}

	else
	{
		// Load the player stats upon entering the play state
		if (waveNumber != 1) waveNumber = 1;
		if (levelNumber != 1) levelNumber = 1;
		if (currentSeedAmount != 100) currentSeedAmount = 100;

		if (enemiesKilled != 0) enemiesKilled = 0;
		if (enemySpawnTime != 0.0f) enemySpawnTime = 0.0f;

		Engine::UpdateCurrentWaveText();
		Engine::UpdateSeedAmountText();

		if (waveChanged != false) waveChanged = false;
		if (waveFinishedChanging != false) waveFinishedChanging = false;

		if (levelChanged != true) levelChanged = true;
		if (levelFinishedChanging != false) levelFinishedChanging = false;

		if (canSaveProgress != true) canSaveProgress = true;

		if (fadingTexts["levelText"].GetAlpha() != 0.0f) fadingTexts["levelText"].SetAlpha(0.0f);
		if (fadingTexts["levelText"].GetAlphaStateChanged() != false) fadingTexts["levelText"].SetAlphaStateChanged(false);

		if (flowerUpgrade != 0) flowerUpgrade = 0;

		if (currentPlayerScore != 0) currentPlayerScore = 0;
		if (playerCurrency != 0) playerCurrency = 0;
		if (scoreChanged != true) scoreChanged = true;
	}
}

void Player::UpdatePlayer()
{
	HandlePlayerInput();
	if (Window::gameState == GameState::Playing)
	{
		UpdateLevel();
		UpdateWave();
	}

	ChangeScore();
}

void Player::DestroyPlayer()
{
	// Destroy and clear the fading texts map
	for (std::pair<std::string, FadingText> fadingTextMap : fadingTexts)
	{
		fadingTextMap.second.DestroyText();
		fadingTextMap.first.clear();
	}
}

void Player::HandlePlayerInput()
{
	SDL_Event event;

	// Check if there's an event to handle
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			Window::StopRunning();
			break;

		case SDL_EVENT_KEY_DOWN:

			// Handle press events depending on current game state
			if (event.key.scancode == SDL_SCANCODE_SPACE && Window::gameState == GameState::MainMenu && !pressed)
			{
				Window::gameState = GameState::GameIntro;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_RETURN && Window::gameState == GameState::MainMenu && !pressed)
			{
				Engine::RestartCreditsMenu();
				Window::gameState = GameState::CreditsMenu;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_ESCAPE && Window::gameState == GameState::CreditsMenu && !pressed)
			{
				Window::gameState = GameState::MainMenu;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_RETURN && Window::gameState == GameState::GameIntro && !pressed)
			{
				LoadPlayerStats();

				Window::gameState = GameState::Playing;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_ESCAPE && Window::gameState == GameState::Playing && !pressed)
			{
				Window::gameState = GameState::Paused;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_RETURN && Window::gameState == GameState::Paused && !pressed)
			{
				Window::gameState = GameState::MainMenu;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_ESCAPE && Window::gameState == GameState::Paused && !pressed)
			{
				Window::gameState = GameState::Playing;
				pressed = true;
			}

#ifdef _DEBUG
			if (event.key.scancode == SDL_SCANCODE_RETURN && Window::gameState == GameState::Playing && !pressed &&
				waveFinishedChanging && levelFinishedChanging)
			{
				Window::gameState = GameState::Shopping;
				pressed = true;
			}
#endif

			if (event.key.scancode == SDL_SCANCODE_ESCAPE && Window::gameState == GameState::Shopping && !pressed)
			{
				Player::GoToNextLevel();

				Window::gameState = GameState::Playing;
				pressed = true;
			}

			if (event.key.scancode == SDL_SCANCODE_ESCAPE && Window::gameState == GameState::MainMenu && !pressed)
			{
				Window::StopRunning();
				pressed = true;
			}
			break;

		case SDL_EVENT_KEY_UP:

			if (pressed) pressed = false;
			break;

		case SDL_EVENT_MOUSE_MOTION:
			if (Window::gameState == GameState::Playing && waveFinishedChanging && levelFinishedChanging ||
				Window::gameState == GameState::Shopping && waveFinishedChanging && levelFinishedChanging)
			{
				HandleAimCursor();
			}
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (Window::gameState == GameState::Playing && waveFinishedChanging && levelFinishedChanging || 
				Window::gameState == GameState::Shopping && waveFinishedChanging && levelFinishedChanging)
			{
				HandleAimAction(event);
			}
			break;

		default:
			break;
		}
	}
}

void Player::HandleAimCursor()
{
	unsigned int currentMouseStates = SDL_GetMouseState(&mouseX, &mouseY);

/*#ifdef _DEBUG
	std::cout << "moving cursor x:" << mouseX << " y: " << mouseY << std::endl;
#endif*/
}

void Player::HandleAimAction(SDL_Event& event)
{
	SDL_MouseButtonEvent b = event.button;

	if (b.button == SDL_BUTTON_LEFT)
	{
#ifdef _DEBUG
		std::cout << "moving cursor x:" << Window::GetWindowWidth() / mouseX << " y: " <<
			Window::GetWindowHeight() / mouseY << std::endl;
#endif

#ifdef _DEBUG
		std::cout << "left mouse btn pressed" << std::endl;
#endif

		// Handle some mouse pressed events
		Engine::HandleMousePressedEvents();

		Engine::HasShovel();

		if (currentSeedAmount >= 50) Engine::InstantiateTomatoCannon();
		if (currentSeedAmount >= 30) Engine::InstantiateSunflowerShooter();
		if (currentSeedAmount >= 25) Engine::InstantiateEggplantTrap();
		if (currentSeedAmount >= 90) Engine::InstantiateCornMortar();
	}

	if (b.button == SDL_BUTTON_RIGHT)
	{		
		#ifdef _DEBUG
			std::cout << "right mouse btn pressed" << std::endl;
		#endif
	}

}

void Player::UpdateWave()
{
	switch (waveNumber)
	{
	case 1:
		if (!waveChanged)
		{
			if (waveFinishedChanging != true) waveFinishedChanging = true;
		}

		else if (waveChanged)
		{
			Engine::UpdateCurrentWaveText();
			Engine::UpdateSeedAmountText();

			if (canSaveProgress) SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		break;

	case 2:
		if (waveChanged)
		{
			Engine::UpdateCurrentWaveText();
			Engine::UpdateSeedAmountText();

			if (canSaveProgress) SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (waveFinishedChanging != true) waveFinishedChanging = true;
		}

		break;

	case 3:
		if (waveChanged)
		{
			Engine::UpdateCurrentWaveText();
			Engine::UpdateSeedAmountText();

			if (canSaveProgress) SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (waveFinishedChanging != true) waveFinishedChanging = true;
		}

		break;

	case 4:
		if (waveChanged)
		{
			Engine::UpdateCurrentWaveText();
			Engine::UpdateSeedAmountText();

			if (canSaveProgress) SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (waveFinishedChanging != true) waveFinishedChanging = true;
		}

		break;

	case 5:
		if (waveChanged)
		{
			Engine::UpdateCurrentWaveText();
			Engine::UpdateSeedAmountText();

			if (canSaveProgress) SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (waveFinishedChanging != true) waveFinishedChanging = true;
		}

		break;

	default:

#ifdef _DEBUG
		std::cout << "Wave number invalid\n";
#endif

		break;
	}
}

void Player::UpdateLevel()
{
	switch (levelNumber)
	{
	case 1:
		if (levelChanged)
		{
			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			Engine::UpdateCurrentLevelText();

			if (canSaveProgress) SavePlayerProgress();

			levelFinishedChanging = false;
			levelChanged = false;
		}

		else if (!levelChanged)
		{
			if (!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (levelFinishedChanging != true) levelFinishedChanging = true;
			}
		}
		break;

	case 2:
		if (levelChanged)
		{
			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			Engine::UpdateCurrentLevelText();

			if (canSaveProgress) SavePlayerProgress();

			levelFinishedChanging = false;
			levelChanged = false;
		}

		else if (!levelChanged)
		{
			if (!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (levelFinishedChanging != true) levelFinishedChanging = true;
			}
		}
		break;

	case 3:
		if (levelChanged)
		{
			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			Engine::UpdateCurrentLevelText();

			if (canSaveProgress) SavePlayerProgress();

			levelFinishedChanging = false;
			levelChanged = false;
		}

		else if (!levelChanged)
		{
			if (!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (levelFinishedChanging != true) levelFinishedChanging = true;
			}
		}
		break;

	default:

#ifdef _DEBUG
		std::cout << "Level number invalid\n";
#endif

		break;
	}
}

void Player::SavePlayerProgress()
{
	// Save player progress on file
	std::ofstream writeFile("Player Save/SaveGame.txt");

	std::string waveNumberString = "Wave Number = ";
	std::string levelNumberString = "Level Number = ";
	std::string playerScoreString = "Player score = ";
	std::string currencyString = "Player currency = ";
	std::string flowerUpgradeString = "Flower upgrade ";
	std::string seedAmountString = "Seed amount = ";

	writeFile << waveNumberString << waveNumber << std::endl;
	writeFile << levelNumberString << levelNumber << std::endl;
	writeFile << playerScoreString << currentPlayerScore << std::endl;
	writeFile << currencyString << playerCurrency << std::endl;
	writeFile << flowerUpgradeString << flowerUpgrade << std::endl;
	writeFile << seedAmountString << currentSeedAmount << std::endl;
	writeFile.close();

#ifdef _DEBUG
	std::cout << "Saved wave number: " << waveNumber << std::endl;
	std::cout << "Saved level number: " << levelNumber << std::endl;
	std::cout << "Saved player score: " << currentPlayerScore << std::endl;
	std::cout << "Saved player currency: $" << playerCurrency << std::endl;
	std::cout << "Saved flower upgrade: " << flowerUpgrade << std::endl;
	std::cout << "Saved seed amount: " << currentSeedAmount << std::endl;
#endif
}

void Player::GoToNextWave()
{
	if (waveNumber < 5) ++waveNumber;
	else if (waveNumber >= 5) waveNumber = 1;

	waveChanged = true;
	canSaveProgress = true;
}

void Player::GoToNextLevel()
{
	if (levelNumber < 3)
	{
		++levelNumber;
		levelChanged = true;

		fadingTexts["levelText"].SetAlphaStateChanged(false);
	}

	else
	{
		levelNumber = 1;
		levelChanged = true;

		fadingTexts["levelText"].SetAlphaStateChanged(false);
	}

	if (waveNumber != 1) waveNumber = 1;
	if (currentSeedAmount != 100) currentSeedAmount = 100;

	Engine::UpdateCurrentWaveText();
	Engine::UpdateSeedAmountText();

	if (canSaveProgress != true) canSaveProgress = true;
	
	playerCurrency += currentPlayerScore;

	if (currentPlayerScore != 0)
	{
		currentPlayerScore = 0;
		scoreChanged = true;
	}
}

void Player::ChangeScore()
{
	if (scoreChanged)
	{
		if (currentSeedAmount <= 0) currentSeedAmount = 0;

		Engine::UpdatePlayerScore();
		Engine::UpdateSeedAmountText();

		scoreChanged = false;
	}
}
