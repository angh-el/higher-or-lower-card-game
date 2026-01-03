#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"
#include <vector>

/**
 * models a standard deck of playing cards (without Jokers)
 * 
 * deck is responsible for card ownership, ordering and draw state
 * contains no game logic
 */
class Deck{
private:
    /**
     * cards are stored in a flat container and accessed sequentially
     * using an index ranther than removing elements
     * this avoids unnecessary memory churn once the deck would be finished
     * and had to be reshuffled
     * 
     * index acts as a cursor the traverses the vector
     * this simplifies shuffling and peeking to the next card
     */
    std::vector<Card> cards;
    size_t currentIdx;

public:
    /**
     * constructs the 52 card deck
     * card creation is centralised here to ensure deck validity
     * and to make sure that all cards follow consistent rank and suit rules
     * the deck is shuffled once created.
     */
    Deck();

    /**
     * randomises the order of the cards in the deck
     * shuffling is separated from the construction 
     * so that gmae logic can specify when it wants for 
     * the randomness to be applies
     */
    void shuffle();

    /**
     * draws the next card from the deck by incrementing the cursor(currentIdx)
     */
    Card draw();

    /**
     * check to ensure next card can be drawn, else reset cursor and shuffle deck again
     */
    bool isEmpty() const;
    void reset();
    size_t cardsRemaining() const;

    /**
     * return next card without consumning it
     * used as for one of the effects of the die
     */
    Card peek() const;
};

#endif