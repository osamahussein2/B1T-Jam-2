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
        virtual bool                   checkCollision(Entity* other);

        void DestroyPlantTower();

        PlantType          getEntityID() const;

        void PlacePlant() { if (goingToPlacePlant != false) goingToPlacePlant = false; }
        bool GetGoingToPlacePlant() const { return goingToPlacePlant; }

        Vector2 GetPosition() const { return { destEntity.x, destEntity.y }; }
        Vector2 GetCenter() const { return { destEntity.x + (destEntity.w / 2.0f),
            destEntity.y + (destEntity.h / 2.0f) }; }

        float GetAnimationTimer() const { return animationTimer; }
        bool GetIsDead() const { return isDead; }

        float GetShootingTime() const { return shootingTime; }
        void ResetShootingTime() { shootingTime = 0.0f; }

protected:
    float          animationTimer;

    bool goingToPlacePlant;

    bool isDead;
    bool hasTextureChanged;

    float shootingTime;

    private:
        PlantType   m_PlantID;
    };

#endif
