/*
  File: Card.h
  Description: Card class for the War card game
*/

#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit { clubs, diamonds, hearts, spades };
enum class Value { 
    deuce, trey, four, five, six, seven, eight, nine, ten, 
    jack, queen, king, ace 
};

class Card {
public:
    Card(Value faceValue = Value::deuce, Suit suit = Suit::clubs)
        : suit(suit), faceValue(faceValue) {}
    
    Suit getSuit() const { return suit; }
    Value getValue() const { return faceValue; }
    
    static std::string suitName(Suit s);
    static std::string valueName(Value v);
    std::string name() const { 
        return valueName(faceValue) + " of " + suitName(suit); 
    }

private:
    Suit suit;
    Value faceValue;
};

#endif