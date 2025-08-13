#include "Entity.h"

#include <iostream>

Entity::Entity()
	: m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_LifePoints(0)
{

}

Entity::~Entity()
{

}

void Entity::update()
{
	std::cout << "update entity" << std::endl;

}

void Entity::render()
{

}

void Entity::moveEntity(Vector2 position)
{
}

void Entity::collision(Entity* other)
{
}
