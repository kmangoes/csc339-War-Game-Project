/*
  File: Card.cpp
  Description: Card class implementation
*/

#include "Card.h"
#include <stdexcept>

std::string Card::suitName(Suit s) {
    switch(s) {
        case Suit::clubs: return "Clubs";
        case Suit::diamonds: return "Diamonds";
        case Suit::hearts: return "Hearts";
        case Suit::spades: return "Spades";
        default: throw std::out_of_range("Suit value out of range");
    }
}

std::string Card::valueName(Value v) {
    switch(v) {
        case Value::ace: return "Ace";
        case Value::deuce: return "Deuce";
        case Value::trey: return "Trey";
        case Value::four: return "Four";
        case Value::five: return "Five";
        case Value::six: return "Six";
        case Value::seven: return "Seven";
        case Value::eight: return "Eight";
        case Value::nine: return "Nine";
        case Value::ten: return "Ten";
        case Value::jack: return "Jack";
        case Value::queen: return "Queen";
        case Value::king: return "King";
        default: throw std::out_of_range("Face value out of range");
    }
}