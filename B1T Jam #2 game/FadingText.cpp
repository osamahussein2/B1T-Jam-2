#include "FadingText.h"
#include "Window.h"

FadingText::FadingText() : alpha(0.0f), alphaStateChanged(false)
{
}

FadingText::~FadingText()
{
}

void FadingText::InitializeText(std::string text_, float fontSize_, Vector2 textPos_)
{
	// Initialize SDL_ttf
	if (TTF_Init())
	{
		// Load the font
		font = TTF_OpenFont("Fonts/PIXEARG_.TTF", fontSize_);

		textSurface = TTF_RenderText_Blended_Wrapped(font, text_.c_str(), 0, SDL_Color{ 255, 255, 255 }, 0);

		if (!textSurface) std::cout << "Can't load " << SDL_GetError();

		textTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), textSurface);

		SDL_DestroySurface(textSurface);

		// Set the source rectangle and destination rectangle for text
		srcText.x = 0;
		srcText.y = 0;

		srcText.w = textTexture->w;
		srcText.h = textTexture->h;

		// Draw text somewhere inside the window
		destText.x = textPos_.x;
		destText.y = textPos_.y;

		destText.w = srcText.w * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destText.h = srcText.h * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
	}
}

void FadingText::RenderText()
{
	// Make text fade overtime
	if (alphaStateChanged) alpha -= Window::GetDeltaTime();
	else if (!alphaStateChanged) alpha += Window::GetDeltaTime();

	if (alpha >= 255.0f && !alphaStateChanged) alphaStateChanged = true;

	// Render text
	SDL_RenderTexture(Window::GetRenderer(), textTexture, &srcText, &destText);
	SDL_SetTextureAlphaMod(textTexture, static_cast<Uint8>(alpha));
}

void FadingText::DestroyText()
{
	// Close the font
	TTF_CloseFont(font);
}