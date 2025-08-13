#include "Alien.h"
#include "Window.h"
#include <iostream>

Alien::Alien(AlienType type)
	: m_AlienID(type), animationTimer(0.0f)
{
	switch (type)
	{
	case AlienType::GruntZogling:

		// Load grunt zogling
		entitySurface = IMG_Load("Textures/GruntZogling.png");

		if (!entitySurface) std::cout << "Can't load " << SDL_GetError() << std::endl;

		entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
		SDL_DestroySurface(entitySurface);

		break;

	case AlienType::ShieldDrone:

		// Load shield drone
		entitySurface = IMG_Load("Textures/ShieldDrone.png");

		if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

		entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
		SDL_DestroySurface(entitySurface);

		break;

	case AlienType::BigZogling:

		// Load big zogling
		entitySurface = IMG_Load("Textures/");

		if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

		entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
		SDL_DestroySurface(entitySurface);

		break;

	case AlienType::StunSporeling:

		// Load stun sporeling
		entitySurface = IMG_Load("Textures/");

		if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

		entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
		SDL_DestroySurface(entitySurface);

		break;

	case AlienType::GoliathWalker:

		// Load goliath walker
		entitySurface = IMG_Load("Textures/");

		if (!entitySurface) std::cout << "Can't load " << SDL_GetError();

		entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
		SDL_DestroySurface(entitySurface);

		break;

	default:
		break;
	}
}

Alien::~Alien()
{
}

void Alien::update()
{
	switch (m_AlienID)
	{
	case AlienType::GruntZogling:

		// Update grunt zogling
		
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

		break;

	case AlienType::ShieldDrone:

		// Update shield drone
		
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

		break;

	case AlienType::BigZogling:

		// Update big zogling
		
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

		break;

	case AlienType::StunSporeling:

		// Update stun sporeling
		
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

		break;

	case AlienType::GoliathWalker:

		// Update goliath walker
		
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

		break;

	default:
		break;
	}
}

void Alien::render()
{
	switch (m_AlienID)
	{
	case AlienType::GruntZogling:

		// Render grunt zogling
		SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
			SDL_FLIP_NONE);

		break;

	case AlienType::ShieldDrone:

		// Render shield drone
		SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
			SDL_FLIP_NONE);

		break;

	case AlienType::BigZogling:

		// Render big zogling
		SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
			SDL_FLIP_NONE);

		break;

	case AlienType::StunSporeling:

		// Render stun sporeling
		SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
			SDL_FLIP_NONE);

		break;

	case AlienType::GoliathWalker:

		// Render goliath walker
		SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, 0.0, NULL,
			SDL_FLIP_NONE);

		break;

	default:
		break;
	}
}

void Alien::moveEntity(Vector2 position)
{
	switch (m_AlienID)
	{
	case AlienType::GruntZogling:

		// Move grunt zogling


		break;

	case AlienType::ShieldDrone:

		// Move shield drone


		break;

	case AlienType::BigZogling:

		// Move big zogling


		break;

	case AlienType::StunSporeling:

		// Move stun sporeling


		break;

	case AlienType::GoliathWalker:

		// Move goliath walker


		break;

	default:
		break;
	}
}

void Alien::collision(Entity* other)
{
	switch (m_AlienID)
	{
	case AlienType::GruntZogling:

		// Grunt zogling check for collision


		break;

	case AlienType::ShieldDrone:

		// Shield drone check for collision


		break;

	case AlienType::BigZogling:

		// Big zogling check for collision


		break;

	case AlienType::StunSporeling:

		// Stun sporeling check for collision


		break;

	case AlienType::GoliathWalker:

		// Goliath walker check for collision


		break;

	default:
		break;
	}
}

void Alien::DestroyAlien()
{
	SDL_DestroyTexture(entityTexture);

	entityTexture = NULL;
}

AlienType Alien::getEntityID() const
{
	return m_AlienID;
}
