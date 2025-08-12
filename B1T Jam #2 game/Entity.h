#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"

class Entity
{
    public:
                                Entity();
                                ~Entity();

        virtual void                render();
        virtual void                moveEntity(Vector2 position);
        virtual void                collision(Entity* other);

    protected:
        virtual void                update();

        // virtual unsigned int        getEntityID() const;

    private:
        Vector2     m_Position;
        Vector2     m_Velocity;
        int         m_LifePoints;
};

#endif
