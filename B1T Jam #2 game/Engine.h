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

private:
	Engine();

	static void InitializeGameTexts();
	static void InitializeScrollingCreditsTexts();
	static void InitializeGameEntities();
	static void InitializeAnimatedObjects();
	static void IsMouseHovered();

	static void CheckIfScrollingCreditsFinished();
};

#endif