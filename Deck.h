/*
  File: Deck.h
  Description: Deck class for the War card game
*/

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>

class Deck {
public:
    // Constructor that creates a shuffled 52-card deck
    Deck(std::default_random_engine& gen);
    
    // Draw a card from the deck; returns nullptr if empty
    Card* draw();
    
    // Check if deck is empty
    bool empty() const { return cards.empty(); }
    
    // Get number of cards remaining
    size_t size() const { return cards.size(); }

private:
    std::vector<Card*> cards;
};

#endif