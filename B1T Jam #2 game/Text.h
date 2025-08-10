#ifndef TEXT_H
#define TEXT_H

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>

class Text
{
public:
	Text();
	~Text();

	void InitializeText(std::string filePath_, float fontSize_, std::string text_, SDL_Color color_, float textPosX_,
		float textPosY_);

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