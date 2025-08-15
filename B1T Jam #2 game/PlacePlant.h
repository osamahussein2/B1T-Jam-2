#ifndef PLACEPLANT_H
#define PLACEPLANT_H

#pragma once

#include "Entity.h"
#include <iostream>

class PlacePlant : public Entity
{
public:
    PlacePlant();
    ~PlacePlant();

    void InitializePlacingPlant(std::string filePath_, Vector2 startingPosition_);

    void update() override;
    void render() override;
    void moveEntity(Vector2 position) override;
    void collision(Entity* other) override;

    void HandlePlacingPlant();

    void DestroyPlacingPlant();

    bool GetPickedUpPlacingPlant() const { return pickedUpPlacingPlant; }

private:
    bool pickedUpPlacingPlant;

    Vector2 initialPosition;
    Vector2 mouseCenterOnPlant;
};

#endif