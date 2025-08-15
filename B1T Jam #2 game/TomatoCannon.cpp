#include "TomatoCannon.h"
#include <iostream>
#include "Window.h"
#include "SunflowerShooter.h"
#include "Player.h"

TomatoCannon::TomatoCannon() : PlantTower(PlantType::TomatoCannon), tomatoPosition()
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
		// Set the source rectangle to match the sprite dimensions for static animation
		srcEntity.x = (entityTexture->w / 2) * (0 % 2);
		srcEntity.y = (entityTexture->h / 1) * (0 % 1);

		srcEntity.w = (entityTexture->w / 2);
		srcEntity.h = entityTexture->h;

		// Draw shield drone somewhere on window
		destEntity.x = Player::GetMouseX() - (destEntity.w / 2.0f);
		destEntity.y = Player::GetMouseY() - (destEntity.h / 2.0f);

		destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

		if (animationTimer != 0.0f) animationTimer = 0.0f;
	}

	else
	{
		if (!isDead)
		{
			//Prevents the x frame animation from animating too fast
			animationTimer += Window::GetDeltaTime() * 0.1f;

			// Set the source rectangle to match the sprite dimensions for animation
			srcEntity.x = (entityTexture->w / 2) * (static_cast<int>(animationTimer) % 2);
			srcEntity.y = (entityTexture->h / 1) * (0 % 1);

			srcEntity.w = (entityTexture->w / 2);
			srcEntity.h = entityTexture->h;

			destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
			destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

			if (animationTimer >= 10.0f)
			{
				tomatoPosition = { destEntity.x, destEntity.y };

				animationTimer = 0.0f;
				isDead = true;
			}
		}

		else
		{
			if (!hasTextureChanged)
			{
				entitySurface = IMG_Load("Textures/Tomato_Explode1.png");

				if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

				entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
				SDL_DestroySurface(entitySurface);

				hasTextureChanged = true;
			}

			else
			{
				//Prevents the x frame animation from animating too fast
				animationTimer += Window::GetDeltaTime() * 0.1f;

				// Set the source rectangle to match the sprite dimensions for animation
				srcEntity.x = (entityTexture->w / 10) * (static_cast<int>(animationTimer) % 10);
				srcEntity.y = (entityTexture->h / 1) * (0 % 1);

				srcEntity.w = (entityTexture->w / 10);
				srcEntity.h = entityTexture->h;

				destEntity.x = tomatoPosition.x - 25.0f; // Offset to last position before explosion
				destEntity.y = tomatoPosition.y - 25.0f; // Offset to last position before explosion

				destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
				destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
			}
		}
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

bool TomatoCannon::checkCollision(Entity* other)
{
	return destEntity.x + destEntity.w >= other->destEntity.x && destEntity.x <= other->destEntity.x + other->destEntity.w 
		&& destEntity.y + destEntity.h >= other->destEntity.y && destEntity.y <= other->destEntity.y + other->destEntity.h;
}

PlantType TomatoCannon::getPlantID() const
{
	return PlantType::TomatoCannon;
}
