#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

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

        SDL_Texture* entityTexture;

        SDL_FRect srcEntity;
        SDL_FRect destEntity;

        SDL_Surface* entitySurface;

        // virtual unsigned int        getEntityID() const;

    private:
        Vector2     m_Position;
        Vector2     m_Velocity;
        int         m_LifePoints;
};

#endif
