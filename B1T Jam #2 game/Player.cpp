#include "Player.h"
#include "Window.h"
#include "Engine.h"

SDL_Texture* Player::playerTexture = NULL;

SDL_FRect Player::srcPlayer = {};
SDL_FRect Player::destPlayer = {};

SDL_Surface* Player::playerSurface = NULL;

SDL_FPoint Player::camera = { 0.0f, 0.0f };

float Player::animationTimer = 0.0f;
int Player::frameY = 0;

Vector2 Player::velocity = Vector2{0.0f, 0.0f};

bool Player::spriteFlipX = false;

// Initialize non-static variables
bool pressed = false;

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

void Player::UpdatePlayer()
{
	HandlePlayerInput();

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
	SDL_RenderTextureRotated(Window::GetRenderer(), playerTexture, &srcPlayer, &destPlayer, 0.0f, NULL,
		spriteFlipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Player::DestroyPlayer()
{
	// Destroy the player texture
	SDL_DestroyTexture(playerTexture);

	playerTexture = NULL;
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
			if (Window::gameState == GameState::Playing) StopMovement();

			if (pressed) pressed = false;
			break;

		case SDL_EVENT_MOUSE_MOTION:
			if (Window::gameState == GameState::Playing) HandleAimCursor();
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (Window::gameState == GameState::Playing) HandleAimAction();
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
	float mouseX;
	float mouseY;
	unsigned int currentMouseStates = SDL_GetMouseState(&mouseX, &mouseY);

#ifdef _DEBUG
	std::cout << "moving cursor x:" << mouseX << " y: " << mouseY << std::endl;
#endif
}

void Player::HandleAimAction()
{
#ifdef _DEBUG
	std::cout << "mouse btn pressed" << std::endl;
#endif
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
