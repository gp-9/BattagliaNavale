#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "../include/Prompt/Prompt.h"
//#include "../include/Bot/Bot.h"


static void printTitle();
std::string eval(const std::string& input, BattleShip::Board& board);
std::string setupBoard(const std::string& input, BattleShip::Board& board, const BattleShip::army_t& boat, const BattleShip::nplayer_t& player);
std::string addBotArmy(BattleShip::Board& board, const BattleShip::nplayer_t& player);

int main (int argc, char *argv[]) {
    BattleShip::match_t typeofmatch;
    BattleShip::Prompt prompt;

    if (argc == 1) {
        printTitle();
        std::cout << "Nessun argomento fornito, sarà usato Giocatore vs Computer" << std::endl;
        typeofmatch = BattleShip::pc;
    } else if (argc == 2) {
        
        char tmpstring[2] = {0};
        std::strncpy(tmpstring, argv[1], 2);
        std::string tmptypeofmatch = tmpstring;
        printTitle();

        if (tmptypeofmatch == "pc" || tmptypeofmatch == "PC" || tmptypeofmatch == "Pc" || tmptypeofmatch == "pC") {
            std::cout << "Selezionta partita Giocatore vs Computer" << std::endl;
            typeofmatch = BattleShip::pc;
        } else if (tmptypeofmatch == "cc" || tmptypeofmatch == "CC" || tmptypeofmatch == "Cc" || tmptypeofmatch == "cC") {
            std::cout << "Selezionata partita Computer vs Computer" << std::endl;
            typeofmatch = BattleShip::cc;
        } else {
            std::cerr << "Tipo di partita non valido\nPerfavore usare 'pc' per Giocatore vs Computer o 'cc' per Computer vs Computer" << std::endl;
            return -1;
        }
    } else {
        std::cerr << "Too many arguments for the program\nPlease use: ./battaglia_navale TypeOfMatch ('pc' for Player vs Computer or 'cc' for Computer vs Computer)" << std::endl;
        return -1;
    }

	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomturn(0, 1);
	int startturn = randomturn(rng);
	std::uniform_int_distribution<std::mt19937::result_type> randomletter(65, 76);
	std::uniform_int_distribution<std::mt19937::result_type> randomnumber(1, 12);
    bool exited = false;
    std::ofstream myFile;
    myFile.open("../logFiles/pcLogFile.txt");
    if(typeofmatch == BattleShip::pc && myFile.is_open()) {
        exited = prompt.setUpBoardHuman(BattleShip::p1, myFile); 

        if(!exited) {
            std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n";
            prompt.setUpBoardBot(BattleShip::p2, myFile);
        }

        while(!exited) {
            exited = prompt.playGame(BattleShip::p1, BattleShip::human, BattleShip::p2, BattleShip::bot, startturn);
        }
        
        myFile.close();
    } else {
        std::cout << "Giocando partita Computer vs Computer\n";
    }
    
    return 0;
}

static void printTitle() {
    std::cout << "\033[2J\033[H" << R"(
  ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗      ███████╗███╗   ██╗██╗  ██╗ █████╗  ██████╗███████╗██████╗ 
  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗     ██╔════╝████╗  ██║██║  ██║██╔══██╗██╔════╝██╔════╝██╔══██╗
  ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝     █████╗  ██╔██╗ ██║███████║███████║██║     █████╗  ██║  ██║
  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝      ██╔══╝  ██║╚██╗██║██╔══██║██╔══██║██║     ██╔══╝  ██║  ██║
  ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║          ███████╗██║ ╚████║██║  ██║██║  ██║╚██████╗███████╗██████╔╝
  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝          ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚═════╝ 
                                                            
  ████████╗███╗   ███╗
  ╚══██╔══╝████╗ ████║
     ██║   ██╔████╔██║
     ██║   ██║╚██╔╝██║
     ██║   ██║ ╚═╝ ██║
     ╚═╝   ╚═╝     ╚═╝)" << '\n';

}
