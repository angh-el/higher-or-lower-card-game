#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"
#include <vector>

class Deck{
private:
    std::vector<Card> cards;
    size_t currentIdx;

public:
    Deck();
    void initialise();
    void shuffle();
    Card draw();
    bool isEmpty() const;
    void reset();
    Card peek() const;
    size_t cardsRemaining() const;
};

#endif