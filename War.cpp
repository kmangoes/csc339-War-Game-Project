/*
  File: war.cpp
  Description: War class implementation
*/

#include "war.h"
#include <iostream>
#include <algorithm>

// Constructor: initialize gen and deck, then deal cards to players
War::War(std::default_random_engine& _gen) 
    : gen(_gen), deck(_gen), playState(PlayState::normal) {
    
    // Deal cards alternately to each player
    std::queue<Card*>* current = &handA;
    std::queue<Card*>* other = &handB;
    
    Card* card = deck.draw();
    while (card != nullptr) {
        current->push(card);
        std::swap(current, other);
        card = deck.draw();
    }
}

// Place each player's top card into the middle, return the pair
std::pair<Card*, Card*> War::placeCards() {
    Card* cardA = handA.front();
    handA.pop();
    Card* cardB = handB.front();
    handB.pop();
    
    middle.push_back(cardA);
    middle.push_back(cardB);
    
    return {cardA, cardB};
}

// Shuffle the middle cards and give them to the winning player
void War::collectRound(std::queue<Card*>& to) {
    std::shuffle(middle.begin(), middle.end(), gen);
    
    while (!middle.empty()) {
        to.push(middle.back());
        middle.pop_back();
    }
}

// Check if the game is over and return appropriate WinState
WinState War::checkForWin() {
    if (handA.empty() && handB.empty()) {
        std::cout << "Both players are out of cards; it's a tie." << std::endl;
        return WinState::tie;
    }
    else if (handA.empty()) {
        std::cout << "Player A is out of cards; player B wins." << std::endl;
        return WinState::winB;
    }
    else if (handB.empty()) {
        std::cout << "Player B is out of cards; player A wins." << std::endl;
        return WinState::winA;
    }
    return WinState::ongoing;
}

// Update the play state based on whether cards matched
void War::updateState(bool cardsMatch) {
    if (playState == PlayState::normal) {
        if (cardsMatch) {
            std::cout << "Cards have same value. War!" << std::endl;
            playState = PlayState::warDown;
        }
        // If cards don't match, stay in normal state (round is over)
    }
    else if (playState == PlayState::warDown) {
        // After face-down cards, next is face-up comparison
        playState = PlayState::warUp;
    }
    else if (playState == PlayState::warUp) {
        if (cardsMatch) {
            std::cout << "Cards have same value. War continues." << std::endl;
            playState = PlayState::warDown;
        }
        else {
            // War is over, reset to normal
            playState = PlayState::normal;
        }
    }
}

// Execute one sub-round of play
WinState War::subRound() {
    bool cardsMatch = false;
    
    if (playState == PlayState::normal || playState == PlayState::warUp) {
        // Check if players have cards to play
        if (handA.empty()) {
            std::cout << "Player A is out of cards; player B wins." << std::endl;
            return WinState::winB;
        }
        if (handB.empty()) {
            std::cout << "Player B is out of cards; player A wins." << std::endl;
            return WinState::winA;
        }
        
        // Place face-up cards
        auto [cardA, cardB] = placeCards();
        
        std::cout << "Player A plays " << cardA->name() << std::endl;
        std::cout << "Player B plays " << cardB->name() << std::endl;
        
        // Compare cards
        if (cardA->getValue() > cardB->getValue()) {
            if (playState == PlayState::warUp) {
                std::cout << "Player A has the higher card and wins the war." << std::endl;
            } else {
                std::cout << "Player A has the higher card and wins the round." << std::endl;
            }
            collectRound(handA);
        }
        else if (cardB->getValue() > cardA->getValue()) {
            if (playState == PlayState::warUp) {
                std::cout << "Player B has the higher card and wins the war." << std::endl;
            } else {
                std::cout << "Player B has the higher card and wins the round." << std::endl;
            }
            collectRound(handB);
        }
        else {
            // Cards match - don't collect yet
            cardsMatch = true;
        }
    }
    else if (playState == PlayState::warDown) {
        // Check if players have cards for face-down
        if (handA.empty()) {
            std::cout << "Player A is out of cards; player B wins." << std::endl;
            // Give any middle cards to player B
            collectRound(handB);
            return WinState::winB;
        }
        if (handB.empty()) {
            std::cout << "Player B is out of cards; player A wins." << std::endl;
            // Give any middle cards to player A
            collectRound(handA);
            return WinState::winA;
        }
        
        std::cout << "Players playing one card each, face down..." << std::endl;
        
        // Place face-down cards (no comparison)
        placeCards();
    }
    
    // Check for win after collecting
    WinState result = checkForWin();
    
    // Update state if game is not over
    if (result == WinState::ongoing) {
        updateState(cardsMatch);
    }
    
    return result;
}

// Play one complete round (including any wars)
WinState War::playRound() {
    playState = PlayState::normal;
    
    WinState result;
    do {
        result = subRound();
    } while (result == WinState::ongoing && playState != PlayState::normal);
    
    // Print card counts at end of round if game continues
    if (result == WinState::ongoing) {
        std::cout << "(Player A has " << handA.size() << " cards; "
                  << "player B has " << handB.size() << " cards.)" << std::endl;
    }
    
    return result;
}