#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2.h"

#include <iostream>

class StaticObject
{
public:
	StaticObject();
	~StaticObject();

	void InitializeStaticObject(std::string filePath_, Vector2 position_, Vector2 scaleMultiplier_);
	void RenderStaticObject();

	SDL_FRect GetObjectPosition() const { return destObject; }

private:
	SDL_Texture* staticTexture;

	SDL_FRect srcObject;
	SDL_FRect destObject;

	SDL_Surface* staticSurface;
};

#endif