#include "Player.h"
#include "Window.h"
#include "Engine.h"

#include <fstream>
#include <algorithm>

SDL_Texture* Player::playerTexture = NULL;

SDL_FRect Player::srcPlayer = {};
SDL_FRect Player::destPlayer = {};

SDL_Surface* Player::playerSurface = NULL;

SDL_FPoint Player::camera = { 0.0f, 0.0f };

float Player::animationTimer = 0.0f;
int Player::frameY = 0;

Vector2 Player::velocity = Vector2{0.0f, 0.0f};

bool Player::spriteFlipX = false;

int Player::waveNumber = 1;

bool Player::waveChanged = true;

std::map<std::string, FadingText> Player::fadingTexts;

bool Player::waveFinishedChanging = false;

float Player::mouseX = 0.0f;
float Player::mouseY = 0.0f;

bool Player::scoreChanged = false;

int Player::levelNumber = 1;

// Initialize non-static variables
bool pressed = false;

ScoringSystem Player::scoring;


Player::Player()
{
}

Player::~Player()
{
	playerTexture = NULL;
}

void Player::InitializePlayer(std::string filePath_)
{
	// Load the images from SDL image library
	playerSurface = IMG_Load(filePath_.c_str());

	if (!playerSurface) std::cout << "Can't load " << SDL_GetError();

	// Use the sprite texture to render from the SDL's surface
	playerTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), playerSurface);

	// Free the surface to release any used memory
	SDL_DestroySurface(playerSurface);
}

void Player::LoadPlayerStats()
{
	// Read the save file
	std::ifstream getFile("Player Save/SaveGame.txt");

	if (getFile.is_open())
	{
		// Ignore string will detect any whitespace found in the file and skip it entirely
		std::string ignore;

		// Since there are 3 whitespaces in the file for found strings, we must use ignore 3 times
		getFile >> ignore >> ignore >> ignore >> waveNumber;
		getFile >> ignore >> ignore >> ignore >> levelNumber;
		getFile.close();

		if (waveChanged != true) waveChanged = true;
		if (waveFinishedChanging != false) waveFinishedChanging = false;

		if (fadingTexts["waveText"].GetAlpha() != 0.0f) fadingTexts["waveText"].SetAlpha(0.0f);
		if (fadingTexts["waveText"].GetAlphaStateChanged() != false) fadingTexts["waveText"].SetAlphaStateChanged(false);

		if (fadingTexts["levelText"].GetAlpha() != 0.0f) fadingTexts["levelText"].SetAlpha(0.0f);
		if (fadingTexts["levelText"].GetAlphaStateChanged() != false) fadingTexts["levelText"].SetAlphaStateChanged(false);

		if (scoring.getCurrentPlayerScore() != 0 && waveNumber == 1)
		{
			// Reset the score and make sure the score changed bool is true to show the actual score on HUD
			scoring.resetScore();
			scoreChanged = true;
		}

#ifdef _DEBUG
		std::cout << "Loaded wave number: " << waveNumber << std::endl;
		std::cout << "Loaded level number: " << levelNumber << std::endl;
#endif
	}

	else
	{
		// Load the player stats upon entering the play state
		if (waveNumber != 1) waveNumber = 1;
		if (levelNumber != 1) levelNumber = 1;

		if (waveChanged != true) waveChanged = true;
		if (waveFinishedChanging != false) waveFinishedChanging = false;

		if (fadingTexts["waveText"].GetAlpha() != 0.0f) fadingTexts["waveText"].SetAlpha(0.0f);
		if (fadingTexts["waveText"].GetAlphaStateChanged() != false) fadingTexts["waveText"].SetAlphaStateChanged(false);

		if (fadingTexts["levelText"].GetAlpha() != 0.0f) fadingTexts["levelText"].SetAlpha(0.0f);
		if (fadingTexts["levelText"].GetAlphaStateChanged() != false) fadingTexts["levelText"].SetAlphaStateChanged(false);

		if (scoring.getCurrentPlayerScore() != 0) scoring.resetScore();
		scoreChanged = true;
	}
}

