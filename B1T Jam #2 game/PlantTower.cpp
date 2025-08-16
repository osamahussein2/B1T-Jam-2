#include "PlantTower.h"

PlantTower::PlantTower(PlantType type)
: m_PlantID(type), goingToPlacePlant(true), isDead(false), hasTextureChanged(false), shootingTime(0.0f), 
seedDecreased(false)
{
}

PlantTower::~PlantTower()
{
}

void PlantTower::update()
{
}

void PlantTower::render()
{
}

void PlantTower::moveEntity(Vector2 position)
{
}

void PlantTower::collision(Entity* other)
{
}

bool PlantTower::checkCollision(Entity* other)
{
	return false;
}

void PlantTower::DestroyPlantTower()
{
	SDL_DestroyTexture(entityTexture);

	entityTexture = NULL;
}

PlantType PlantTower::getEntityID() const
{
	return m_PlantID;
}
