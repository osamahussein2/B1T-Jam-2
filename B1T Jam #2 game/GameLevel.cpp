#include "GameLevel.h"
#include "Window.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>


GameLevel::GameLevel()
	: m_Tiles()
{
}

GameLevel::~GameLevel()
{
	// need to destroy all tiles texture here!! or in a method, when level is completed
    std::cout << "level destroyed" << std::endl;
}

void GameLevel::BuildLevel(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	// calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); 
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / static_cast<float>(height); 

    SDL_Texture* textureBlock0 = IMG_LoadTexture(Window::GetRenderer(), "Textures/block_0.png");
    SDL_Texture* textureBlock1 = IMG_LoadTexture(Window::GetRenderer(), "Textures/block_1.png");
    SDL_Texture* textureBlock2 = IMG_LoadTexture(Window::GetRenderer(), "Textures/block_2.png");

    // initialize level tiles based on tileData
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            Tile tile;
            Vector2 tilePosition(unit_width * x, unit_height * y);
            Vector2 tileScale(unit_width, unit_height);

            if (tileData[y][x] == 0)
            {
                tile.InitializeTile(textureBlock0, tilePosition, tileScale);
            }
            else if (tileData[y][x] == 1) // tile
            {
                tile.InitializeTile(textureBlock1, tilePosition, tileScale);
            } else if (tileData[y][x] == 2)
            {
                tile.InitializeTile(textureBlock2, tilePosition, tileScale);
            }

            tile.SetTileID(tileData[y][x]);

            m_Tiles.push_back(tile);
        }
    }
}
void GameLevel::LoadLevel(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
	unsigned int tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (!fstream)
	{
		std::cout << "Error loading level file" << std::endl;
		return;
	}


	while(std::getline(fstream, line)) // read each line from level file
	{
		std::istringstream sstream(line);
		std::vector<unsigned int> row;
		while (sstream >> tileCode) // read each word separated by spaces
			row.push_back(tileCode);
		tileData.push_back(row);
	}

	if (tileData.size() > 0)
		this->BuildLevel(tileData, levelWidth, levelHeight);

	std::cout << "Level file was loaded succesfully" << std::endl;
}

void GameLevel::DestroyLevel()
{
    std::cout << "Destroy levels" << std::endl;
	for (Tile& tile : m_Tiles)
    {
    	tile.DestroyTile();
    }
}



void GameLevel::RenderLevel()
{
    for (Tile& tile : m_Tiles)
    {
    	tile.RenderTile();
    }
}

bool GameLevel::IsLevelLoaded()
{
	return false;
}

std::vector<Tile> GameLevel::GetTilesArray() const
{
    return m_Tiles;
}

bool GameLevel::TileCollision(Entity* other, int tileNumber_)
{
    for (int i = 0; i < m_Tiles.size(); i++)
    {
        if (m_Tiles[i].GetTileDimensions().x + m_Tiles[i].GetTileDimensions().w >= other->destEntity.x &&
            m_Tiles[i].GetTileDimensions().x <= other->destEntity.x + other->destEntity.w &&
            m_Tiles[i].GetTileDimensions().y + m_Tiles[i].GetTileDimensions().h >= other->destEntity.y &&
            m_Tiles[i].GetTileDimensions().y <= other->destEntity.y + other->destEntity.h &&
            m_Tiles[i].GetTileID() == tileNumber_)
        {
            return true;
        }
    }

    return false;
}
