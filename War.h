/*
  File: war.h
  Description: War class header for the War card game
*/

#ifndef WAR_H
#define WAR_H

#include "Deck.h"
#include <queue>
#include <vector>
#include <random>

// Required enum class for game state
enum class WinState { winA, winB, tie, ongoing };

// Private enum for tracking sub-round state
enum class PlayState { normal, warDown, warUp };

class War {
public:
    // Constructor
    War(std::default_random_engine& _gen);
    
    // Play one round of War
    WinState playRound();

private:
    std::default_random_engine& gen;
    Deck deck;
    
    // Player hands using queues (pop from front, push to back)
    std::queue<Card*> handA;
    std::queue<Card*> handB;
    
    // Cards in the middle during a round/war
    std::vector<Card*> middle;
    
    // Current state of play
    PlayState playState;
    
    // Helper methods
    WinState subRound();
    std::pair<Card*, Card*> placeCards();
    void collectRound(std::queue<Card*>& to);
    WinState checkForWin();
    void updateState(bool cardsMatch);
};

#endif