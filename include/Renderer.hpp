#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include "Card.hpp"


/**
 * handles all rendering needed for the ui
 * the class as an abstraction over SDL, it translates
 * the game state into visual output without owning or
 * modifying the gameplay logic
 * class is stateless (in regrads to game rules)
 */
class Renderer{
private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    /**
     * cache of loaded textures where key is file paths
     * this is an optimisation to avoid repeatedly re loading the same
     * assets from the disk,
     * which would cause overhead
     */
    std::unordered_map<std::string, SDL_Texture*> textures;
    
    /**
     * loads an image as an SDL texture and caches it
     * centralising texture loading ensures consistent
     * asset usage and prevents duplicated resource management logic
     */
    SDL_Texture* loadTexture(const std::string& path);
    
    // renders text on screen at a given position 
    void renderText(const std::string& text, int x, int y, SDL_Color colour, bool centered=false);
    
    // functions to get the path of an asset
    std::string getCardImagePath(const Card& card) const;
    std::string getDiceImagePath(int diceValue) const;

public:
    // constructs a rendered using SDL_Renderer
    // ownership of the renderer remains externals so that
    // the context management can be handles elsewhere
    Renderer(SDL_Renderer * ren);

    // make sure allocated resources are released
    ~Renderer();
    
    // initialises the font and rendering subsystems
    bool initialise();
    
    // clears the screen before a new frame
    void clear();

    // present new rendered frame to the screen
    void present();

    // functions to render the game elemetns
    void renderTopBar(double multiplier, int score, int hearts);
    void renderCards(const Card& currentCard, bool showNextCard);
    void renderDice(int diceValue, const std::string& effectText);

    void cleanup();

};


#endif