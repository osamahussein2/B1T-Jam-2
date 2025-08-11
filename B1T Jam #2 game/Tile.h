#ifndef TILE_H
#define TILE_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2.h"

#include <iostream>

class Tile
{
public:
	Tile();
	~Tile();

	void InitializeTile(std::string filePath_, Vector2 tilePos_, Vector2 scaleMultiplier_);
	void RenderTile();

private:
	SDL_Texture* tileTexture;
	
	SDL_FRect srcTile;
	SDL_FRect destTile;
	
	SDL_Surface* tileSurface;
};

#endif