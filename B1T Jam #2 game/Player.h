#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2.h"
#include "FadingText.h"
#include "ScoringSystem.h"

#include <iostream>
#include <map>

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
	static bool GetLevelFinishedChanging() { return levelFinishedChanging; }

	static float GetMouseX() { return mouseX; }
	static float GetMouseY() { return mouseY; }

	static ScoringSystem getScoringSystem() { return scoring; }

	static int GetLevelNumber() { return levelNumber; }

	static int currentPlayerScore;

	static unsigned int GetPlayerCurrency() { return playerCurrency; }
	static void SpendPlayerCurrency(unsigned int cost_) { playerCurrency -= cost_; }

	static void GoToNextLevel();

private:
	Player();

	static void HandlePlayerInput();

	static void HandleMovement();
	static void HandleAimCursor();
	static void HandleAimAction(SDL_Event& event);
	static void StopMovement();

	static void UpdateWave();
	static void UpdateLevel();

	static void SavePlayerProgress();

	static void GoToNextWave();

	static void ChangeScore();

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

	static bool levelChanged;
	static bool levelFinishedChanging;

	static std::map<std::string, FadingText> fadingTexts;

	static float mouseX;
	static float mouseY;

	static bool scoreChanged;

	static ScoringSystem scoring;

	static int levelNumber;

	static bool canSaveProgress;

	static unsigned int playerCurrency;
};

#endif