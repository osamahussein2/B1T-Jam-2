#include "Alien.h"

Alien::Alien(AlienType type)
	: m_AlienID(type)
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

AlienType Alien::getEntityID() const
{
	return m_AlienID;
}
