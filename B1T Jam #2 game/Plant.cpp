#include "Plant.h"

Plant::Plant(PlantType type)
: m_PlantID(type)
{
}

Plant::~Plant()
{
}

void Plant::update()
{
}

void Plant::render()
{
}

void Plant::moveEntity(Vector2 position)
{
}

void Plant::collision(Entity* other)
{
}

PlantType Plant::getEntityID() const
{
	return m_PlantID;
}
