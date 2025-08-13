#ifndef CHILIPEPPERBLASTER_H
#define CHILIPEPPERBLASTER_H

#pragma once

#include "PlantTower.h"

class ChiliPepperBlaster : public PlantTower
{
public:
	ChiliPepperBlaster();
	~ChiliPepperBlaster();

    void                    update() override;
    void                    render() override;
    void                    moveEntity(Vector2 position) override;
    void                    collision(Entity* other) override;


    PlantType           getPlantID() const;
};

#endif