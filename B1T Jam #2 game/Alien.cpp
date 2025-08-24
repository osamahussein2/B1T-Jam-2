#include "Alien.h"
#include "Window.h"
#include "Player.h"

#include <iostream>

Alien::Alien()
	: animationTimer(0.0f), isDead(false), hasTextureChanged(false), deathTimer(0.0f), 
	position(Window::GetWindowWidth() / 6.83f, Window::GetWindowHeight() / 200.0f), direction(), velocity(0.0f), initialVelocity(0.0f),
	currentDirectionIndex(0), stunned(false), stunnedTime(0.0f), seedIncreased(false)
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

void Alien::moveEntity(Vector2 moveToPosition, Vector2 startingPosition)
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

