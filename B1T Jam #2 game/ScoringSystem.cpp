#include "ScoringSystem.h"
#include <iostream>

ScoringSystem::ScoringSystem(): totalScore(0) {}

ScoringSystem::~ScoringSystem() {}

int ScoringSystem::getEnemyScore(AlienType enemy)
{
    switch(enemy)
    {
        case AlienType::GruntZogling:
            return 10;
        case AlienType::ShieldDrone:
            return 25;
        case AlienType::OrangeZogling:
            return 15;
        case AlienType::StunSporeling:
            return 30;
        case AlienType::GoliathWalker:
            return 100;
    }

    return 0; // in case of not valid enemy type
}

void ScoringSystem::scorePlayer(AlienType enemy)
{
   totalScore += getEnemyScore(enemy);
   #ifdef _DEBUG
         std::cout << "totalScore: " << totalScore << std::endl;
   #endif
}



