#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::RunEngine()
{
	Window::InitializeWindow();

	while (Window::GetIsRunning())
	{
		Window::RenderBeginFrame();
		Window::RenderEndFrame();
	}

	Window::DestroyWindow();
}