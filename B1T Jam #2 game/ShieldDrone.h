#pragma once
#ifndef SHIELD_DRONE_H
#define SHIELD_DRONE_H

#include "Alien.h"

class ShieldDrone : public Alien
{
     public:
                            ShieldDrone();
                            ~ShieldDrone();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void moveEntity(Vector2 moveToPosition, Vector2 startingPosition);
        void                    collision(Entity* other) override;


        AlienType           getAlienID() const;

private:
    void CheckIfStunned();
};

#endif

