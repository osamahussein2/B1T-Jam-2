#include "Engine.h"
#include "Player.h"
#include "Text.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <map>

std::map<std::string, Text> gameTexts;

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

	InitializeGameTexts();

	while (Window::GetIsRunning())
	{
		Window::RenderBeginFrame();

		//Player::UpdatePlayer();
		//Player::RenderPlayer();

		gameTexts["gameIntro"].RenderText();
		gameTexts["gameEndIntro"].RenderText();

		Window::RenderEndFrame();
	}

	Window::DestroyWindow();
	//Player::DestroyPlayer();

	// Destroy all mapped texts and clear all mapped elements as well
	for (std::pair<std::string, Text> textMap : gameTexts)
	{
		textMap.second.DestroyText();
		textMap.first.clear();
	}

	// Quit all SDL subsystems including SDL_TTF
	TTF_Quit();
	SDL_Quit();
}

void Engine::InitializeGameTexts()
{
	// Create game intro texts
	gameTexts["gameIntro"].InitializeText("Aliens from Planet Zog have discovered Earth's livestock and \ndecided they're"
		" the perfect energy source for their interstellar \nBBQ. Unfortunately for them, the local farmer has some friends"
		" \nin the garden... genetically engineered plants with unique \ncombat abilities, ready to defend the farm!",
		20.0f, { static_cast<float>(Window::GetWindowWidth() / 30.0f),
		static_cast<float>(Window::GetWindowHeight() / 3.0f) });

	gameTexts["gameEndIntro"].InitializeText("Press ENTER to continue!",
		15.0f, { static_cast<float>(Window::GetWindowWidth() / 3.0f),
		static_cast<float>(Window::GetWindowHeight() / 1.2f) });
}