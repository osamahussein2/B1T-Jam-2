#include "GameLevel.h"

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
}

void GameLevel::BuildLevel(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	// calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); 
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / static_cast<float>(height); 
    // initialize level tiles based on tileData
    float size_sc = 1;		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            Tile tile;
            if (tileData[y][x] == 1) // tile
            {
                Vector2 tilePosition(unit_width * x, unit_height * y);
                Vector2 tileScale(unit_width, unit_height);
                tile.InitializeTile("Textures/block_1.png", tilePosition, tileScale);
                m_Tiles.push_back(tile);
            }
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
	for (Tile& tile : m_Tiles)
    {
    	//tile.DestroyTile();
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
