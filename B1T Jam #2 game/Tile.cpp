#include "Tile.h"
#include "Window.h"

Tile::Tile() : tileTexture(NULL), srcTile(), destTile(), tileSurface(NULL)
{
}

Tile::~Tile()
{	
}

void Tile::InitializeTile(SDL_Texture* _tileTexture, Vector2 tilePos_, Vector2 worldPos_, Vector2 scaleMultiplier_)
{
	// Load tile image
	tileTexture = _tileTexture;
	// Set the source rectangle and destination rectangle for tile
	srcTile.x = 0;
	srcTile.y = 0;

	srcTile.w = tileTexture->w;
	srcTile.h = tileTexture->h;

	// Draw tile somewhere inside the window
	destTile.x = tilePos_.x;
	destTile.y = tilePos_.y;

	worldPosition.x = worldPos_.x;
	worldPosition.y = worldPos_.y;

	destTile.w = scaleMultiplier_.x;
	destTile.h = scaleMultiplier_.y;
}

void Tile::DestroyTile()
{
	SDL_DestroyTexture(tileTexture);
}

void Tile::RenderTile()
{
	// Render the tile
	SDL_RenderTexture(Window::GetRenderer(), tileTexture, &srcTile, &destTile);
}

void Tile::RenderTile(bool highlight_)
{
	// Render the tile
	SDL_RenderTexture(Window::GetRenderer(), tileTexture, &srcTile, &destTile);

	// Decrease its alpha a bit to highlight the tile texture
	if (highlight_) SDL_SetTextureAlphaMod(tileTexture, 175);

	// Otherwise, just show the tile texture with full alpha value
	else SDL_SetTextureAlphaMod(tileTexture, 255);
}

void Tile::SetTileID(unsigned int id)
{
	m_ID = id;
}

unsigned int Tile::GetTileID() const
{
	return m_ID;
}

Vector2 Tile::GetTilePosition() const
{
	return Vector2 {destTile.x, destTile.y};
}

Vector2 Tile::GetTileWorldPosition() const
{
	return Vector2 {worldPosition.x, worldPosition.y};
}