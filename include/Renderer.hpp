#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include "Card.hpp"

class Renderer{
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::unordered_map<std::string, SDL_Texture*> textures;
    
    SDL_Texture* loadTexture(const std::string& path);
    void renderText(const std::string& text, int x, int y, SDL_Color colour, bool centered=false);
    std::string getCardImagePath(const Card& card) const;
    std::string getDiceImagePath(int diceValue) const;

public:
    Renderer(SDL_Renderer * ren);
    ~Renderer();
    
    bool initialise();
    void clear();
    void present();

    // functions to render the game elemetns
    void renderTopBar(double multiplier, int score, int hearts);
    void renderCards(const Card& currentCard, bool showNextCard);
    void renderDice(int diceValue, const std::string& effectText);

    void cleanup();

};


#endif