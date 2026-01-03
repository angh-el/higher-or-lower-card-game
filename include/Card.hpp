#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>


/**
 * represent the suits
 * defined as enum to prevent accidental misuse
 * it also enforces type safety throught the game logic
 */
enum class Suit {Hearts, Diamonds, Clubs, Spades};

/**
 * represents card ranks by asigning each rank to an integer
 * explicit integer values allow for easier rank comparisons and arithmetic
 */
enum class Rank {Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13, Ace=14};


/**
 * models a single immutable card
 * class intentionally contains only card related logic
 * clear separation from game logic, scoring, etc
 * -> loosly coupled
 * 
 * if new rulesets or gamemodes would be added this would still stay the same
 */
class Card{
private:
    Rank rank;
    Suit suit;

public:
    // just creates a card (no validation as the deck is responsible for making sure the combination is valid)
    Card(Rank r, Suit s);

    // returns a readable representation of the card, mostly used for the ui
    std::string toString() const;
    
    // functions that support the die rolling aspect
    bool isRed() const;
    void increaseRank();
    void decreaseRank();

    // getters
    Rank getRank() const;
    Suit getSuit() const;    
};

#endif