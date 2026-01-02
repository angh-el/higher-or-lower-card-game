#ifndef HIGHERORLOWERGAME_HPP
#define HIGHERORLOWERGAME_HPP

#include "Card.hpp"
#include "Deck.hpp"

enum class Guess {Higher, Lower};
enum class DiceEffect {RankPlusOne=1, RankMinusOne=2, MultiplierTimesTwo=3, PeekNextCard=4, GainHeart=5, NoEffect=6};

class HigherLowerGame{
private:
    Deck deck;
    Card currentCard;
    int hearts;
    int score;
    double streakMultiplier;
    double dieMultiplier;

    bool gameOver;
    bool peekedCard;
    Card nextCardPeeked;

    int rollDice();
    void applyDiceEffect(DiceEffect effect, Card& nextCard);
    bool evaluateGuess(Guess guess, Card& current, Card& next);
    void updateScore(bool correct);

public:
    HigherLowerGame();
    

};

#endif