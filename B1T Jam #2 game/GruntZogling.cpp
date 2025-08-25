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

	velocity = 0.3f;
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
		//animationTimer += Window::GetDeltaTime() * 0.1f;

		// Set the source rectangle to match the sprite dimensions for animation
		srcEntity.x = (entityTexture->w / 8) * frameX;

		srcEntity.y = (entityTexture->h / 1) * (0 % 1);

		srcEntity.w = entityTexture->w / static_cast<float>(8);
		srcEntity.h = entityTexture->h / static_cast<float>(1);

		// Draw grunt zogling somewhere on window
		destEntity.x = position.x + direction.x;
		destEntity.y = position.y + direction.y;

		//if (direction.x <= 0.1f && direction.y <= 0.1f && frameX != 0) frameX = 0;

		//if (direction.y > 0.1f && frameX != 0) frameX = 0; // Moving down
		//else if (direction.x > 0.1f && frameX != 2) frameX = 2; // Moving right
		//else if (direction.x > 0.1f && frameX != 3) frameX = 3; // Moving right
		//else if (direction.x < -0.1f && frameX != 6) frameX = 6; // Moving left
		//else if (direction.x < -0.1f && frameX != 7) frameX = 7; // Moving left

		destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

		CheckIfStunned();

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
			// Also increase the player's score for defeating grunt zogling
			Player::getScoringSystem().scorePlayer(AlienType::GruntZogling);

			// Make sure to set score changed to true wherever the score player function is
			Player::scoreChanged = true;

			// Change texture image
			entitySurface = IMG_Load("Textures/enemy_dyingx.png");

			if (!entitySurface) std::cout << "Can't load " << SDL_GetError() << std::endl;

			entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
			SDL_DestroySurface(entitySurface);

			if (deathTimer != 0.0f) deathTimer = 0.0f; // Just in case for starting the death animation frames

			Window::sounds["EnemyDeathSound"].PlayAudio();

			hasTextureChanged = true;
		}

		else
		{
			// Prevents the x frame animation from animating too fast
			deathTimer += Window::GetDeltaTime() * 10.0f;

			// Set the source rectangle to match the sprite dimensions for animation
			srcEntity.x = (entityTexture->w / 8) * static_cast<int>(deathTimer);

			srcEntity.y = (entityTexture->h / 1) * (0 % 1);

			srcEntity.w = entityTexture->w / static_cast<float>(8);
			srcEntity.h = entityTexture->h / static_cast<float>(1);

			// Draw grunt zogling somewhere on window
			destEntity.x += 0.0f;
			destEntity.y += 0.0f;

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

void GruntZogling::moveEntity(Vector2 moveToPosition, Vector2 startingPosition)
{
	// Move grunt zogling
	if (!isDead)
	{
		float dx = moveToPosition.x - destEntity.x;
		float dy = moveToPosition.y - destEntity.y;
		float distance = sqrtf((dx * dx) + (dy * dy));

		Vector2 pos = { Window::GetWindowWidth() / GetPosition().x, Window::GetWindowHeight() / GetPosition().y };

		if (distance > 0.3f)
		{
			direction.x += (moveToPosition.x - startingPosition.x) * velocity * Window::GetDeltaTime();
			direction.y += (moveToPosition.y - startingPosition.y) * velocity * Window::GetDeltaTime();
		}
		else
		{
			currentDirectionIndex += 1;
		}
	}
}

void GruntZogling::collision(Entity* other)
{
	// Grunt zogling check for collision
}

AlienType GruntZogling::getAlienID() const
{
	return AlienType::GruntZogling;
}

void GruntZogling::CheckIfStunned()
{
	// Move at normal speed when not stunned
	if (!stunned)
	{
		if (velocity != 0.3f && currentDirectionIndex != 6) velocity = 0.3f;
		else if (velocity != 0.15f && currentDirectionIndex >= 6) velocity = 0.15f;
		if (stunnedTime != 0.0f) stunnedTime = 0.0f;
	}

	// Move 50% slower if stunned
	else if (stunned)
	{
		stunnedTime += Window::GetDeltaTime();

		if (velocity != 0.15f && currentDirectionIndex != 6) velocity = 0.15f;
		else if (velocity != 0.075f && currentDirectionIndex >= 6) velocity = 0.075f;

		if (stunnedTime >= 3.0f)
		{
			stunnedTime = 0.0f;
			stunned = false;
		}
	}
}