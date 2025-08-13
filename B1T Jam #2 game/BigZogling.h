#pragma once
#ifndef BIG_ZOGLING_H
#define BIG_ZOGLING_H

#include "Alien.h"

class BigZogling : public Alien
{
     public:
                            BigZogling();
                            ~BigZogling();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void                    collision(Entity* other) override;


        AlienType           getAlienID() const;
};

#endif

