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

	void InitializeTile(SDL_Texture* _tileTexture, Vector2 tilePos_, Vector2 scaleMultiplier_);
	void DestroyTile();
	void RenderTile();

	void SetTileID(unsigned int id);
	unsigned int GetTileID() const;

	Vector2 GetTilePosition() const;

	SDL_FRect GetTileDimensions() const { return destTile; }
	Vector2 GetTileCenter() const { return { destTile.x + (destTile.w / 2.0f), destTile.y + (destTile.h / 2.0f) }; }

private:
	SDL_Texture* tileTexture;
	
	SDL_FRect srcTile;
	SDL_FRect destTile;
	
	SDL_Surface* tileSurface;

	unsigned int m_ID;
};

#endif