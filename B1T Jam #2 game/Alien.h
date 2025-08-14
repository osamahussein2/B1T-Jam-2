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
        void                    collision(Entity* other) override;

        void DestroyAlien();

        float GetAlienHealth() const { return alienHealth; }
        void SetAlienDamaged(float damagedValue_) { alienHealth -= damagedValue_; }

        // Death logic
        float getDeathAnimationTime() const { return deathTimer; }
        bool getIsDead() const { return isDead; }

        virtual AlienType           getAlienID() const;

    protected:
         float          alienHealth;
         float          animationTimer;

         bool isDead;
         bool hasTextureChanged;

         float          deathTimer;
};

#endif

