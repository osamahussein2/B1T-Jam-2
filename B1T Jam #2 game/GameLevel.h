#pragma once
#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "Tile.h"

#include <SDL3/SDL.h>

#include <vector>

class GameLevel
{
    public:
        GameLevel();
        ~GameLevel();

    private:
         void BuildLevel(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

    public:
         void LoadLevel(const char *file, unsigned int levelWidth, unsigned int levelHeight);
         void DestroyLevel();
         void RenderLevel();

         bool IsLevelLoaded();

         std::vector<Tile> GetTilesArray() const;


    private:
        std::vector<Tile> m_Tiles;
};

#endif 
