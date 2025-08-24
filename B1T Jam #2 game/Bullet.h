#ifndef BULLET_H
#define BULLET_H

#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Vector2 position_);
	~Bullet();

    void update() override;
    void render() override;
    void moveEntity(Vector2 position) override;
    void collision(Entity* other) override;
    bool checkCollision(Entity* other);

    void DestroyBullet();

    float GetLifeTime() const { return lifeTime; }

    void SetIsDestroyed(bool destroyed_) { isDestroyed = destroyed_; }
    bool IsDestroyed() const { return isDestroyed; }

    Vector2 GetPosition() { return position; }

private:
    int frameX;

    Vector2 position;
    Vector2 direction;

    float lifeTime;

    bool isDestroyed;

    double rotation;

    float velocity;
};

#endif