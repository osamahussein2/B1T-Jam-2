#pragma once

#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"
#include "PlantType.h"

class Plant : public Entity
{
    public:
                        Plant(PlantType type);
                        ~Plant();

        void                   update() override;
        void                   render() override;
        void                   moveEntity(Vector2 position) override;
        void                   collision(Entity* other) override;

        PlantType          getEntityID() const;

    private:
        PlantType   m_PlantID;
    };

#endif
