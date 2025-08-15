#ifndef ALIEN_H
#define ALIEN_H

#pragma once

#include "Entity.h"
#include "AlienType.h"

class Alien : public Entity
{
    public:
                            Alien();
                            ~Alien();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        virtual void moveEntity(Vector2 moveToPosition, Vector2 startingPosition);
        void                    collision(Entity* other) override;

        void DestroyAlien();

        float GetAlienHealth() const { return alienHealth; }
        void SetAlienDamaged(float damagedValue_) { alienHealth -= damagedValue_; }

        // Death logic
        float getDeathAnimationTime() const { return deathTimer; }
        bool getIsDead() const { return isDead; }

        virtual AlienType           getAlienID() const;

        int GetCurrentDirectionIndex() const { return currentDirectionIndex; }

    protected:
         float          alienHealth;
         float          animationTimer;

         bool isDead;
         bool hasTextureChanged;

         float          deathTimer;

         Vector2 position;
         Vector2 direction;

         float velocity;

         int frameX;

         int currentDirectionIndex;
};

#endif

