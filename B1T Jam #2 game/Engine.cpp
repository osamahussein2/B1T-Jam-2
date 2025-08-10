#include "Engine.h"
#include "Player.h"
#include <SDL3_ttf/SDL_ttf.h>

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::RunEngine()
{
	Window::InitializeWindow();
	//Player::InitializePlayer("");

	while (Window::GetIsRunning())
	{
		Window::RenderBeginFrame();

		//Player::UpdatePlayer();
		//Player::RenderPlayer();

		Window::RenderEndFrame();
	}

	Window::DestroyWindow();
	//Player::DestroyPlayer();

	// Quit all SDL subsystems including SDL_TTF
	TTF_Quit();
	SDL_Quit();
}