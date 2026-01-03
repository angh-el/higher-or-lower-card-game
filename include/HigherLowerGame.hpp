#ifndef HIGHERLOWERGAME_HPP
#define HIGHERLOWERGAME_HPP

#include "Card.hpp"
#include "Deck.hpp"

/** 
 * represents the players guess for the next card
*/
enum class Guess {Higher, Lower};

/**
 * represents all possible die outcomes
 * explicit numeric values -> direct mapping for a 
 * dice roll (no need for translating)
 */
enum class DiceEffect {RankPlusOne=1, RankMinusOne=2, MultiplierTimesTwo=3, PeekNextCard=4, GainHeart=5, NoEffect=6};

/** 
 * represnet the outcome of a single round
 * this struct is solely uses to decouple game logic fromt he ui layer
 * the renderer displays the current game state without inspecting the 
 * actual internal state of the game
*/
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

/**
 * the central game controller f
 * this class owns and coordinates all gameplay state:
 * deck, scoring, hearts, multipliers and tracks the rounf
 * it deliberately has a minimal public api so that the ui
 * can drive the game without duplicating rules
 */
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

    // state related to dice peek effect
    bool peekedCard;
    Card nextCardPeeked;

    // cache the result of the most recent round to be consumed by the ui
    RoundResult lastRoundResult;

    // simulates a six sided dice roll
    int rollDice();

    // applies the effect of the dice roll to the round
    void applyDiceEffect(DiceEffect effect, Card& nextCard, std::string& effectText);
    std::string getDiceEffectText(DiceEffect effect) const;
    
    // evaluate if player guess was correct
    bool evaluateGuess(Guess guess, Card& current, Card& next);
    
    void updateScore(bool correct);

public:
    // initilises a new game and sets the default player state and draws the initial card
    HigherLowerGame();
    
    void processGuess(Guess guess);

    // read only getters
    Card getCurrentCard() const;
    int getHearts() const;
    int getScore() const;
    double getStreakMultiplier() const;
    bool isGameOver() const;
    size_t getCardsRemaining() const;

    // returns the cached result of the most recent round
    // allows ui to render feedback without re doing the logic
    RoundResult getLastRoundResult() const;
};

#endif