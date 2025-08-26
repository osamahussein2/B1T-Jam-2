#include "ScrollingCredits.h"
#include "Window.h"
#include "Colors.h"

ScrollingCredits::ScrollingCredits() : textTexture(NULL), srcText(), destText(), textSurface(NULL), font(), velocityY(),
startingPosition()
{
}

ScrollingCredits::~ScrollingCredits()
{
}

void ScrollingCredits::InitializeScrollingCredits(std::string text_, float fontSize_, Vector2 textPos_)
{
	// Initialize SDL_ttf
	if (TTF_Init())
	{
		// Load the font
		font = TTF_OpenFont("Fonts/PIXEARG_.TTF", fontSize_);

		textSurface = TTF_RenderText_Blended_Wrapped(font, text_.c_str(), 0, DARK_GREEN, 0);

		if (!textSurface) std::cout << "Can't load " << SDL_GetError();

		textTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), textSurface);

		SDL_DestroySurface(textSurface);

		// Set the source rectangle and destination rectangle for text
		srcText.x = 0;
		srcText.y = 0;

		srcText.w = textTexture->w;
		srcText.h = textTexture->h;

		// Draw scrolling credits somewhere inside the window
		destText.x = textPos_.x;
		destText.y = textPos_.y;

		destText.w = srcText.w * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destText.h = srcText.h * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);

		startingPosition = textPos_;
	}
}

void ScrollingCredits::UpdateScrollingCredits()
{
	// Draw scrolling credits somewhere inside the window
	destText.x = startingPosition.x;
	destText.y = startingPosition.y + velocityY;

	destText.w = srcText.w * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destText.h = srcText.h * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
	
	velocityY -= 125.0f * Window::GetDeltaTime();
}

void ScrollingCredits::RenderScrollingCredits()
{
	// Render text
	if (destText.y >= static_cast<float>(Window::GetWindowWidth()) / 8.0f && 
		destText.y <= static_cast<float>(Window::GetWindowWidth()) / 1.7f)
		SDL_RenderTexture(Window::GetRenderer(), textTexture, &srcText, &destText);
}

void ScrollingCredits::DestroyScrollingCredits()
{
	// Close the font
	TTF_CloseFont(font);
}

void ScrollingCredits::ResetScrollingCredits()
{
	// Make sure the credits texts are at the bottom of the screen to restart the scrolling
	velocityY = static_cast<float>(Window::GetWindowHeight());
}

void ScrollingCredits::StartScrollingCredits()
{
	if (velocityY != 0.0f) velocityY = 0.0f;
}