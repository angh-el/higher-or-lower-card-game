#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>

enum class Suit {Hearts, Diamonds, Clubs, Spades};
enum class Rank {Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13, Ace=14};

class Card{
private:
    Rank rank;
    Suit suit;

public:
    Card(Rank r, Suit s);
    std::string toString() const;
    bool isRed() const;

    void increaseRank();
    void decreaseRank();

    Rank getRank() const;
    Suit getSuit() const;    
};

#endif