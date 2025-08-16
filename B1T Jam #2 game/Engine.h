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
	static void UpdatePlayerCurrencyText();
	static void UpdateSeedAmountText();

	static void HasShovel();

	static void InstantiateTomatoCannon();
	static void InstantiateSunflowerShooter();
	static void InstantiateEggplantTrap();
	static void InstantiateCornMortar();

private:
	Engine();

	static void InitializeGameTexts();
	static void InitializeScrollingCreditsTexts();
	static void InitializeGameEntities();
	static void InitializeAnimatedObjects();
	static void InitializePlayerHUD();
	static void InitializeShopMenu();
	static void InitializeGameLevels();
	static void InitializePlacingPlants();

	static void IsMouseHovered();

	static void CheckIfScrollingCreditsFinished();

	static void SwitchFlowerUpgrades();

	static void IterateAliens();
	static void IteratePlacingPlants();
	static void IteratePlants();
	static void IterateBullets();
};

#endif