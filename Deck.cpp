/*
  File: Deck.cpp
  Description: Deck class implementation
*/

#include "Deck.h"
#include <algorithm>

Deck::Deck(std::default_random_engine& gen) {
    // Create all 52 cards
    for (int s = 0; s < 4; ++s) {
        for (int v = 0; v < 13; ++v) {
            cards.push_back(new Card(static_cast<Value>(v), static_cast<Suit>(s)));
        }
    }
    
    // Shuffle the deck
    std::shuffle(cards.begin(), cards.end(), gen);
}

Card* Deck::draw() {
    if (cards.empty()) {
        return nullptr;
    }
    Card* card = cards.back();
    cards.pop_back();
    return card;
}