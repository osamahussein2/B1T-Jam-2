#pragma once
#ifndef GRUNT_ZOG
#define GRUNT_ZOG

#include "Alien.h"

class GruntZogling : public Alien
{
    public:
                            GruntZogling();
                            ~GruntZogling();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void                    collision(Entity* other) override;


        AlienType           getAlienID() const;
};
#endif 

