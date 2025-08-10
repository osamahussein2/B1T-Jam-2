#include "Text.h"
#include "Window.h"

Text::Text() : textTexture(NULL), srcText(), destText(), textSurface(NULL), font(NULL)
{
}

Text::~Text()
{
}

void Text::InitializeText(std::string filePath_, float fontSize_, std::string text_, SDL_Color color_, float textPosX_,
	float textPosY_)
{
	// Initialize SDL_ttf
	if (TTF_Init())
	{
		// Load the font
		font = TTF_OpenFont(filePath_.c_str(), fontSize_);

		textSurface = TTF_RenderText_Solid(font, text_.c_str(), 0, color_);

		if (!textSurface) std::cout << "Can't load " << SDL_GetError();

		textTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), textSurface);

		SDL_DestroySurface(textSurface);

		// Set the source rectangle and destination rectangle for text
		srcText.x = 0;
		srcText.y = 0;

		srcText.w = textTexture->w;
		srcText.h = textTexture->h;

		// Draw text somewhere inside the window
		destText.x = textPosX_;
		destText.y = textPosY_;

		destText.w = srcText.w * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
		destText.h = srcText.h * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
	}
}

void Text::RenderText()
{
	// Render text
	SDL_RenderTexture(Window::GetRenderer(), textTexture, &srcText, &destText);
}

void Text::DestroyText()
{
	// Close the font
	TTF_CloseFont(font);
}
