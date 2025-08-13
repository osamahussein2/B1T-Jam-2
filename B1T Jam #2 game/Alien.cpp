#include "Alien.h"
#include "Window.h"
#include "Player.h"

#include <iostream>

Alien::Alien()
	: animationTimer(0.0f)
{
}

Alien::~Alien()
{
}

void Alien::update()
{
}

void Alien::render()
{
}

void Alien::moveEntity(Vector2 position)
{
}

void Alien::collision(Entity* other)
{
}

void Alien::DestroyAlien()
{
	SDL_DestroyTexture(entityTexture);

	entityTexture = NULL;
}

AlienType Alien::getAlienID() const
{
	return AlienType();
}

