#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2.h"
#include "FadingText.h"

#include <iostream>

class Player
{
public:
	~Player();

	static void InitializePlayer(std::string filePath_);

	static void LoadPlayerStats();

	static void UpdatePlayer();
	static void RenderPlayer();

	static void DestroyPlayer();

	static SDL_FPoint GetCamera() { return camera; }

	static int GetWaveNumber() { return waveNumber; }
	static void SetWaveNumber(int waveNumber_) { waveNumber = waveNumber_; }

	static bool GetWaveFinishedChanging() { return waveFinishedChanging; }

private:
	Player();

	static void HandlePlayerInput();

	static void HandleMovement();
	static void HandleAimCursor();
	static void HandleAimAction(SDL_Event& event);
	static void StopMovement();

	static void UpdateWave();

	static void SavePlayerProgress();

	static void GoToNextWave();

	static SDL_Texture* playerTexture;

	static SDL_FRect srcPlayer;
	static SDL_FRect destPlayer;

	static SDL_Surface* playerSurface;

	static SDL_FPoint camera;

	static float animationTimer;
	static int frameY;

	static Vector2 velocity;

	static bool spriteFlipX;

	static int waveNumber;

	static bool waveChanged;
	static bool waveFinishedChanging;

	static FadingText waveText;
};

#endif