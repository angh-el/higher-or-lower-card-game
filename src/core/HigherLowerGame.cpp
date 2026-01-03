#include "HigherLowerGame.hpp"
#include <random>

HigherLowerGame::HigherLowerGame() : 
        deck(), 
        currentCard(Rank::Ace, Suit::Spades), 
        hearts(3),
        score(0), 
        basePoints(10), 
        streakMultiplier(1.0), 
        dieMultiplier(1.0), 
        gameOver(false), 
        peekedCard(false), 
        nextCardPeeked(Rank::Ace, Suit::Spades), 
        lastRoundResult(false, false, false, 0, "", currentCard)
      {
    currentCard = deck.draw();
    lastRoundResult = {false, false, false, 0, "", currentCard};
};

int HigherLowerGame::rollDice(){
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    // static std::uniform_int_distribution<> dis(4, 4);
    return dis(generator);
}

std::string HigherLowerGame::getDiceEffectText(DiceEffect effect) const {
    switch(effect) {
        case DiceEffect::RankPlusOne:
            return "Next card rank +1!";
        case DiceEffect::RankMinusOne:
            return "Next card rank -1!";
        case DiceEffect::MultiplierTimesTwo:
            return "Score multiplier x2!";
        case DiceEffect::PeekNextCard:
            return "Peek at next card!";
        case DiceEffect::GainHeart:
            return "+1 Heart!";
        case DiceEffect::NoEffect:
            return "No effect";
        default:
            return "";
    }
}

void HigherLowerGame::applyDiceEffect(DiceEffect effect, Card& nextCard, std::string& effectText){
    effectText = getDiceEffectText(effect);
    
    switch(effect) {
        case DiceEffect::RankPlusOne:
            std::cout << "Dice Effect: Next card rank +1\n";
            nextCard.increaseRank();
            break;
        case DiceEffect::RankMinusOne:
            std::cout <<"Dice Effect: Next card rank -1\n";
            nextCard.decreaseRank();
            break;
        case DiceEffect::MultiplierTimesTwo:
            std::cout <<"Dice Effect: Score multiplier x2\n";
            dieMultiplier = 2.0;
            break;
        case DiceEffect::PeekNextCard:
            std::cout <<"Dice Effect: Peek at next card \n ";
            if (!deck.isEmpty()) {
                nextCardPeeked = deck.peek();
                peekedCard = true;
                std::cout << "Next card is: "<<nextCardPeeked.toString()<<"\n";
                effectText += nextCardPeeked.toString();
            }
            break;
        case DiceEffect::GainHeart:
            std::cout << "Dice Effect: +1 heart\n";
            hearts++;
            break;
        case DiceEffect::NoEffect:
            std::cout << "Dice Effect: No effect\n";
            break;
    }

    // effectText += "Yooo";
}

bool HigherLowerGame::evaluateGuess(Guess guess, Card& current,  Card& next){
    int currentRank = static_cast<int>(current.getRank());
    int nextRank = static_cast<int>(next.getRank());
    if(guess == Guess::Higher){
        return nextRank >= currentRank;
    }
    else{
        return nextRank <= currentRank;
    }
}

void HigherLowerGame::updateScore(bool correct){
    if (correct){
        double totalMultiplier = streakMultiplier * dieMultiplier;
        score += static_cast<int>(basePoints * totalMultiplier);
        streakMultiplier = std::min(2.0, streakMultiplier + 0.1);
    }
    else{
        streakMultiplier = 1.0;
        hearts--;
        if (hearts <= 0){
            gameOver = true;
        }
    }

    dieMultiplier = 1.0;
}

void HigherLowerGame::processGuess(Guess guess){
    if (gameOver) return;

    lastRoundResult = {false, false, false, 0, "", currentCard};

    if (deck.isEmpty()){
        std::cout<<"Deck is finished, reshuffling\n";
        deck.reset();
        hearts += 3;
        lastRoundResult.diceEffectText = "Deck reshuffled! +3 Hearts";
    }

    // draws the next card
    Card nextCard = deck.draw();

    // check if same rank 
    if (nextCard.getRank() == currentCard.getRank()){
        std::cout<<"Same rank, +1 heart\n";
        hearts++;
        lastRoundResult.wasTie = true;
        if (!lastRoundResult.diceEffectText.empty()){
            lastRoundResult.diceEffectText += "\nTIE! +1 Heart";
        } 
        else{
            lastRoundResult.diceEffectText = "TIE! Same rank! +1 Heart";
        }
    }

    // check if colours match
    bool colourMatch = currentCard.isRed() == nextCard.isRed();
    if(colourMatch){
        lastRoundResult.wasColourMatch = true;
        int diceRoll = rollDice();
        lastRoundResult.diceRoll = diceRoll;
        std::cout<<"Colour match, rolling dice ...\n";
        std::string effectText;
        DiceEffect effect = static_cast<DiceEffect>(diceRoll);
        applyDiceEffect(effect, nextCard, effectText);
        if (!lastRoundResult.diceEffectText.empty()) {
            lastRoundResult.diceEffectText += "\n" + effectText;
        } else {
            lastRoundResult.diceEffectText = effectText;
        }
    }

    peekedCard = false;

    bool correct = evaluateGuess(guess, currentCard, nextCard);
    lastRoundResult.wasCorrect = correct;
    lastRoundResult.nextCard = nextCard;
    
    std::cout<<"Next card: "<<nextCard.toString()<<"\n";

    if(correct) std::cout<<"Correct\n";
    else std::cout<<"Wrong\n";

    updateScore(correct);

    currentCard = nextCard;
    // std::cout << "Hearts: " << hearts << " | Score: " <<score<< " | Multiplier: " << std::fixed << streakMultiplier<< "\n";
    
    if(gameOver){
        std::cout<<"Game Over! Final Score: "<<score<<"\n";
    }
}

Card HigherLowerGame::getCurrentCard() const {return currentCard;}
int HigherLowerGame::getHearts() const {return hearts;}
int HigherLowerGame::getScore() const {return score;}
double HigherLowerGame::getStreakMultiplier() const {return streakMultiplier;}
bool HigherLowerGame::isGameOver() const {return gameOver;}
size_t HigherLowerGame::getCardsRemaining() const {return deck.cardsRemaining();}
RoundResult HigherLowerGame::getLastRoundResult() const {return lastRoundResult;}