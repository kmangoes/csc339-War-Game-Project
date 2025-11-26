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

std::string Card::suitSymbol(Suit s) {
    switch(s) {
        case Suit::clubs: return "\u2663";    // ♣
        case Suit::diamonds: return "\u2666"; // ♦
        case Suit::hearts: return "\u2665";   // ♥
        case Suit::spades: return "\u2660";   // ♠
        default: return "?";
    }
}

std::string Card::valueSymbol(Value v) {
    switch(v) {
        case Value::ace: return "A";
        case Value::deuce: return "2";
        case Value::trey: return "3";
        case Value::four: return "4";
        case Value::five: return "5";
        case Value::six: return "6";
        case Value::seven: return "7";
        case Value::eight: return "8";
        case Value::nine: return "9";
        case Value::ten: return "10";
        case Value::jack: return "J";
        case Value::queen: return "Q";
        case Value::king: return "K";
        default: return "?";
    }
}

std::string Card::art() const {
    std::string val = valueSymbol(faceValue);
    std::string s = suitSymbol(suit);
    
    // Pad single-character values for alignment
    std::string topVal = (val.length() == 1) ? val + " " : val;
    std::string botVal = (val.length() == 1) ? " " + val : val;
    
    std::string result;
    result += ".---------.\n";
    result += "|" + topVal + "       |\n";
    result += "|         |\n";
    result += "|    " + s + "    |\n";
    result += "|         |\n";
    result += "|       " + botVal + "|\n";
    result += "'---------'";
    
    return result;
}