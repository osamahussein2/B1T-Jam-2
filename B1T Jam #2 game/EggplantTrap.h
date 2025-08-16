#ifndef EGGPLANTTRAP_H
#define EGGPLANTTRAP_H

#pragma once

#include "PlantTower.h"

class EggplantTrap : public PlantTower
{
public:
    EggplantTrap();
    ~EggplantTrap();

    void                    update() override;
    void                    render() override;
    void                    moveEntity(Vector2 position) override;
    bool checkCollision(Entity* other);
    void                    collision(Entity* other) override;


    PlantType           getPlantID() const;
};

#endif