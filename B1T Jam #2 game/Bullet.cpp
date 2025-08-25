#include "Bullet.h"
#include "Window.h"
#include "Player.h"

Bullet::Bullet(Vector2 position_) : frameX(0), position(position_), direction(), isDestroyed(false)
{
	// Load bullet
	entitySurface = IMG_Load("Textures/Bullet.png");

	if (!entitySurface) std::cout << "Can't load " << SDL_GetError() << std::endl;

	entityTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), entitySurface);
	SDL_DestroySurface(entitySurface);

	if (Player::flowerUpgrade == 0) velocity = 1.0f;
	else if (Player::flowerUpgrade == 1) velocity = 1.5f;
}

Bullet::~Bullet()
{
	entityTexture = NULL;
}

void Bullet::update()
{
	lifeTime += Window::GetDeltaTime();

	//std::cout << direction.x << ", " << direction.y << std::endl;

	// Set the source rectangle to match the sprite dimensions for animation
	srcEntity.x = 0.0f;
	srcEntity.y = 0.0f;

	srcEntity.w = entityTexture->w;
	srcEntity.h = entityTexture->h;

	srcEntity.x = (entityTexture->w / 4) * frameX;
	srcEntity.y = 0;

	srcEntity.w = entityTexture->w / static_cast<float>(4);
	srcEntity.h = entityTexture->h;

	destEntity.x = position.x + direction.x;
	destEntity.y = position.y + direction.y;

	destEntity.w = (srcEntity.w * 1.0f) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destEntity.h = (srcEntity.h * 1.0f) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
}

void Bullet::render()
{
	// Rotate bullets based on current direction
	if (direction.x <= -0.1f && direction.y < 0.1f && direction.y > -0.1f) rotation = -90.0; // Moving left
	else if (direction.x >= 0.1f && direction.y < 0.1f && direction.y > -0.1f) rotation = 90.0; // Moving right
	else if (direction.y <= -0.1f && direction.x < 0.1f) rotation = 0.0; // Moving up
	else if (direction.y >= 0.1f && direction.x < 0.1f) rotation = 180.0; // Moving down
	else if (direction.x <= -0.1f && direction.y >= 0.1f) rotation = 45.0; // Moving left and down
	else if (direction.x <= -0.1f && direction.y <= -0.1f) rotation = -45.0; // Moving left and up

	// Render bullet
	SDL_RenderTextureRotated(Window::GetRenderer(), entityTexture, &srcEntity, &destEntity, rotation, NULL, 
		SDL_FLIP_NONE);
}

void Bullet::moveEntity(Vector2 position_)
{
	direction.x += (position_.x - position.x) * velocity * Window::GetDeltaTime();
	direction.y += (position_.y - position.y) * velocity * Window::GetDeltaTime();
}

void Bullet::collision(Entity* other)
{
}

bool Bullet::checkCollision(Entity* other)
{
	return destEntity.x + destEntity.w >= other->destEntity.x && destEntity.x <= other->destEntity.x + other->destEntity.w
		&& destEntity.y + destEntity.h >= other->destEntity.y && destEntity.y <= other->destEntity.y + other->destEntity.h;
}

void Bullet::DestroyBullet()
{
	SDL_DestroyTexture(entityTexture);

	entityTexture = NULL;
}
