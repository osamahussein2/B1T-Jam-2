#ifndef TEXT_H
#define TEXT_H

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Vector2.h"

class Text
{
public:
	Text();
	~Text();

	void InitializeText(std::string text_, float fontSize_, Vector2 textPos_);

	void RenderText();
	void DestroyText();

private:
	SDL_Texture* textTexture;

	SDL_FRect srcText;
	SDL_FRect destText;

	SDL_Surface* textSurface;

	TTF_Font* font;
};

#endif