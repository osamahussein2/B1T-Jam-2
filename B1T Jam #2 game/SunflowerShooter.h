#ifndef SUNFLOWERSHOOTER_H
#define SUNFLOWERSHOOTER_H

#pragma once

#include "PlantTower.h"
#include "Bullet.h"
#include <vector>

class SunflowerShooter : public PlantTower
{
public:
    SunflowerShooter();
    ~SunflowerShooter();

    void                    update() override;
    void                    render() override;
    void                    moveEntity(Vector2 position) override;
    void                    collision(Entity* other) override;


    PlantType           getPlantID() const;
};

#endif