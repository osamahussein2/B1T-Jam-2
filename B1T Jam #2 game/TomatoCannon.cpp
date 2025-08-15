#include "TomatoCannon.h"
#include <iostream>
#include "Window.h"
#include "SunflowerShooter.h"
#include "Player.h"

TomatoCannon::TomatoCannon() : PlantTower(PlantType::TomatoCannon)
{
	// Load tomato cannon
	entitySurface = IMG_Load("Textures/Tomato1.png");

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);
}

TomatoCannon::~TomatoCannon()
{
}

void TomatoCannon::update()
{
	// Update tomato cannon
	
	if (goingToPlacePlant)
	{
		// Set the source rectangle to match the sprite dimensions for animation
		srcEntity.x = 0;
		srcEntity.y = 0;

		srcEntity.w = entityTexture->w;
		srcEntity.h = entityTexture->h;

		// Draw shield drone somewhere on window
		destEntity.x = Player::GetMouseX() - (destEntity.w / 2.0f);
		destEntity.y = Player::GetMouseY() - (destEntity.h / 2.0f);

		destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
	}

	else
	{
		// Set the source rectangle to match the sprite dimensions for animation
		srcEntity.x = 0;
		srcEntity.y = 0;

		srcEntity.w = entityTexture->w;
		srcEntity.h = entityTexture->h;

		destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
	}
}

void TomatoCannon::render()
{
	// Render tomato cannon
	SDL_RenderTexture(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity);
}

void TomatoCannon::moveEntity(Vector2 position)
{
}

void TomatoCannon::collision(Entity* other)
{
}

PlantType TomatoCannon::getPlantID() const
{
	return PlantType::TomatoCannon;
}
