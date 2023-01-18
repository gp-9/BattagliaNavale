#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "../include/Prompt/Prompt.h"
#include "../include/Board/Board.h"

#define F_ARGUMENT "f"
#define V_ARGUMENT "v"

int main(int argc, char* argv[]){
    BattleShip::Prompt prompt;
    std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomturn(0, 1);
    std::string argument = argv[1];
    std::ifstream myFile_pc;
    std::ifstream myFile_cc;
    std::ofstream myFile_output;
    BattleShip::Board _board {};
    bool exited = false;
    int startturn;
    myFile_pc.open("../logFiles/pcLogFile.txt");
    myFile_cc.open("../logFiles/ccLogFile.txt");
    myFile_output.open("../logFiles/replay_output.txt");
    std::string file1 = "../logFiles/pcLogFile.txt";
    std::string file2 = "../logFiles/ccLogFile.txt";
    std::string file3 = "../logFiles/replay_output.txt";
    std::string s;

    if (argc == 1){                                                                             //There aren't arguments in command
        std::cout << "Nessun argomento fornito" << std::endl;
    }else if ((argc == 2 && argument == F_ARGUMENT) || (argc == 2 && argument == V_ARGUMENT)) {     //Not specified files
        std::cout << "Nessun file fornito" << std::endl;
    }else if(argc == 3 && argument == V_ARGUMENT){      //V ARGUMENT
        if(file1.compare(argv[2]) == 0){             //Human vs Computer match    
            getline(myFile_pc, s);        //Reading line in file and copying it in a string variable
            
            if(s.substr(0,2) == "p1"){    //Checking which player starts  
                startturn = 0;
            }else startturn = 1;

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);   
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);
            if(player1 < player2) {       //player 1 starts first
                exited = prompt.setUpBoardHumanForReplay(player1, myFile_pc);   //setting human board
                if(!exited) {
                    std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n"; //setting bot board
                    prompt.setUpBoardBotForReplay(player2, myFile_pc);
                }

            while(!exited) {
                int moves(0);
                exited = prompt.playGameForReplay(player1, BattleShip::human, player2, BattleShip::bot, startturn, moves, myFile_pc);
                moves++;
            }
            myFile_pc.close(); 
        } else {                        //player 2 starts first         
            prompt.setUpBoardBotForReplay(player2, myFile_pc);                  //setting bot boards
            exited = prompt.setUpBoardHumanForReplay(player1, myFile_pc);       //setting human board
            while(!exited) {
                int moves(0);
                exited = prompt.playGameForReplay(player2, BattleShip::bot, player1, BattleShip::human, startturn, moves, myFile_pc);
                moves++;
            }
        }
        
        }else if(file2.compare(argv[2]) == 0){       //Computer vs Computer match
            getline(myFile_cc, s);
            if(s.substr(0,2) == "p1"){
                startturn = 0;
            }else startturn = 1;

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);
            prompt.setUpBoardBotForReplay(player1, myFile_cc);
            prompt.setUpBoardBotForReplay(player2, myFile_cc);
            int moves = 0;

            while(!exited) {                     
                prompt.playGameForReplay(player1, BattleShip::bot, player2, BattleShip::bot, startturn, moves, myFile_cc);
                moves++;
            }
            myFile_cc.close();
        }
    }else if(argc == 4 && argument == F_ARGUMENT){  //F ARGUMENT
        if(file1.compare(argv[2]) == 0 && file3.compare(argv[3]) == 0){ 
            std::string line;
            getline(myFile_pc, line);
            myFile_output << line << "\n";
            if(s.substr(0,2) == "p1"){    //Checking which player starts  
                startturn = 0;
            }else startturn = 1;

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);   
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);

            if(player1 < player2) {
                myFile_output << _board.getPlayerStringBoard(player1);
            }else myFile_output << _board.getPlayerStringBoard(player2);
            
            myFile_output.close();

        }else if(file2.compare(argv[2]) == 0 && file3.compare(argv[3]) == 0){
            std::string line;
            getline(myFile_cc, line);
            myFile_output << line << "\n";
            if(s.substr(0,2) == "p1"){    //Checking which player starts  
                startturn = 0;
            }else startturn = 1;

            BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);   
            BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);

            if(player1 < player2) {
                myFile_output << _board.getPlayerStringBoard(player1);
            }else myFile_output << _board.getPlayerStringBoard(player2);

             myFile_output.close();

        }else std::cout << "Comando non valido!";
    }else{
        std::cout << "Comando non valido!" << std::endl;
    }

    return 0;
}