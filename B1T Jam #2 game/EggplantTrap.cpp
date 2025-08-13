#include "EggplantTrap.h"
#include "Window.h"
#include <iostream>

EggplantTrap::EggplantTrap() : PlantTower(PlantType::EggplantTrap)
{
	// Load eggplant trap
	entitySurface = IMG_Load("Textures/");

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);
}

EggplantTrap::~EggplantTrap()
{
}

void EggplantTrap::update()
{
	// Update eggplant trap

	// Prevents the x frame animation from animating too fast
	animationTimer += Window::GetDeltaTime() * 0.1f;

	// Set the source rectangle to match the sprite dimensions for animation
	srcEntity.x = (entityTexture->w / 8) * (static_cast<int>(animationTimer) % 8);

	srcEntity.y = (entityTexture->h / 1) * (0 % 1);

	srcEntity.w = entityTexture->w / static_cast<float>(8);
	srcEntity.h = entityTexture->h / static_cast<float>(1);

	// Draw shield drone somewhere on window
	destEntity.x = 200.0f;
	destEntity.y = 200.0f;

	destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
}

void EggplantTrap::render()
{
	// Render eggplant trap
	SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
		SDL_FLIP_NONE);
}

void EggplantTrap::moveEntity(Vector2 position)
{
}

void EggplantTrap::collision(Entity* other)
{
}

PlantType EggplantTrap::getPlantID() const
{
	return PlantType::EggplantTrap;
}