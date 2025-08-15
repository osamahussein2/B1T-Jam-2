#include "PlacePlant.h"
#include "Window.h"
#include "Player.h"

PlacePlant::PlacePlant() : pickedUpPlacingPlant(false), initialPosition(), mouseCenterOnPlant()
{
}

PlacePlant::~PlacePlant()
{
	entityTexture = NULL;
}

void PlacePlant::InitializePlacingPlant(std::string filePath_, Vector2 startingPosition_)
{
	// Load shovel
	entitySurface = IMG_Load(filePath_.c_str());

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError() << std::endl;

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);

	// Set the source rectangle to match the sprite dimensions for animation
	srcEntity.x = 0.0f;
	srcEntity.y = 0.0f;

	srcEntity.w = entityTexture->w;
	srcEntity.h = entityTexture->h;

	destEntity.x = startingPosition_.x;
	destEntity.y = startingPosition_.y;

	destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

	initialPosition = startingPosition_;
}

void PlacePlant::update()
{
}

void PlacePlant::render()
{
	// Render placing plant
	SDL_RenderTexture(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity);
}

void PlacePlant::moveEntity(Vector2 position)
{
	destEntity.x = position.x;
	destEntity.y = position.y;
}

void PlacePlant::collision(Entity* other)
{
}

void PlacePlant::HandlePlacingPlant()
{
	// If mouse is hovered on the shovel and is pressed, pick up the shovel
	if (Player::GetMouseX() >= destEntity.x && Player::GetMouseX() <= destEntity.x + destEntity.w &&
		Player::GetMouseY() >= destEntity.y && Player::GetMouseY() <= destEntity.y + destEntity.h && !pickedUpPlacingPlant)
	{
		Player::SetToggleMouseInput(true);
		pickedUpPlacingPlant = true;
	}

	else if (pickedUpPlacingPlant)
	{
		Player::SetToggleMouseInput(false);
		pickedUpPlacingPlant = false;
	}
}

void PlacePlant::DestroyPlacingPlant()
{
	SDL_DestroyTexture(entityTexture);

	entityTexture = NULL;
}
