#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <SDL3/SDL.h>

#include "GameState.h"

class Window
{
public:
	~Window();

	static void InitializeWindow();
	static void RenderBeginFrame();
	static void RenderEndFrame();

	static void DestroyWindow();

	// Getters
	static SDL_Window* GetWindow() { return gameWindow; }
	static SDL_Renderer* GetRenderer() { return gameRenderer; }

	static int GetWindowWidth() { return windowWidth; }
	static int GetWindowHeight() { return windowHeight; }

	static bool GetIsRunning() { return isRunning; }

	static float GetDeltaTime() { return deltaTime; }

	static GameState gameState;

	static void StopRunning() { isRunning = false; }

private:
	Window();

	static SDL_Window* gameWindow;
	static SDL_Renderer* gameRenderer;

	static int windowWidth;
	static int windowHeight;

	static bool isRunning;

	static constexpr float deltaTime = 1.0f / 60.0f;
};

#endif