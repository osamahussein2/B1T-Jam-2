#ifndef PEAVINESNIPER_H
#define PEAVINESNIPER_H

#pragma once

#include "PlantTower.h"

class PeaVineSniper : public PlantTower
{
public:
	PeaVineSniper();
	~PeaVineSniper();

    void                    update() override;
    void                    render() override;
    void                    moveEntity(Vector2 position) override;
    void                    collision(Entity* other) override;


    PlantType           getPlantID() const;
};

#endif