#include "HigherLowerGame.hpp"
#include "iostream"
#include "SDLApp.hpp"

// function was used when game was still cli to provide
// a snapshot of the current state of the game to the player
void printGameState(const HigherLowerGame& game){
    std::cout<<"\n========================================\n";
    std::cout<<"Current Card: " << game.getCurrentCard().toString()<<"\n";
    std::cout<<"Hearts: " << game.getHearts() <<"\n";
    std::cout<<"Score: " << game.getScore() <<"\n";
    std::cout<<"Multiplier: " << game.getStreakMultiplier() <<"x\n";
    std::cout<<"Cards remaining: " << game.getCardsRemaining()<<"\n";
    std::cout<<"========================================\n";
}

int main(){
    SDLApp app;
    
    // init all SLD and game subsystems before entering 
    // the main application loop
    if (!app.initialise()){
        std::cerr<<"Failed to initialise game"<<std::endl;
        return 1;
    }

    // run the application until the user exits
    app.run();

    return 0;
}