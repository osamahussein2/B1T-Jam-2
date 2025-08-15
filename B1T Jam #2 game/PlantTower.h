#pragma once

#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"
#include "PlantType.h"

class PlantTower : public Entity
{
    public:
        PlantTower(PlantType type);
                        ~PlantTower();

        void                   update() override;
        void                   render() override;
        void                   moveEntity(Vector2 position) override;
        void                   collision(Entity* other) override;

        void DestroyPlantTower();

        PlantType          getEntityID() const;

        void PlacePlant() { if (goingToPlacePlant != false) goingToPlacePlant = false; }
        bool GetGoingToPlacePlant() const { return goingToPlacePlant; }

        Vector2 GetPosition() const { return { destEntity.x, destEntity.y }; }

protected:
    float          animationTimer;

    bool goingToPlacePlant;

    private:
        PlantType   m_PlantID;
    };

#endif
