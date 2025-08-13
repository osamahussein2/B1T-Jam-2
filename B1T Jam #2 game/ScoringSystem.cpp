#include "ScoringSystem.h"
#include <iostream>
#include "Player.h"

ScoringSystem::ScoringSystem() {}

ScoringSystem::~ScoringSystem() {}

int ScoringSystem::getEnemyScore(AlienType enemy)
{
    switch(enemy)
    {
        case AlienType::GruntZogling:
            return 10;
        case AlienType::ShieldDrone:
            return 25;
        case AlienType::BigZogling:
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
   Player::currentPlayerScore += getEnemyScore(enemy);
   /*#ifdef _DEBUG
         std::cout << "totalScore: " << Player::currentPlayerScore << std::endl;
   #endif*/
}