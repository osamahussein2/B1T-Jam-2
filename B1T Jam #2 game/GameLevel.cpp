#include "GameLevel.h"

#include <fstream>
#include <sstream>
#include <cstdlib>


GameLevel::GameLevel()
	: m_Tiles()
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::BuildLevel(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	// calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height; 
    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            Tile tile;
            if (tileData[y][x] == 1) // solid
            {
                Vector2 tilePosition(unit_width * x, unit_height * y);
                Vector2 tileScale(unit_width, unit_height);
                tile.InitializeTile("Textures/background.png", tilePosition, tileScale);
                m_Tiles.push_back(tile);
            }
            else if (tileData[y][x] > 1)	// non-solid; now determine its color based on level data
            {
                Vector2 tilePosition(unit_width * x, unit_width * y);
                Vector2 tileScale(unit_width, unit_height);
                tile.InitializeTile("Textures/background.png", tilePosition, tileScale);
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

	if(fstream)
	{
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
	}
}




void GameLevel::DrawLevel()
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
