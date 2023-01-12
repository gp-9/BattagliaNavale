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
std::string eval(const std::string& input, const BattleShip::Board& board);
std::string setupBoard(const std::string& input, BattleShip::Board& board, const BattleShip::army_t& boat);

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

    const static std::string prompt = "\033[36;1m>\033[35;1m>\033[0m ";
    const static std::string errorprompt = "\033[31;1m>>\033[0m ";
    std::string line;
    std::stringstream output {};
    output << prompt;
    int currIronclad = 0;
    int currSupport = 0;
    int currSubmarine = 0;
    bool exited = false;
    while(currIronclad < 3 || currSupport < 3 || currSubmarine < 3) {
        BattleShip::army_t boat;
        if(currIronclad < 3) {
            boat = BattleShip::ironclad;
            output << "Quali sono le coordinate per la corazzata " << (currIronclad + 1) << '\n' << prompt;
        } else if(currSupport < 3) {
            boat = BattleShip::support;
            output << "Quali sono le coordinate per la nave di supporto " << (currSupport + 1) << '\n' << prompt;
        } else if(currSubmarine < 3) {
            boat = BattleShip::submarine;
            output << "Quali sono le coordinate per il sottomarino " << (currSubmarine + 1) << '\n' << prompt;
        }
        std::cout << output.str();
        output.str("");
        if(!std::getline(std::cin, line)) {
            std::cout << "\nExiting BattleShip prompt" << std::endl;
            exited = true;
            break;
        } else {
            try {
                output << setupBoard(line, *gameBoard, boat) << prompt;
                currIronclad = gameBoard->getCurrP1Iroclad();
                currSupport = gameBoard->getCurrP1Support();
                currSubmarine = gameBoard->getCurrP1Submarine();
            } catch(const std::invalid_argument& e) {
                output << e.what() << ". Please reinsert the command\n" << errorprompt;
            }
        }
    }
    output.str("");
    while(!exited) {
        if(!std::getline(std::cin, line)) {
            std::cout << "\nExiting BattleShip prompt" << std::endl;
            exited = true;
            break;
        } else {
            try {
                output << eval(line, *gameBoard) << prompt;
            } catch(const std::invalid_argument& e) {
                output << e.what() << ". Please reinsert the command\n" << errorprompt;
            }
            std::cout << output.str();
            output.str("");
        }
    }
    return 0;
}

static void printTitle() {
    std::cout << R"(
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

bool checkFirstElement(const std::string& input) {
    if((input[0] < 0x4d && input[0] > 0x40) || (input[0] > 0x60 && input[0] < 0x6d)) return true;
    return false;
}

bool checkIsCommand(const std::vector<std::string>& input, const char c) {
    if(input[0][0] == c && input[1][0] == c) return true;
    return false;
}

std::string setupBoard(const std::string& input, BattleShip::Board& board, const BattleShip::army_t& boat) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    std::string output = "";
    if(tokens.size() != 2) throw std::invalid_argument("Invalid command");
    BattleShip::point_t head = {};
    BattleShip::point_t tail = {};
    if((checkFirstElement(tokens[0]) && checkFirstElement(tokens[1])) || ((checkIsCommand(tokens, 'X') || checkIsCommand(tokens, 'x')) && tokens[0].size() == 2 && tokens[1].size() == 2)) {
        std::string headstr = tokens[0].substr(1);
        std::string tailstr = tokens[1].substr(1);
        if((headstr == "X" || headstr == "x") && (tailstr == "X" || tailstr == "x")) {
            output = board.getStringBoard(board.getP1DefenceGrid(), board.getP1AttackGrid()) + '\n';
        } else {
            if(head.xPos < 0x4d && head.xPos > 0x40) {
                head.xPos = tokens[0][0] - 0x40;
            }
            if(head.xPos < 0x6d && head.xPos > 0x60) {
                head.xPos = tokens[0][0] - 0x60;
            }
            if(tail.xPos < 0x4d && tail.xPos > 0x40) {
                tail.xPos = tokens[1][0] - 0x40;
            }
            if(tail.xPos < 0x6d && tail.xPos > 0x60) {
                tail.xPos = tokens[1][0] - 0x60;
            }
            int yHead = 0;
            int yTail = 0;
            try {
                yHead = std::stoi(headstr);
                yTail = std::stoi(tailstr);
            } catch(const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid command");
            } catch(const std::out_of_range& e) {
                throw std::invalid_argument("Invalid command");
            }
            if((yHead < 13 && yHead > 0) && (yTail < 13 && yTail > 0)) {
                head.yPos = yHead;
                tail.yPos = yTail;
                BattleShip::point_t center = {};
                BattleShip::direction_t shipdir;
                if(head.xPos == tail.xPos) {
                    shipdir = BattleShip::eastwest;
                    center.xPos = tail.xPos;
                    center.yPos = tail.yPos + boat;
                }
                else if(head.yPos == tail.yPos) {
                    shipdir = BattleShip::northsouth;
                    center.yPos = tail.yPos;
                    center.xPos = tail.xPos + boat;

                } else throw std::invalid_argument("Invalid ship direction");
                try {
                    board.addP1Army(center, shipdir, boat);
                } catch(const std::invalid_argument& e) {
                    throw;
                }
                std::stringstream s; 
                s << static_cast<char>(tokens[0][0]) << head.yPos << " " << static_cast<char>(tokens[1][0]) << tail.yPos << '\n';
                output = s.str();
            } else throw std::invalid_argument("Invalid coordinates");
        }
    } else throw std::invalid_argument("Invalid command");
    return output;
}

