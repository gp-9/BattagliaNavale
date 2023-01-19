#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "../include/Prompt/Prompt.h"
#include "../include/Board/Board.h"

int main (int argc, char *argv[]){
    std::ifstream myFile_pc_write;
    std::ofstream myFile_pc_read;
    std::ifstream myFile_cc_write;
    std::ofstream myFile_cc_read;
    std::ofstream myFile_output;
    BattleShip::Board _board {};
    myFile_pc_write.open("../logFiles/pcLogFile.txt");
    myFile_cc_write.open("../logFiles/ccLogFile.txt");
    myFile_output.open("../logFiles/replay_output.txt");
    BattleShip::Prompt prompt;
    std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomturn(0, 1);
    bool exited = false;
    int startturn;
    std::string s;
    if (argc == 1){
        std::cout << "Nessun argomento fornito" << std::endl;
    }else if ((argc == 2 && std::string(argv[1]) == "v" ) || (argc == 2 && std::string(argv[1]) == "f")) {
        std::cout << "Nessun file fornito" << std::endl;
    }else if(argc == 3 && std::string(argv[1]) == "v"){
        if(std::string(argv[2]) == "./logFiles/pcLogFile.txt"){
            getline(myFile_pc_write, s);
            if(s[1] == '1'){
                startturn = 0;
            }else startturn = 1;

            myFile_pc_write.seekg(0);
            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);
            if(player1 < player2) {
                exited = prompt.setUpBoardHumanForReplay(player1, myFile_pc_write); 
                if(!exited) {
                    std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n";
                    prompt.setUpBoardBotForReplay(player2, myFile_pc_write);
                }
                
                int moves = 0;
                while(!exited) {   
                    exited = prompt.playGameForReplay(player1, BattleShip::human, player2, BattleShip::bot, startturn, moves, myFile_pc_write);
                    moves++;
                }
                myFile_pc_write.close();
            } else {

            prompt.setUpBoardBotForReplay(player2, myFile_pc_write);
            exited = prompt.setUpBoardHumanForReplay(player1, myFile_pc_write);
            int moves = 0;
            while(!exited) {
                exited = prompt.playGameForReplay(player2, BattleShip::bot, player1, BattleShip::human, startturn, moves, myFile_pc_write);
                moves++;
            }
            myFile_pc_write.close();
            }
        
        }else if(std::string(argv[2]) == "./logFiles/ccLogFile.txt"){
            getline(myFile_cc_write, s);
            if(s[1] == '1'){
                startturn = 0;
            }else startturn = 1;

            myFile_cc_write.seekg(0);

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);
            prompt.setUpBoardBotForReplay(player1, myFile_cc_write);
            prompt.setUpBoardBotForReplay(player2, myFile_cc_write);
            int moves = 0;
            while(!exited) {
                exited = prompt.playGameForReplay(player1, BattleShip::bot, player2, BattleShip::bot, startturn, moves, myFile_cc_write);
                moves++;
            }
            myFile_cc_write.close();
        }
    }else if(argc == 4 && std::string(argv[1]) == "f"){
        if(std::string(argv[2]) == "./logFiles/pcLogFile.txt" && std::string(argv[3]) == "./logFiles/replay_output.txt"){
            std::string line;
            getline(myFile_pc_write, line);
            if(line[1] == '1'){
                startturn = 0;
            }else startturn = 1;

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);

            myFile_pc_write.seekg(0);
            if(player1 < player2) {
                exited = prompt.setUpBoardHumanForReplayOut(player1, myFile_pc_write, myFile_output); 
                if(!exited) {
                    exited = prompt.setUpBoardBotForReplayOut(player2, myFile_pc_write, myFile_output);
                }
                
                int moves = 0;
                while(!exited) {   
                    exited = prompt.playGameForReplayOut(player1, BattleShip::human, player2, BattleShip::bot, startturn, moves, myFile_pc_write, myFile_output);
                    moves++;
                }
                myFile_pc_write.close();
                myFile_output.close();
            } else {

                exited = prompt.setUpBoardHumanForReplayOut(player1, myFile_pc_write, myFile_output);
                int moves = 0;
                while(!exited) {
                    exited = prompt.playGameForReplayOut(player2, BattleShip::bot, player1, BattleShip::human, startturn, moves, myFile_pc_write, myFile_output);
                    moves++;
                }
                myFile_pc_write.close();
                myFile_output.close();
            }
        }else if(std::string(argv[2]) == "./logFiles/ccLogFile.txt" && std::string(argv[3]) == "./logFiles/replay_output.txt"){
            std::string line;
            getline(myFile_cc_write, line);
            if(line[1] == '1'){
                startturn = 0;
            }else startturn = 1;

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);
            myFile_pc_write.seekg(0);
            int moves = 0;
            while(!exited) {
                exited = prompt.playGameForReplayOut(player1, BattleShip::bot, player2, BattleShip::bot, startturn, moves, myFile_cc_write, myFile_output);
                moves++;
            }
            myFile_cc_write.close();
            myFile_output.close(); 

        }else std::cout << "Comando non valido!";
    }else{
        std::cout << "Comando non valido!" << std::endl;
    }
}