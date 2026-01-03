#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <SDL2/SDL.h>
#include <memory>
#include "HigherLowerGame.hpp"
#include "Renderer.hpp"

class SDLApp{
private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<HigherLowerGame> game;

    bool running;

    int lastDiceRoll;
    std::string lastDiceEffect;
    bool showDice;

    void handleEvents();
    void update();
    void render();
    void processGameGuess(Guess guess);

public:
    SDLApp();
    ~SDLApp();

    bool initialise();
    void run();
    void cleanup();

};

#endif