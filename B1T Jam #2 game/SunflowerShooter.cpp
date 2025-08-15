#include "SunflowerShooter.h"
#include "Window.h"
#include <iostream>
#include "Player.h"

SunflowerShooter::SunflowerShooter() : PlantTower(PlantType::SunflowerShooter)
{
	// Load sunflower shooter
	entitySurface = IMG_Load("Textures/Sunflower1.png");

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);
}

SunflowerShooter::~SunflowerShooter()
{
}

void SunflowerShooter::update()
{
	// Update sunflower shooter

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

		if (shootingTime != 0.0f) shootingTime = 0.0f;
	}

	else
	{
		shootingTime += Window::GetDeltaTime() * 0.02f;

		// Set the source rectangle to match the sprite dimensions for animation
		srcEntity.x = 0;
		srcEntity.y = 0;

		srcEntity.w = entityTexture->w;
		srcEntity.h = entityTexture->h;

		destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
	}
}

void SunflowerShooter::render()
{
	// Render sunflower shooter
	SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
		SDL_FLIP_NONE);
}

void SunflowerShooter::moveEntity(Vector2 position)
{
}

void SunflowerShooter::collision(Entity* other)
{
}

PlantType SunflowerShooter::getPlantID() const
{
	return PlantType::SunflowerShooter;
}