void Player::UpdatePlayer()
{
	HandlePlayerInput();
	if (Window::gameState == GameState::Playing) UpdateWave();

	ChangeScore();

	// Prevents the x frame animation from animating too fast
	animationTimer += Window::GetDeltaTime() * 0.1f;

	// Set the source rectangle to match the sprite dimensions for animation
	srcPlayer.x = (playerTexture->w / 4) * (static_cast<int>(animationTimer) % 4);
	srcPlayer.y = (playerTexture->h / 4) * (frameY % 4);

	srcPlayer.w = playerTexture->w / 4;
	srcPlayer.h = playerTexture->h / 4;

	// Draw image on window and move it accordingly (also will move with the camera centered at the image)
	destPlayer.x = velocity.x - camera.x;
	destPlayer.y = velocity.y - camera.y;

	destPlayer.w = (srcPlayer.w * 5) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destPlayer.h = (srcPlayer.h * 5) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

	camera = { velocity.x - (Window::GetWindowWidth() / 2.25f), velocity.y - (Window::GetWindowHeight() / 2.5f) };
}

void Player::RenderPlayer()
{
	// Render the sprite based on sprite flip X
	if (waveFinishedChanging)
	{
		SDL_RenderTextureRotated(Window::GetRenderer(), playerTexture, &srcPlayer, &destPlayer, 0.0f, NULL, 
			spriteFlipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}
}

void Player::DestroyPlayer()
{
	// Destroy the player texture
	SDL_DestroyTexture(playerTexture);

	playerTexture = NULL;

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
			if (Window::gameState == GameState::Playing) HandleMovement();

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

			if (event.key.scancode == SDL_SCANCODE_ESCAPE && Window::gameState == GameState::MainMenu && !pressed)
			{
				Window::StopRunning();
				pressed = true;
			}
			break;

		case SDL_EVENT_KEY_UP:
			if (Window::gameState == GameState::Playing && waveFinishedChanging) StopMovement();

			if (pressed) pressed = false;
			break;

		case SDL_EVENT_MOUSE_MOTION:
			if (Window::gameState == GameState::Playing && waveFinishedChanging) HandleAimCursor();
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (Window::gameState == GameState::Playing && waveFinishedChanging) HandleAimAction(event);
			break;

		default:
			break;
		}
	}
}

void Player::HandleMovement()
{
#ifdef _DEBUG
	std::cout << "keyboard btn pressed" << std::endl;
#endif

	const bool* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_D])
	{
		if (frameY != 2) frameY = 2;
		if (spriteFlipX != false) spriteFlipX = false;
		velocity.x += 50.0f * Window::GetDeltaTime();
	}

	if (currentKeyStates[SDL_SCANCODE_A])
	{
		if (frameY != 2) frameY = 2;
		if (spriteFlipX != true) spriteFlipX = true;
		velocity.x += -50.0f * Window::GetDeltaTime();
	}

	if (currentKeyStates[SDL_SCANCODE_W])
	{
		if (frameY != 1) frameY = 1;
		velocity.y += -50.0f * Window::GetDeltaTime();
	}

	if (currentKeyStates[SDL_SCANCODE_S])
	{
		if (frameY != 0) frameY = 0;
		velocity.y += 50.0f * Window::GetDeltaTime();
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
			std::cout << "left mouse btn pressed" << std::endl;
		#endif
		// test case of scoring player before killing an enemy	
		scoring.scorePlayer(AlienType::GruntZogling);

		scoreChanged = true; // Make sure to set score changed to true wherever the score player function is

		// Handle some mouse pressed events
		Engine::HandleMousePressedEvents();
	}

	if (b.button == SDL_BUTTON_RIGHT)
	{		
		#ifdef _DEBUG
			std::cout << "right mouse btn pressed" << std::endl;
		#endif
	}

}

