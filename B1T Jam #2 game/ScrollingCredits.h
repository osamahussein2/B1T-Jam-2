#ifndef SCROLLINGCREDITS_H
#define SCROLLINGCREDITS_H

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Vector2.h"

class ScrollingCredits
{
public:
	ScrollingCredits();
	~ScrollingCredits();

	void InitializeScrollingCredits(std::string text_, float fontSize_, Vector2 textPos_);

	void UpdateScrollingCredits();
	void RenderScrollingCredits();

	void DestroyScrollingCredits();

	float GetPositionY() const { return destText.y; }

	void ResetScrollingCredits();
	void StartScrollingCredits();

private:
	SDL_Texture* textTexture;

	SDL_FRect srcText;
	SDL_FRect destText;

	SDL_Surface* textSurface;

	TTF_Font* font;

	float velocityY;

	Vector2 startingPosition;
};

#endif