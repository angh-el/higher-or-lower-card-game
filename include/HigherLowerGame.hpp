#ifndef HIGHERLOWERGAME_HPP
#define HIGHERLOWERGAME_HPP

#include "Card.hpp"
#include "Deck.hpp"

enum class Guess {Higher, Lower};
enum class DiceEffect {RankPlusOne=1, RankMinusOne=2, MultiplierTimesTwo=3, PeekNextCard=4, GainHeart=5, NoEffect=6};
struct RoundResult{
    bool wasCorrect;
    bool wasTie;
    bool wasColourMatch;
    int diceRoll;
    std::string diceEffectText;
    Card nextCard;

    RoundResult(bool correct,
                bool tie,
                bool colourMatch,
                int roll,
                const std::string& effectText,
                const Card& card)
        : wasCorrect(correct),
          wasTie(tie),
          wasColourMatch(colourMatch),
          diceRoll(roll),
          diceEffectText(effectText),
          nextCard(card) {}

};

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

    RoundResult lastRoundResult;

    int rollDice();
    void applyDiceEffect(DiceEffect effect, Card& nextCard, std::string& effectText);
    bool evaluateGuess(Guess guess, Card& current, Card& next);
    void updateScore(bool correct);
    std::string getDiceEffectText(DiceEffect effect) const;

public:
    HigherLowerGame();

    // void startNewRound();
    void processGuess(Guess guess);

    Card getCurrentCard() const;
    int getHearts() const;
    int getScore() const;
    double getStreakMultiplier() const;
    bool isGameOver() const;
    size_t getCardsRemaining() const;
    // std::string getDiceEffect() const;

    // for the gui
    RoundResult getLastRoundResult() const;
};

#endif