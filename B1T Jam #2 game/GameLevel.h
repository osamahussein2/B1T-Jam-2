#pragma once
#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "Tile.h"

#include <SDL3/SDL.h>

#include <vector>
#include "Entity.h"

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

         Vector2    GetAlienDestinationPosition() const { return m_EndPosition; }
         void       SetAlienDestinationPosition(Vector2 position) { m_EndPosition = position; }

         bool IsLevelLoaded();

         std::vector<Tile> GetTilesArray() const;

         bool TileCollision(Entity* other, int tileNumber_);

         void TilePlanted(Entity* other, int tileNumber_);
         void TileNotPlanted(Entity* other, int tileNumber_);

         bool GetTilePlanted(Entity* other, int tileNumber_);
         bool GetTileNotPlanted(Entity* other, int tileNumber_);

    private:
        std::vector<Tile>   m_Tiles;
        Vector2             m_EndPosition;
};

#endif 
