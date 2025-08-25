#include "Window.h"
#include "Colors.h"

#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

SDL_Window* Window::gameWindow = NULL; 
SDL_Renderer* Window::gameRenderer = NULL;

int Window::windowWidth = 800;
int Window::windowHeight = 600;

bool Window::isRunning = false;

float Window::deltaTime = 0.0f;

GameState Window::gameState = GameState::MainMenu;

std::map<std::string, Audio> Window::sounds;

Uint32 Window::lastTick = 0;

Window::Window()
{
}

Window::~Window()
{
	gameWindow = NULL;
	gameRenderer = NULL;
}

void Window::InitializeAudioItems()
{
	sounds["EnemyDeathSound"].InitializeAudio("Sounds/Enemy_Dead.wav");
	sounds["BulletSound"].InitializeAudio("Sounds/BulletSound__001.wav");
}

void Window::InitializeWindow()
{
	InitializeAudioItems();


	// Initialize SDL to initialize all of the SDL subsystems
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) >= 0)
	{
		// If initialize SDL_ttf failed
		if (!TTF_Init())
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError());
		}

		/* Make sure the desktop display mode is valid to set the window width and height to be less than the user's
		desktop resolution to ensure compatiblity */
		if (SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay()))
		{
			windowWidth = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay())->w / 2.4; // desktopWidth
			windowHeight = SDL_GetDesktopDisplayMode(SDL_GetPrimaryDisplay())->h / 1.8; // desktopHeight

#ifdef _DEBUG
			std::cout << windowWidth << ", " << windowHeight << std::endl;
#endif
		}

#ifdef _DEBUG
		// Otherwise, set an error message
		else
		{
			std::cerr << "Failed to get desktop display mode: " << SDL_GetError() << std::endl;
		}
#endif

		gameWindow = SDL_CreateWindow("B1T Jam #2 Game", windowWidth, windowHeight, SDL_WINDOW_MAXIMIZED);

		SDL_Surface* iconSurface = IMG_Load("Textures/Sunflower1.png"); 

		if (iconSurface) {
	    	SDL_SetWindowIcon(Window::gameWindow, iconSurface);
	    	SDL_DestroySurface(iconSurface); 
		} else {
		    // SDL_Log("Failed to load icon: %s", IMG_GetError());
			std::cout << "not icon found " << std::endl;
		}
		
		// Create an SDL renderer if the window creation works
		if (gameWindow != 0)
		{
			gameRenderer = SDL_CreateRenderer(gameWindow, NULL);

			if (gameRenderer != 0)
			{
				SDL_SetRenderDrawColor(gameRenderer, LIGHT_GREEN.r, LIGHT_GREEN.g, LIGHT_GREEN.b, LIGHT_GREEN.a);
				isRunning = true;
				
				gameState = GameState::MainMenu;

				lastTick = SDL_GetTicks();
			}

			else
			{
				isRunning = false;
				
				gameState = GameState::Error;
			}
		}
	}

	else if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		isRunning = false;
		
		gameState = GameState::Error;
	}
}

void Window::RenderBeginFrame()
{
	Uint32 currentTick = SDL_GetTicks();
	deltaTime = (float)(currentTick - lastTick) / 1000.0f;
	lastTick = currentTick;

	//std::cout << deltaTime << std::endl;

	// Clear the window with the set drawing color
	SDL_RenderClear(gameRenderer);
}

void Window::RenderEndFrame()
{
	// Draw the window renderer
	SDL_RenderPresent(gameRenderer);
}

void Window::DestroyWindow()
{
	// Destroy both the window and renderer
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	gameWindow = NULL;
	gameRenderer = NULL;

	// Unload any audio
	for (std::pair<std::string, Audio> soundMap : sounds)
	{
		soundMap.second.UnloadAudio();
		soundMap.first.clear();
	}
}