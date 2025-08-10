#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2.h"

#include <iostream>

class Player
{
public:
	~Player();

	static void InitializePlayer(std::string filePath_);
	static void UpdatePlayer();
	static void RenderPlayer();

	static void DestroyPlayer();

	static SDL_FPoint GetCamera() { return camera; }

private:
	Player();

	static void HandlePlayerInput();

	static void HandleMovement();
	static void StopMovement();

	static SDL_Texture* playerTexture;

	static SDL_FRect srcPlayer;
	static SDL_FRect destPlayer;

	static SDL_Surface* playerSurface;

	static SDL_FPoint camera;

	static float animationTimer;
	static int frameY;

	static Vector2 velocity;

	static bool spriteFlipX;
};

#endif