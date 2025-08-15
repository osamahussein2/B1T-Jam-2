#ifndef SHOVEL_H
#define SHOVEL_H

#pragma once

#include "Entity.h"

class Shovel : public Entity
{
public:
	Shovel();
	~Shovel();

    void InitializeShovel(Vector2 startingPosition_);

    void update() override;
    void render() override;
    void moveEntity(Vector2 position) override;
    void collision(Entity* other) override;
    bool shouldDestroyEntity(Entity* other);

    void HandleShovel();

    void DestroyShovel();

private:
    bool pickedUpShovel;
    bool canDestroyEntity;

    Vector2 initialPosition;

    Vector2 mouseCenterOnShovel;

    float destroyTime;
};

#endif