#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "../include/Prompt/Prompt.h"

#define F_ARGUMENT "f"
#define V_ARGUMENT "v"

int main (int argc, char *argv[]){
    BattleShip::Prompt prompt;
    std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomturn(0, 1);
	int startturn = randomturn(rng);
    std::string argument = argv[1];
    std::ifstream myFile_pc;
    std::ifstream myFile_cc;
    std::ofstream myFile_output;
    bool exited = false;

    myFile_pc.open("../logFiles/pcLogFile.txt");
    myFile_cc.open("../logFiles/ccLogFile.txt");
    myFile_output.open("../logFiles/replay_output.txt");

    if (argc == 1){
        std::cout << "Nessun argomento fornito" << std::endl;
    }else if (argc == 2 && argument == F_ARGUMENT || argc == 2 && argument == V_ARGUMENT) {
        std::cout << "Nessun file fornito" << std::endl;
    }else if(argc == 3 && argument == V_ARGUMENT){
        if(argv[2] == "../logFiles/pcLogFile.txt"){
            exited = prompt.setUpBoardHumanForReplay(BattleShip::p1, myFile_pc); 

            if(!exited) {
                std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n";
                prompt.setUpBoardBotForReplay(BattleShip::p2, myFile_pc);
            }

            while(!exited) {
                //TODO
                //exited = prompt.playGame(BattleShip::p1, BattleShip::human, BattleShip::p2, BattleShip::bot, startturn);
            }
        
            myFile_pc.close();
        }else if(argv[2] == "../logFiles/ccLogFile.txt"){
            exited = prompt.setUpBoardBotForReplay(BattleShip::p1, myFile_cc); 

            if(!exited) {
                std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n";
                prompt.setUpBoardBotForReplay(BattleShip::p2, myFile_cc);
            }

            while(!exited) {
                //TODO
                //exited = prompt.playGame(BattleShip::p1, BattleShip::human, BattleShip::p2, BattleShip::bot, startturn);
            }
        
            myFile_pc.close();
        }
    }else if(argc == 4 && argument == F_ARGUMENT){
        if(argv[2] == "../logFiles/ccLogFile.txt" && argv[3] == "../logFiles/replay_output.txt"){
            std::string line;
            getline(myFile_pc, line);
            myFile_output << line;
        }else if(argv[2] == "../logFiles/ccLogFile.txt" && argv[3] == "../logFiles/replay_output.txt"){
            std::string line;
            getline(myFile_cc, line);
            myFile_output << line;
        }else std::cout << "Comando non valido!";
    }else{
        std::cout << "Comando non valido!" << std::endl;
    }
}