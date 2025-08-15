#include "CornMortar.h"
#include <iostream>
#include "Window.h"
#include "Player.h"

CornMortar::CornMortar() : PlantTower(PlantType::CornMortar)
{
	// Load corn mortar
	entitySurface = IMG_Load("Textures/CornMortar1.png");

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);
}

CornMortar::~CornMortar()
{
}

void CornMortar::update()
{
	// Update corn mortar

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

void CornMortar::render()
{
	// Render corn mortar
	SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
		SDL_FLIP_NONE);
}

void CornMortar::moveEntity(Vector2 position)
{
}

void CornMortar::collision(Entity* other)
{
}

PlantType CornMortar::getPlantID() const
{
	return PlantType::CornMortar;
}