void Player::StopMovement()
{
	const bool* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (!currentKeyStates[SDL_SCANCODE_S] && !currentKeyStates[SDL_SCANCODE_W] &&
		!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
	{
		if (frameY != 3) frameY = 3;
		if (spriteFlipX != false) spriteFlipX = false;

		velocity.x += 0.0f;
		velocity.y += 0.0f;
	}

	else if (!currentKeyStates[SDL_SCANCODE_S] && !currentKeyStates[SDL_SCANCODE_W])
	{
		velocity.y += 0.0f;
	}

	else if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
	{
		if (spriteFlipX != false) spriteFlipX = false;
		velocity.x += 0.0f;
	}
}

void Player::UpdateWave()
{
	switch (waveNumber)
	{
	case 1:
		if (!waveChanged)
		{
			if (!fadingTexts["waveText"].GetAlphaStateChanged() ||
				fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() > 0.0f &&
				!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["waveText"].RenderText();
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() <= 0.0f ||
				fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (waveFinishedChanging != true) waveFinishedChanging = true;
			}
		}

		else if (waveChanged)
		{
			fadingTexts["waveText"].InitializeText("Wave " + std::to_string(waveNumber), 30, 
				{ static_cast<float>(Window::GetWindowWidth() / 2.35f),
				static_cast<float>(Window::GetWindowHeight() / 2.25f) });

			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		break;

	case 2:
		if (waveChanged)
		{
			fadingTexts["waveText"].InitializeText("Wave " + std::to_string(waveNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.35f),
				static_cast<float>(Window::GetWindowHeight() / 2.25f) });

			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (!fadingTexts["waveText"].GetAlphaStateChanged() ||
				fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() > 0.0f &&
				!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["waveText"].RenderText();
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() <= 0.0f ||
				fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (waveFinishedChanging != true) waveFinishedChanging = true;
			}
		}

		break;

	case 3:
		if (waveChanged)
		{
			fadingTexts["waveText"].InitializeText("Wave " + std::to_string(waveNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.35f),
				static_cast<float>(Window::GetWindowHeight() / 2.25f) });

			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (!fadingTexts["waveText"].GetAlphaStateChanged() ||
				fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() > 0.0f &&
				!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["waveText"].RenderText();
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() <= 0.0f ||
				fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (waveFinishedChanging != true) waveFinishedChanging = true;
			}
		}

		break;

	case 4:
		if (waveChanged)
		{
			fadingTexts["waveText"].InitializeText("Wave " + std::to_string(waveNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.35f),
				static_cast<float>(Window::GetWindowHeight() / 2.25f) });

			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (!fadingTexts["waveText"].GetAlphaStateChanged() ||
				fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() > 0.0f &&
				!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["waveText"].RenderText();
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() <= 0.0f ||
				fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (waveFinishedChanging != true) waveFinishedChanging = true;
			}
		}

		break;

	case 5:
		if (waveChanged)
		{
			fadingTexts["waveText"].InitializeText("Wave " + std::to_string(waveNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.35f),
				static_cast<float>(Window::GetWindowHeight() / 2.25f) });

			fadingTexts["levelText"].InitializeText("Level " + std::to_string(levelNumber), 30,
				{ static_cast<float>(Window::GetWindowWidth() / 2.3f),
				static_cast<float>(Window::GetWindowHeight() / 2.75f) });

			SavePlayerProgress();

			waveFinishedChanging = false;
			waveChanged = false;
		}

		else if (!waveChanged)
		{
			if (!fadingTexts["waveText"].GetAlphaStateChanged() ||
				fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() > 0.0f &&
				!fadingTexts["levelText"].GetAlphaStateChanged() || fadingTexts["levelText"].GetAlphaStateChanged() &&
				fadingTexts["levelText"].GetAlpha() > 0.0f)
			{
				fadingTexts["waveText"].RenderText();
				fadingTexts["levelText"].RenderText();
			}

			else if (fadingTexts["waveText"].GetAlphaStateChanged() && fadingTexts["waveText"].GetAlpha() <= 0.0f &&
				fadingTexts["levelText"].GetAlphaStateChanged() && fadingTexts["levelText"].GetAlpha() <= 0.0f)
			{
				if (waveFinishedChanging != true) waveFinishedChanging = true;
			}
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
		break;

	case 2:
		break;

	case 3:
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

	writeFile << waveNumberString << waveNumber << std::endl;
	writeFile << levelNumberString << levelNumber << std::endl;
	writeFile.close();

#ifdef _DEBUG
	std::cout <<  "Saved wave number: " << waveNumber << std::endl;
	std::cout << "Saved level number: " << levelNumber << std::endl;
#endif
}

void Player::GoToNextWave()
{
	if (waveNumber < 5) ++waveNumber;
	else if (waveNumber >= 5) waveNumber = 1;

	waveChanged = true;

	if (waveNumber % 3 == 0)
	{
		++levelNumber;

		if (scoring.getCurrentPlayerScore() != 0) scoring.resetScore();
		scoreChanged = true;
	}

	fadingTexts["waveText"].SetAlphaStateChanged(false);
	fadingTexts["levelText"].SetAlphaStateChanged(false);
}

void Player::ChangeScore()
{
	if (scoreChanged)
	{
		Engine::UpdatePlayerScore();

		scoreChanged = false;
	}
}
