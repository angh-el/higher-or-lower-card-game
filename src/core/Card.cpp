#include "Card.hpp"

Card::Card(Rank r, Suit s) : rank(r), suit(s){};

std::string Card::toString() const{
    std::string cardName {""};
    
    // add the rank
    switch(rank){
        case Rank::Two:     cardName += "2";  break;
        case Rank::Three:   cardName += "3";  break;
        case Rank::Four:    cardName += "4";  break;
        case Rank::Five:    cardName += "5";  break;
        case Rank::Six:     cardName += "6";  break;
        case Rank::Seven:   cardName += "7";  break;
        case Rank::Eight:   cardName += "8";  break;
        case Rank::Nine:    cardName += "9";  break;
        case Rank::Ten:     cardName += "10"; break;
        case Rank::Jack:    cardName += "J";  break;
        case Rank::Queen:   cardName += "Q";  break;
        case Rank::King:    cardName += "K";  break;
        case Rank::Ace:     cardName += "A";  break;
        default:            cardName += "???";break;
    }

    // add the suit
    switch (suit){
        case Suit::Hearts:      cardName += "H"; break;
        case Suit::Diamonds:    cardName += "D"; break;
        case Suit::Spades:      cardName += "S"; break;
        case Suit::Clubs:       cardName += "C"; break;
    }

    return cardName;
}

bool Card::isRed() const{
    return suit == Suit::Hearts || suit == Suit::Diamonds;
}

void Card::increaseRank(){
    if (rank != Rank::Ace){
        rank = static_cast<Rank>(static_cast<int>(rank) + 1);
    }
}

void Card::decreaseRank(){
    if (rank != Rank::Ace){
        rank = static_cast<Rank>(static_cast<int>(rank) - 1);
    }
}

Rank Card::getRank() const{
    return rank;
}

Suit Card::getSuit() const{
    return suit;
}