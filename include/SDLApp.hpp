#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <SDL2/SDL.h>
#include <memory>
#include "HigherLowerGame.hpp"
#include "Renderer.hpp"

/**
 * owns and control the lifetime of the sdl app, it is responsible for:
 *  - initialising and closing sdl subsystems
 *  - driving the main game loop
 *  - routing user input to the game logic
 *  - delegating rendering to the rendere
 * does not contain game or rendering logic
 */
class SDLApp{
private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    
    // high level subsystems owned by the application
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<HigherLowerGame> game;

    bool running;

    // cached ui state derived from the last processed round
    int lastDiceRoll;
    std::string lastDiceEffect;
    bool showDice;
    
    // hadnles all sdl inputs + window events
    // input is translated into game actionas here
    // preventing sdl code from interfering with game logic
    void handleEvents();

    // rendered the current frame based on game state
    void render();
    
    // processe a player guess and updates the cached ui state
    // this wrapper method allows SDLApp to react to round results
    // without directly having access to the game state
    void processGameGuess(Guess guess);

public:
    // constructs application with no active SDL resources
    // initialisation is deffered to allow failure handling
    SDLApp();

    // ensures all owned resources are released when destroyed
    ~SDLApp();

    // initialises SDL, creates window and rendered 
    bool initialise();
    
    // runs the main application loop
    // function blocks until application exits
    void run();
    
    void cleanup();

};

#endif