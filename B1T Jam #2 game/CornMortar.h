#ifndef CORNMORTAR_H
#define CORNMORTAR_H

#pragma once

#include "PlantTower.h"

class CornMortar : public PlantTower
{
public:
	CornMortar();
	~CornMortar();

    void                    update() override;
    void                    render() override;
    void                    moveEntity(Vector2 position) override;
    void                    collision(Entity* other) override;


    PlantType           getPlantID() const;
};

#endif