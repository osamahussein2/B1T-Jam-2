#include "GruntZogling.h"
#include "Window.h"
#include "Player.h"


GruntZogling::GruntZogling()
{
	// Load grunt zogling
	entitySurface = IMG_Load("Textures/GruntZogling.png");

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError() << std::endl;

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);

	// Set alien's health to be whatever at the start and increased after progressing past waves
	alienHealth = 100.0f + ((Player::GetWaveNumber() - 1) * 10.0f);
}

GruntZogling::~GruntZogling()
{
}

void GruntZogling::update()
{
	// Update grunt zogling while isn't dead
	if (!isDead)
	{
		//if (alienHealth >= -0.1f) alienHealth -= Window::GetDeltaTime();

		// Prevents the x frame animation from animating too fast
		animationTimer += Window::GetDeltaTime() * 0.1f;

		// Set the source rectangle to match the sprite dimensions for animation
		srcEntity.x = (entityTexture->w / 8) * (static_cast<int>(animationTimer) % 8);

		srcEntity.y = (entityTexture->h / 1) * (0 % 1);

		srcEntity.w = entityTexture->w / static_cast<float>(8);
		srcEntity.h = entityTexture->h / static_cast<float>(1);

		// Draw grunt zogling somewhere on window
		destEntity.x = 100.0f;
		destEntity.y = 100.0f;

		destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

		if (alienHealth <= 0.0f)
		{
			if (hasTextureChanged != false) hasTextureChanged = false;
			isDead = true;
		}
	}

	// Update grunt zogling death animation and logic
	else
	{
		if (!hasTextureChanged)
		{
			entitySurface = IMG_Load("Textures/enemy_dyingx.png");

			if (!entitySurface) std::cout << "Can't load " << SDL_GetError() << std::endl;

			entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
			SDL_DestroySurface(entitySurface);

			if (deathTimer != 0.0f) deathTimer = 0.0f; // Just in case for starting the death animation frames

			hasTextureChanged = true;
		}

		else
		{
			// Prevents the x frame animation from animating too fast
			deathTimer += Window::GetDeltaTime() * 0.1f;

			// Set the source rectangle to match the sprite dimensions for animation
			srcEntity.x = (entityTexture->w / 8) * static_cast<int>(deathTimer);

			srcEntity.y = (entityTexture->h / 1) * (0 % 1);

			srcEntity.w = entityTexture->w / static_cast<float>(8);
			srcEntity.h = entityTexture->h / static_cast<float>(1);

			// Draw grunt zogling somewhere on window
			destEntity.x = 100.0f;
			destEntity.y = 100.0f;

			destEntity.w = (srcEntity.w * 0.5f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
			destEntity.h = (srcEntity.h * 0.5f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
		}
	}
}

void GruntZogling::render()
{
	// Render grunt zogling
	SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
		SDL_FLIP_NONE);

}

void GruntZogling::moveEntity(Vector2 position)
{
	// Move grunt zogling
}

void GruntZogling::collision(Entity* other)
{
	// Grunt zogling check for collision
}

AlienType GruntZogling::getAlienID() const
{
	return AlienType::GruntZogling;
}
