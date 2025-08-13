#pragma once

#ifndef ALIEN_H
#define ALIEN_H

#include "Entity.h"
#include "AlienType.h"

class Alien : public Entity
{
    public:
                            Alien(AlienType type);
                            ~Alien();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void                    collision(Entity* other) override;

        void DestroyAlien();

        float GetAlienHealth() const { return alienHealth; }
        void SetAlienDamaged(float damagedValue_) { alienHealth -= damagedValue_; }

        AlienType           getEntityID() const;

    private:
         AlienType   m_AlienID;

         float animationTimer;

         float alienHealth;
};

#endif

