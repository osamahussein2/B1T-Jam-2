#pragma once
#ifndef STUN_SPORELING_H
#define STUN_SPORELING_H

#include "Alien.h"

class StunSporeling : public Alien
{
     public:
                            StunSporeling();
                            ~StunSporeling();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void                    collision(Entity* other) override;


        AlienType           getAlienID() const;
};

#endif



