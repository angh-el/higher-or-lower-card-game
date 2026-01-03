#include "Deck.hpp"
#include <random>
#include <algorithm>

Deck::Deck() : currentIdx(0){
    // initialise the deck by creating all 52 cards
    for (int s = 0; s < 4; s++){   // for each of the 4 suits ...
        Suit suit = static_cast<Suit>(s);
        for (int r = 2; r < 15; r++){       // for each of the rank cards 2 to 14 (Ace)
            Rank rank = static_cast<Rank>(r);
            cards.emplace_back(rank, suit);
        }
    }

    // shuffle immediately so deck is ready to use
    shuffle();
}

void Deck::shuffle(){
    // static random engine avoid generating new seed on every shuffle
    // trying to avoid unecessary overhead
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::shuffle(cards.begin(), cards.end(), generator);
}

bool Deck::isEmpty() const{
    // deck is considered empty when the cursor reaches the end
    return currentIdx >= cards.size();
}

Card Deck::draw(){
    // method is intentionally kept lightweight as it would be called often
    // user's responsibility to check if a draw is possible    
    return cards[currentIdx++];
}

void Deck::reset(){
    // cards are stored in memory so resetting the cursor is enough to reuse the deck
    currentIdx = 0;
    
    // reshuflle it so that it's not the same game again 
    shuffle();
}

Card Deck::peek() const{
    return cards[currentIdx];
}

size_t Deck::cardsRemaining() const{
    return cards.size() - currentIdx;
}