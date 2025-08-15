#include "Tile.h"
#include "Window.h"

Tile::Tile() : tileTexture(NULL), srcTile(), destTile(), tileSurface(NULL)
{
}

Tile::~Tile()
{
	// Destroy the tile texture
	// SDL_DestroyTexture(tileTexture);

	// tileTexture = NULL;
}

void Tile::InitializeTile(std::string filePath_, Vector2 tilePos_, Vector2 scaleMultiplier_)
{
	// Load tile image
	tileSurface = IMG_Load(filePath_.c_str());

	// If it's invalid, print error
	if (!tileSurface) std::cout << "Can't load " << SDL_GetError();

	// Create a tile texture from surface
	tileTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), tileSurface);

	// Destroy the temporary tile surface
	SDL_DestroySurface(tileSurface);

	// Set the source rectangle and destination rectangle for tile
	srcTile.x = 0;
	srcTile.y = 0;

	srcTile.w = tileTexture->w;
	srcTile.h = tileTexture->h;

	// Draw tile somewhere inside the window
	destTile.x = tilePos_.x;
	destTile.y = tilePos_.y;

	destTile.w = scaleMultiplier_.x;
	destTile.h = scaleMultiplier_.y;
}

void Tile::RenderTile()
{
	// Render the tile
	SDL_RenderTexture(Window::GetRenderer(), tileTexture, &srcTile, &destTile);
}
