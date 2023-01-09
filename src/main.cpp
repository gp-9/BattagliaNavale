#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/BattleShip.h"
#include "../include/Utils/Utils.h"
#include "../include/Army/Army.h"
#include "../include/Board/Board.h"


static void printTitle();
std::vector<std::string> read(const std::string& input);
std::string eval(const std::vector<std::string>& input, const BattleShip::Board& board);
std::string print(const std::string& input);

int main (int argc, char *argv[]) {
    BattleShip::match_t typeofmatch;
    BattleShip::Board *gameBoard = BattleShip::Board::instance();

    if (argc == 1) {
        printTitle();
        std::cout << "No argument provided to determine the type of match, Player vs Computer will be used" << std::endl;
        typeofmatch = BattleShip::pc;
    } else if (argc == 2) {
        char tmpstring[2] = {0};
        std::strncpy(tmpstring, argv[1], 2);
        std::string tmptypeofmatch = tmpstring;
        printTitle();

        if (tmptypeofmatch == "pc" || tmptypeofmatch == "PC" || tmptypeofmatch == "Pc" || tmptypeofmatch == "pC") {
            std::cout << "Selected match type Player vs Computer" << std::endl;
            typeofmatch = BattleShip::pc;
        } else if (tmptypeofmatch == "cc" || tmptypeofmatch == "CC" || tmptypeofmatch == "Cc" || tmptypeofmatch == "cC") {
            std::cout << "Selected match type Computer vs Computer" << std::endl;
            typeofmatch = BattleShip::cc;
        } else {
            std::cerr << "Invalid type of match\nPlease use 'pc' for Player vs Computer or 'cc' for Computer vs Computer" << std::endl;
            return -1;
        }
    } else {
        std::cerr << "Too many arguments for the program\nPlease use: ./battaglia_navale TypeOfMatch ('pc' for Player vs Computer or 'cc' for Computer vs Computer)" << std::endl;
        return -1;
    }

    const static std::string prompt = ">> ";
    std::string line;
    std::cout << prompt;
    int currIronclad = 0;
    int currSupport = 0;
    int currSubmarine = 0;
    do {
        if(!std::getline(std::cin, line)) {
            std::cout << "\nExiting BattleShip REPL" << std::endl;
            break;
        } else {
            std::string toprint;
            try {
                toprint = print(eval(read(line), *gameBoard));
            } catch(const std::invalid_argument& e) {
                toprint = e.what();
                toprint += ". Please reinsert the command\n";
            }
            std::cout << toprint << prompt;
        }
    } while(true);

    return 0;
}

static void printTitle() {
    std::cout << R"(
  ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗ 
  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗
  ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝
  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝ 
  ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║     
  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝     
                                                                               
  ███████╗███╗   ██╗██╗  ██╗ █████╗  ██████╗███████╗██████╗ 
  ██╔════╝████╗  ██║██║  ██║██╔══██╗██╔════╝██╔════╝██╔══██╗
  █████╗  ██╔██╗ ██║███████║███████║██║     █████╗  ██║  ██║
  ██╔══╝  ██║╚██╗██║██╔══██║██╔══██║██║     ██╔══╝  ██║  ██║
  ███████╗██║ ╚████║██║  ██║██║  ██║╚██████╗███████╗██████╔╝
  ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚═════╝ 
                                                            
  ████████╗███╗   ███╗
  ╚══██╔══╝████╗ ████║
     ██║   ██╔████╔██║
     ██║   ██║╚██╔╝██║
     ██║   ██║ ╚═╝ ██║
     ╚═╝   ╚═╝     ╚═╝)" << '\n';

}


std::vector<std::string> read(const std::string& input) {
    std::vector<std::string> tokens = Utils::split(input, " ");
    return tokens;
}

std::string eval(const std::vector<std::string>& input, const BattleShip::Board& board) {
    std::string toreturn = "";
    if(input.size() > 2) throw std::invalid_argument("Command too long");
    BattleShip::point_t origin = {};
    BattleShip::point_t target = {};
    if(((input[0][0] < 0x4d && input[0][0] > 0x40) || (input[0][0] > 0x60 && input[0][0] < 0x6d)) || 
       ((input[1][0] < 0x4d && input[1][0] > 0x40) || (input[1][0] > 0x60 && input[1][0] < 0x6d)) || 
       (input[0][0] == 'X' && input[1][0] == 'X') || (input[0][0] == 'A' && input[1][0] == 'A')) {
        std::string originstr = input[0].substr(1);
        std::string targetstr = input[1].substr(1);
        if(originstr == "X" && targetstr == "X") {
            toreturn = board.getStringBoard(board.getP1DefenceGrid(), board.getP1AttackGrid()) + '\n';
        } else if(originstr == "A" && targetstr == "A") { 
        } else {
            origin.xPos = input[0][0];
            target.xPos = input[1][0];
            int yOrigin = std::stoi(input[0].substr(1));
            int yTarget = std::stoi(input[1].substr(1));
            if((yOrigin < 13 && yOrigin > 0) && (yTarget < 13 && yTarget > 0)) {
                origin.yPos = yOrigin;
                target.yPos = yTarget;
                std::stringstream s; 
                s << static_cast<char>(origin.xPos) << origin.yPos << " " << static_cast<char>(target.xPos) << target.yPos << '\n';
                toreturn = s.str();
            } else throw std::invalid_argument("Invalid coordinates");
        }
    } else throw std::invalid_argument("Invalid command");
    return toreturn;
}

std::string print(const std::string& input) {
    return input;
}
