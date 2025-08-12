#include "Item.h"

Item::Item(ItemType type)
: m_ItemType(type)
{
}

Item::~Item()
{
}

void Item::update()
{
}

void Item::render()
{
}

void Item::moveEntity(Vector2 position)
{
}

void Item::collision(Entity* other)
{
}

ItemType Item::getEntityID() const
{
	return m_ItemType;
}