std::string eval(const std::string& input, const BattleShip::Board& board) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    std::string output = "";
    if(tokens.size() != 2) throw std::invalid_argument("Invalid command");
    BattleShip::point_t origin = {};
    BattleShip::point_t target = {};
    if((checkFirstElement(tokens[0]) && checkFirstElement(tokens[1])) || 
      ((checkIsCommand(tokens, 'X') || checkIsCommand(tokens, 'A') || checkIsCommand(tokens, 'x') || checkIsCommand(tokens, 'a')) && tokens[0].size() == 2 && tokens[1].size() == 2)) {
        std::string originstr = tokens[0].substr(1);
        std::string targetstr = tokens[1].substr(1);
        if((originstr == "X" || originstr == "x") && (targetstr == "X" || targetstr == "x")) {
            output = board.getStringBoard(board.getP1DefenceGrid(), board.getP1AttackGrid()) + '\n';
        } else if((originstr == "A" || originstr == "a") && (targetstr == "A" || targetstr == "a")) {
        } else {
            origin.xPos = tokens[0][0];
            target.xPos = tokens[1][0];
            if(origin.xPos < 0x4d && origin.xPos > 0x40) {
                origin.xPos -= 0x40;
            }
            if(origin.xPos < 0x6d && origin.xPos > 0x60) {
                origin.xPos -= 0x60;
            }
            if(target.xPos < 0x4d && target.xPos > 0x40) {
                target.xPos -= 0x40;
            }
            if(target.xPos < 0x6d && target.xPos > 0x60) {
                target.xPos -= 0x60;
            }
            int yOrigin = 0;
            int yTarget = 0;
            try {
                yOrigin = std::stoi(originstr);
                yTarget = std::stoi(targetstr);
            } catch(const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid command");
            } catch(const std::out_of_range& e) {
                throw std::invalid_argument("Invalid command");
            }
            if((yOrigin < 13 && yOrigin > 0) && (yTarget < 13 && yTarget > 0)) {
                origin.yPos = yOrigin;
                target.yPos = yTarget;
                std::stringstream s; 
                s << static_cast<char>(tokens[0][0]) << origin.yPos << " " << static_cast<char>(tokens[1][0]) << target.yPos << '\n';
                output = s.str();
            } else throw std::invalid_argument("Invalid coordinates");
        }
    } else throw std::invalid_argument("Invalid command");
    return output;
}
