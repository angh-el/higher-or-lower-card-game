#include "SDLApp.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

SDLApp::SDLApp() : window(nullptr), sdlRenderer(nullptr), running(false), lastDiceRoll(0), showDice(false) {}

SDLApp::~SDLApp() {
    cleanup();
}

bool SDLApp::initialise() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialisation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image initialisation failed: " << IMG_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(
        "Higher or Lower Card Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = std::make_unique<Renderer>(sdlRenderer);
    if (!renderer->initialise()) {
        return false;
    }
    
    game = std::make_unique<HigherLowerGame>();
    
    running = true;
    return true;
}

void SDLApp::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN && !game->isGameOver()) {
            switch (event.key.keysym.sym) {
                case SDLK_h:
                    processGameGuess(Guess::Higher);
                    break;
                case SDLK_l:
                    processGameGuess(Guess::Lower);
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    running = false;
                    break;
            }
        }
        else if (event.type == SDL_KEYDOWN && game->isGameOver()) {
            // Press any key to exit when game is over
            running = false;
        }
    }
}

void SDLApp::processGameGuess(Guess guess) {
    game->processGuess(guess);
    
    RoundResult result = game->getLastRoundResult();
    
    if (result.wasColourMatch || !result.diceEffectText.empty()) {
        showDice = true;
        lastDiceRoll = result.diceRoll;
        lastDiceEffect = result.diceEffectText;
    } else {
        showDice = false;
        lastDiceRoll = 0;
        lastDiceEffect = "";
    }
}

void SDLApp::update() {
    // Game logic is handled in processGameGuess
}

void SDLApp::render() {
    renderer->clear();
    
    // Render top bar
    renderer->renderTopBar(
        game->getStreakMultiplier(),
        game->getScore(),
        game->getHearts()
    );
    
    // Render cards
    renderer->renderCards(game->getCurrentCard(), false);
    
    // Render dice if there was a colour match or special event
    if (showDice && lastDiceRoll > 0) {
        renderer->renderDice(lastDiceRoll, lastDiceEffect);
    } else if (showDice && !lastDiceEffect.empty()) {
        // For deck reshuffle or other events without dice
        renderer->renderDice(0, lastDiceEffect);
    }
    
    renderer->present();
}

void SDLApp::run() {
    std::cout << "Controls: Press 'H' for Higher, 'L' for Lower, 'ESC' or 'Q' to quit\n";
    
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16); 
    }
    
    std::cout << "Game ended! Final Score: " << game->getScore() << std::endl;
}

void SDLApp::cleanup() {
    if (renderer) {
        renderer->cleanup();
    }
    
    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
        sdlRenderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    IMG_Quit();
    SDL_Quit();
}