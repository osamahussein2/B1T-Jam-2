#pragma once

#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"
#include "PlantType.h"
#include "Alien.h"
#include "Bullet.h"

#include <vector>
#include <memory>
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

        Vector2 GetCenter() const { return { destEntity.x + (destEntity.w / 2.0f),
            destEntity.y + (destEntity.h / 2.0f) }; }

        float GetAnimationTimer() const { return animationTimer; }

        bool GetIsDead() const { return isDead; }
        void SetIsDead(bool isDead_) { isDead = isDead_; }

        float GetShootingTime() const { return shootingTime; }
        void ResetShootingTime() { shootingTime = 0.0f; }

        bool GetSeedDecreased() { return seedDecreased; }
        void SetSeedDecreased(bool value_) { seedDecreased = value_; }

        void SetEntityTarget(Entity* target_);

        Vector2 GetTarget() { return m_target; } 

        void AddTarget(Alien* alien) { targetEntities.push_back(alien); }
        void RemoveTarget(Alien* alien) { targetEntities.erase(std::find(targetEntities.begin(), targetEntities.end(), alien)); }

        bool GetIsTarget() { return isTargetSet; }
        void SetIsTarget(bool value_) { isTargetSet = value_; }

        std::vector<Alien*> GetTargets() const { return targetEntities; }
        std::vector<std::unique_ptr<Bullet>>& GetBullets() { return bullets; }

protected:
    float          animationTimer;

    bool goingToPlacePlant;

    bool isDead;
    bool hasTextureChanged;

    float shootingTime;
    bool  isTargetSet;

    bool seedDecreased;

    Vector2 m_target;

    std::vector<Alien*> targetEntities;
    std::vector<std::unique_ptr<Bullet>> bullets;

    private:
        PlantType   m_PlantID;
    };

#endif
