#include "Entity.h"

#include <iostream>
#include "Window.h"

Entity::Entity()
	: m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_LifePoints(0)
{

}

Entity::~Entity()
{

}

Vector2 Entity::GetWorldPosition()
{
	m_WorldPosition.x = m_Position.x <= 0 ? m_Position.x : Window::GetWindowWidth() / m_Position.x;
	m_WorldPosition.x = m_Position.y <= 0 ? m_Position.y : Window::GetWindowHeight() / m_Position.y;
	
	return m_WorldPosition;
}

void Entity::SetCenteredPosition(SDL_FRect rect_, Vector2 divideValue_)
{
	destEntity.x = rect_.x + (rect_.w / divideValue_.x);
	destEntity.y = rect_.y + (rect_.h / divideValue_.y);
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
