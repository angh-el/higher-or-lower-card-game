#include "HigherLowerGame.hpp"
#include "iostream"
#include "SDLApp.hpp"

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
    // std::cout<<"Welcome to Higher-or-Lower\n";

    // HigherLowerGame game;

    // while(!game.isGameOver()){
    //     printGameState(game);
    //     std::cout<<"Guess: (H)igher or (L)ower\n";
    //     std::string input;
    //     std::getline(std::cin, input);

    //     if(input.empty()) continue;
    //     char choice = std::tolower(input[0]);

    //     if(choice == 'h'){
    //         game.processGuess(Guess::Higher);
    //     }
    //     else if(choice == 'l'){
    //         game.processGuess(Guess::Lower);
    //     }
    //     else if(choice == 'q'){
    //         std::cout<<"Thank you for playing! Final Score: "<<game.getScore()<<"\n";
    //     }
    //     else{
    //         std::cout<<"Invalid input\n";
    //     }

    //     if (game.isGameOver()){
    //         std::cout<<"Game Over! Final Score: "<<game.getScore()<<"\n";
    //     }

    // }

    SDLApp app;
    if (!app.initialise()){
        std::cerr<<"Failed to initialise game"<<std::endl;
        return 1;
    }

    app.run();
    app.cleanup();

    return 0;
}