#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include "Window.h"

class Engine
{
public:
	~Engine();

	static void RunEngine();

	static void RestartCreditsMenu();

	static void HandleMousePressedEvents();

	static void UpdatePlayerScore();
	static void UpdateCurrentLevelText();
	static void UpdateCurrentWaveText();

private:
	Engine();

	static void InitializeGameTexts();
	static void InitializeScrollingCreditsTexts();
	static void InitializeGameEntities();
	static void InitializeAnimatedObjects();
	static void InitializePlayerHUD();
	static void InitializeShopMenu();

	static void IsMouseHovered();

	static void CheckIfScrollingCreditsFinished();
};

#endif