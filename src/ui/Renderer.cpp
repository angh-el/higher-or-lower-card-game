#include "Renderer.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

Renderer::Renderer(SDL_Renderer* ren) : renderer(ren), font(nullptr){}

Renderer::~Renderer(){
    cleanup();
}

bool Renderer::initialise(){
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return false;
    }
    
    // Load default font
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (!font) {
        font = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 24);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            return false;
        }
    }
    
    return true;
}

SDL_Texture* Renderer::loadTexture(const std::string& path) {
    if (textures.find(path) != textures.end()) {
        return textures[path];
    }
    
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image "<<path<<": "<<IMG_GetError()<<std::endl;
        return nullptr;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (texture) {
        textures[path] = texture;
    }
    
    return texture;
}

std::string Renderer::getCardImagePath(const Card& card) const {
    std::string suit;
    switch(card.getSuit()) {
        case Suit::Hearts: suit = "Hearts"; break;
        case Suit::Diamonds: suit = "Diamonds"; break;
        case Suit::Clubs: suit = "Clubs"; break;
        case Suit::Spades: suit = "Spades"; break;
    }
    
    std::string rank;
    switch(card.getRank()) {
        case Rank::Two: rank = "2"; break;
        case Rank::Three: rank = "3"; break;
        case Rank::Four: rank = "4"; break;
        case Rank::Five: rank = "5"; break;
        case Rank::Six: rank = "6"; break;
        case Rank::Seven: rank = "7"; break;
        case Rank::Eight: rank = "8"; break;
        case Rank::Nine: rank = "9"; break;
        case Rank::Ten: rank = "10"; break;
        case Rank::Jack: rank = "J"; break;
        case Rank::Queen: rank = "Q"; break;
        case Rank::King: rank = "K"; break;
        case Rank::Ace: rank = "A"; break;
    }
    
    return "assets/card" + suit + rank + ".png";
}

std::string Renderer::getDiceImagePath(int diceValue) const {
    return "assets/dieWhite_border" + std::to_string(diceValue) + ".png";
}

void Renderer::renderText(const std::string& text, int x, int y, SDL_Color color, bool centered) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect destRect;
    destRect.w = surface->w;
    destRect.h = surface->h;
    
    if (centered) {
        destRect.x = x - destRect.w / 2;
        destRect.y = y - destRect.h / 2;
    } else {
        destRect.x = x;
        destRect.y = y;
    }
    
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::renderTopBar(double multiplier, int score, int hearts) {
    SDL_Color white = {255, 255, 255, 255};
    
    // Left: Multiplier
    std::string multText = "x" + std::to_string(multiplier).substr(0, 3);
    renderText(multText, 100, 40, white, true);
    
    // Center: Score
    std::string scoreText = "Score: " + std::to_string(score);
    renderText(scoreText, 400, 40, white, true);
    
    // Right: Hearts
    std::string heartsText = std::to_string(hearts) + " Hearts";
    renderText(heartsText, 700, 40, white, true);
}

void Renderer::renderCards(const Card& currentCard, bool showNextCard) {
    // Current card (left side)
    std::string currentCardPath = getCardImagePath(currentCard);
    SDL_Texture* currentTexture = loadTexture(currentCardPath);
    
    if (currentTexture) {
        SDL_Rect cardRect = {80, 200, 120, 168}; // Standard card aspect ratio
        SDL_RenderCopy(renderer, currentTexture, nullptr, &cardRect);
    }
    
    // Next card (right side) - face down or face up
    std::string nextCardPath = showNextCard ? getCardImagePath(currentCard) : "assets/cardBack_green3.png";
    SDL_Texture* nextTexture = loadTexture(nextCardPath);
    
    if (nextTexture) {
        SDL_Rect cardRect = {220, 200, 120, 168};
        SDL_RenderCopy(renderer, nextTexture, nullptr, &cardRect);
    }
    
    // Labels
    SDL_Color white = {255, 255, 255, 255};
    renderText("Current", 140, 380, white, true);
    renderText("Next", 280, 380, white, true);
}

void Renderer::renderDice(int diceValue, const std::string& effectText) {
    if (diceValue > 0) {
        std::string dicePath = getDiceImagePath(diceValue);
        SDL_Texture* diceTexture = loadTexture(dicePath);
        
        if (diceTexture) {
            SDL_Rect diceRect = {500, 200, 100, 100};
            SDL_RenderCopy(renderer, diceTexture, nullptr, &diceRect);
        }
        
        // Render effect text below dice
        if (!effectText.empty()) {
            SDL_Color yellow = {255, 255, 0, 255};
            
            // Split text into multiple lines if needed
            int yOffset = 320;
            size_t pos = 0;
            std::string remaining = effectText;
            
            while (pos < remaining.length()) {
                std::string line;
                if (remaining.length() - pos > 20) {
                    size_t spacePos = remaining.find(' ', pos + 15);
                    if (spacePos != std::string::npos && spacePos < pos + 25) {
                        line = remaining.substr(pos, spacePos - pos);
                        pos = spacePos + 1;
                    } else {
                        line = remaining.substr(pos, 20);
                        pos += 20;
                    }
                } else {
                    line = remaining.substr(pos);
                    pos = remaining.length();
                }
                
                renderText(line, 550, yOffset, yellow, true);
                yOffset += 30;
            }
        }
    }
}

void Renderer::cleanup() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
    
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    
    TTF_Quit();
}