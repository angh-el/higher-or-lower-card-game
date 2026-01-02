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

    shuffle();
}

void Deck::shuffle(){
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::shuffle(cards.begin(), cards.end(), generator);
}

bool Deck::isEmpty() const{
    return currentIdx >= cards.size();
}

Card Deck::draw(){
    // if(isEmpty()){
    //     std::cout<<"Deck is empty now, cannot draw\n";
    //     return;
    // }

    return cards[currentIdx++];
}

void Deck::reset(){
    currentIdx = 0;
    shuffle();
}

Card Deck::peek() const{
    if (isEmpty()){
        std::cout<<"Deck is empty now, cannot peek\n";
    }

    return cards[currentIdx];
}

size_t Deck::cardsRemaining() const{
    return cards.size() - currentIdx;
}