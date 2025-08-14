#include "Shovel.h"
#include "Window.h"
#include "Player.h"
#include <iostream>

Shovel::Shovel() : pickedUpShovel(false), initialPosition(), mouseCenterOnShovel(), canDestroyEntity(false), 
destroyTime(0.0f)
{
}

Shovel::~Shovel()
{
}

void Shovel::InitializeShovel(Vector2 startingPosition_)
{
	// Load shovel
	entitySurface = IMG_Load("Textures/Flower_Remover.png");

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

	destEntity.w = (srcEntity.w * 3.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destEntity.h = (srcEntity.h * 3.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

	initialPosition = startingPosition_;
}

void Shovel::update()
{
	// Center the shovel with the mouse position
	mouseCenterOnShovel = { Player::GetMouseX() - (destEntity.w / 2.0f), Player::GetMouseY() - (destEntity.h / 2.0f) };

	if (pickedUpShovel) moveEntity(mouseCenterOnShovel); // Move shovel with mouse to remove something
	else moveEntity(initialPosition); // Place it back where it was

	// Increase destroy time to prevent objects from being constantly destroyed when mouse hovers on an entity
	if (destroyTime <= 0.1f) destroyTime += Window::GetDeltaTime();
	if (canDestroyEntity != false && destroyTime >= 0.05f) canDestroyEntity = false;
}

void Shovel::render()
{
	// Render shovel
	SDL_RenderTexture(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity);
}

void Shovel::moveEntity(Vector2 position)
{
	destEntity.x = position.x;
	destEntity.y = position.y;
}

void Shovel::collision(Entity* other)
{
	/*if (Player::GetMouseX() >= other->destEntity.x &&
		Player::GetMouseX() <= other->destEntity.x + other->destEntity.w &&
		Player::GetMouseY() >= other->destEntity.y &&
		Player::GetMouseY() <= other->destEntity.y + other->destEntity.h && pickedUpShovel)
	{
#ifdef _DEBUG
		std::cout << "Collided\n";
#endif
	}*/
}

bool Shovel::shouldDestroyEntity(Entity* other)
{
	return Player::GetMouseX() >= other->destEntity.x &&
		Player::GetMouseX() <= other->destEntity.x + other->destEntity.w &&
		Player::GetMouseY() >= other->destEntity.y &&
		Player::GetMouseY() <= other->destEntity.y + other->destEntity.h && !pickedUpShovel && canDestroyEntity;
}

void Shovel::HandleShovel()
{
	// If mouse is hovered on the shovel and is pressed, pick up the shovel
	if (Player::GetMouseX() >= destEntity.x && Player::GetMouseX() <= destEntity.x + destEntity.w &&
		Player::GetMouseY() >= destEntity.y && Player::GetMouseY() <= destEntity.y + destEntity.h && !pickedUpShovel)
	{
		pickedUpShovel = true;
	}

	else if (pickedUpShovel)
	{
		if (destroyTime != 0.0f) destroyTime = 0.0f;
		canDestroyEntity = true;

		pickedUpShovel = false;
	}
}

void Shovel::DestroyShovel()
{
	SDL_DestroyTexture(entityTexture);

	entityTexture = NULL;
}