#pragma once
#ifndef GOLIATH_WALKER_H
#define GOLIATH_WALKER_H

#include "Alien.h"

class GoliathWalker : public Alien
{
     public:
                            GoliathWalker();
                            ~GoliathWalker();

        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void                    collision(Entity* other) override;


        AlienType           getAlienID() const;

};

#endif




