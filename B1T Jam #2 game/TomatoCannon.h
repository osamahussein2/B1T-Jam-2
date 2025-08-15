#ifndef TOMATOCANNON_H
#define TOMATOCANNON_H

#pragma once

#include "PlantTower.h"

class TomatoCannon : public PlantTower
{
public:
	TomatoCannon();
	~TomatoCannon();

    void                    update() override;
    void                    render() override;
    void                    moveEntity(Vector2 position) override;
    void                    collision(Entity* other) override;
    bool                   checkCollision(Entity* other) override;


    PlantType           getPlantID() const;

private:
    Vector2 tomatoPosition;
};

#endif