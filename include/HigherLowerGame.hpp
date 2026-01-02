#ifndef HIGHERLOWERGAME_HPP
#define HIGHERLOWERGAME_HPP

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
    int basePoints;
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

    void startNewRound();
    void processGuess(Guess guess);

    Card getCurrentCard() const;
    int getHearts() const;
    int getScore() const;
    double getStreakMultiplier() const;
    bool isGameOver() const;
    size_t getCardsRemaining() const;
    std::string getDiceEffect() const;
};

#endif