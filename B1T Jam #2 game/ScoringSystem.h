#pragma once
#ifndef SCORING_H
#define SCORING_H

#include "AlienType.h"


// basic scoring system to manage points for the game
// it could be extended to work maybe for upgrades also and work with type of plants
class ScoringSystem
{
    public:
                    ScoringSystem();
                    ~ScoringSystem();

    private:
        int            getEnemyScore(AlienType enemy);

    public:
        void           scorePlayer(AlienType enemy);

    private:
        int            totalScore;    
};

#endif

