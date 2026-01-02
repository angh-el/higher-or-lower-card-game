# higher-or-lower-card-game
Higher or Lower Card Game with a Unique Twist

---
Aim of the game:
- Get the highest score
- Game ends when player runs out of hearts

Rules:
- Player starts with 3 hearts
- Dealer draws a card from the top of the deck and player guesses if next card is higher or lowere
- Correct guesses increase the score by 10 x multiplier
- Multiplier starts at 1.0, for each correct guess +.1 (capped at 2), for wrong guess gets reset to 1.0
- Wrong guesses lose a heart
- If the drawn card rank is the same as the current card rank player gets +1 heart
- If the colour of the drawn suit is the same as the current card colour player rolls a die
- Roll effects:
	- 1 : next card has a value of +1 (capped at Ace)
	- 2 : next card has a value of -1 (capped at 2)
	- 3 : x2 multiplier to next guess
	- 4 : look at next card
	- 5 : +1 heart
	- 6 : nothing
- If the player finishes the deck, the deck gets re shuffled and player gets +3 hearts
- So game can potentially run for infinity
