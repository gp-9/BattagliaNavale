#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "../include/BattleShip.h"
#include "../include/Utils/Utils.h"
#include "../include/Army/Army.h"
#include "../include/Board/Board.h"
#include "../include/Bot/Bot.h"


static void printTitle();
std::string eval(const std::string& input, BattleShip::Board& board);
std::string setupBoard(const std::string& input, BattleShip::Board& board, const BattleShip::army_t& boat, const BattleShip::nplayer_t& player);
std::string addBotArmy(BattleShip::Board& board, const BattleShip::nplayer_t& player);

int main (int argc, char *argv[]) {
    BattleShip::match_t typeofmatch;
    BattleShip::Board gameBoard;

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
    std::stringstream output {};
    int currIronclad = 0;
    int currSupport = 0;
    int currSubmarine = 0;
    bool exited = false;
    std::ofstream myFile;
    myFile.open("../logFiles/pcLogFile.txt");
    if(typeofmatch == BattleShip::pc && myFile.is_open()) {
        const static std::string prompt = "\033[36;1m>\033[35;1m>\033[0m ";
        const static std::string errorprompt = "\033[31;1m>>\033[0m ";
        std::string line;
        output << prompt;
        

        while(currIronclad < 3 || currSupport < 3 || currSubmarine < 3) {
            BattleShip::army_t boat;
            if(currIronclad < 3) {
                boat = BattleShip::ironclad;
                output << "Quali sono le coordinate per la corazzata " << (currIronclad + 1) << '\n' << prompt;
            } else if(currSupport < 3) {
                boat = BattleShip::support;
                output << "Quali sono le coordinate per la nave di supporto " << (currSupport + 1) << '\n' << prompt;
            } else if(currSubmarine < 2) {
                boat = BattleShip::submarine;
                output << "Quali sono le coordinate per il sottomarino " << (currSubmarine + 1) << '\n' << prompt;
            }
            std::cout << output.str();
            output.str("");
            if(!std::getline(std::cin, line)) {
                
                myFile << line << std::endl;
                std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
                exited = true;
                break;
            } else {

                myFile << line << std::endl;
                try {   
                    output << setupBoard(line, gameBoard, boat, BattleShip::p1) << prompt;
                    currIronclad = gameBoard.getCurrP1Iroclad();
                    currSupport = gameBoard.getCurrP1Support();
                    currSubmarine = gameBoard.getCurrP1Submarine();
                } catch(const std::invalid_argument& e) {
                    output << e.what() << ". Perfavore reinserire il comando\n" << errorprompt;
                }
            }
        }

        if(!exited) {
            std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n";
            output.str("");
            //addBotArmy(gameBoard, BattleShip::p2);
            //BattleShip::Bot p2 {gameBoard, BattleShip::p2};
        }

        while(!exited) {
			bool done = false;
			if(startturn) {
				while(!done) {
					try {
						eval(output.str(), gameBoard);
    
						done = true;
					} catch(const std::invalid_argument& e) {
					}
				}
				output.str("");
				std::cout << prompt;
				if(!std::getline(std::cin, line)) {
                    
					std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
					exited = true;
					break;
				} else {
                    myFile << line << '\n';
					try {
						output << eval(line, gameBoard) << prompt;
        
					} catch(const std::invalid_argument& e) {
						output << e.what() << ". Perfavore reinserire il comando\n" << errorprompt;
					}
					std::cout << output.str();
					output.str("");
				}
			} else {
				if(!std::getline(std::cin, line)) {
					std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
    
					exited = true;
					break;
				} else {
                    myFile << line << '\n';
					try {
						output << eval(line, gameBoard) << prompt;
        
					} catch(const std::invalid_argument& e) {
						output << e.what() << ". Perfavore reinserire il comando\n" << errorprompt;
					}
					std::cout << output.str();
					output.str("");
				}
				while(!done) {
					try {
						eval(output.str(), gameBoard);
						done = true;
					} catch(const std::invalid_argument& e) {
					}
				}
			}
		    done = false;
        }
        
    myFile.close();
    } else {
        std::cout << "Giocando partita Computer vs Computer\n";
		//addBotArmy(gameBoard, BattleShip::p1);
		//addBotArmy(gameBoard, BattleShip::p2);
		if(startturn) {
		} else {
		}
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

std::string addBotArmy(BattleShip::Board& board, const BattleShip::nplayer_t& player) {
	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomletter(65, 76);
	std::uniform_int_distribution<std::mt19937::result_type> randomnumber(1, 12);
	int currIronclad = 0;
	int currSupport = 0;
	int currSubmarine = 0;
	std::stringstream output {};
	std::string toreturn = "";
	while(currIronclad < 3 || currSupport < 3 || currSubmarine < 3) {
		BattleShip::army_t boat;
		if(currIronclad < 3) {
			boat = BattleShip::ironclad;
		} else if(currSupport < 3) {
			boat = BattleShip::support;
		} else if(currSubmarine < 2) {
			boat = BattleShip::submarine;
		}
		bool setted = false;
		while(!setted) {
			output << static_cast<char>(randomletter(rng)) << randomnumber(rng) << " " << static_cast<char>(randomletter(rng)) << randomnumber(rng);
			try {
				setupBoard(output.str(), board, boat, player);
				currIronclad = board.getCurrP2Iroclad();
				currSupport = board.getCurrP2Support();
				currSubmarine = board.getCurrP2Submarine();
				setted = true;
			} catch(const std::invalid_argument& e) {
			}
			output.str("");
		}
	}
	if(player == BattleShip::p1) toreturn = board.getStringBoard(board.getP1DefenceGrid(), board.getP1AttackGrid());
	else toreturn = board.getStringBoard(board.getP2DefenceGrid(), board.getP2AttackGrid());
	return toreturn;
}


bool checkFirstElement(const std::string& input) {
    if((input[0] < 0x4d && input[0] > 0x40) || (input[0] > 0x60 && input[0] < 0x6d)) return true;
    return false;
}

bool checkIsCommand(const std::vector<std::string>& input, const char c) {
    if(input[0][0] == c && input[1][0] == c) return true;
    return false;
}

std::string setupBoard(const std::string& input, BattleShip::Board& board, const BattleShip::army_t& boat, const BattleShip::nplayer_t& player) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    std::string output = "";
    if(tokens.size() != 2) throw std::invalid_argument("Comando non valido");
    BattleShip::point_t head = {};
    BattleShip::point_t tail = {};
    if((checkFirstElement(tokens[0]) && checkFirstElement(tokens[1])) || ((checkIsCommand(tokens, 'X') || checkIsCommand(tokens, 'x')) && tokens[0].size() == 2 && tokens[1].size() == 2)) {
        std::string headstr = tokens[0].substr(1);
        std::string tailstr = tokens[1].substr(1);
        if((headstr == "X" || headstr == "x") && (tailstr == "X" || tailstr == "x")) {
            output = board.getStringBoard(board.getP1DefenceGrid(), board.getP1AttackGrid()) + '\n';
        } else {
            char firstX = tokens[0][0];
            char secondX = tokens[1][0];
            if(firstX < 0x4d && firstX > 0x40) {
                head.xPos = firstX - 0x40;
            }
            if(firstX < 0x6d && firstX > 0x60) {
                head.xPos = firstX - 0x60;
            }
            if(secondX < 0x4d && secondX > 0x40) {
                tail.xPos = secondX - 0x40;
            }
            if(secondX < 0x6d && secondX > 0x60) {
                tail.xPos = secondX - 0x60;
            }
            int yHead = 0;
            int yTail = 0;
				bool done = false;
            try {
                yHead = std::stoi(headstr);
                yTail = std::stoi(tailstr);
            } catch(const std::invalid_argument& e) {
                throw std::invalid_argument("Comando non valido");
            } catch(const std::out_of_range& e) {
                throw std::invalid_argument("Comando non valido");
            }
            if((yHead < 13 && yHead > 0) && (yTail < 13 && yTail > 0)) {
                head.yPos = yHead;
                tail.yPos = yTail;
                BattleShip::point_t center = {};
                BattleShip::direction_t shipdir;
                if(head.xPos == tail.xPos) {
                    shipdir = BattleShip::eastwest;
                    center.xPos = tail.xPos;
                    center.yPos = tail.yPos - boat;
                }
                else if(head.yPos == tail.yPos) {
                    shipdir = BattleShip::northsouth;
                    center.yPos = tail.yPos;
                    center.xPos = tail.xPos - boat;

                } else throw std::invalid_argument("Direzione nave non valida");
                try {
					if(player == BattleShip::p1) board.addP1Army(center, shipdir, boat);
					else board.addP2Army(center, shipdir, boat);
                } catch(const std::invalid_argument& e) {
                    throw;
                }
                std::stringstream s; 
                s << static_cast<char>(firstX) << head.yPos << " " << static_cast<char>(secondX) << tail.yPos << '\n';
                output = s.str();
            } else throw std::invalid_argument("Coordinate non valide");
        }
    } else throw std::invalid_argument("Comando non valido");
    return output;
}

std::string eval(const std::string& input, BattleShip::Board& board) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    std::string output = "";
    if(tokens.size() != 2) throw std::invalid_argument("Comando non valido");
    BattleShip::point_t origin = {};
    BattleShip::point_t target = {};
    if((checkFirstElement(tokens[0]) && checkFirstElement(tokens[1])) || 
      ((checkIsCommand(tokens, 'X') || checkIsCommand(tokens, 'A') || checkIsCommand(tokens, 'x') || checkIsCommand(tokens, 'a') || 
		checkIsCommand(tokens, 'B')|| checkIsCommand(tokens, 'b') || checkIsCommand(tokens, 'C') || checkIsCommand(tokens, 'c')) 
	   && tokens[0].size() == 2 && tokens[1].size() == 2)) {
        std::string originstr = tokens[0].substr(1);
        std::string targetstr = tokens[1].substr(1);
        if((originstr == "X" || originstr == "x") && (targetstr == "X" || targetstr == "x")) {
            output = board.getStringBoard(board.getP1DefenceGrid(), board.getP1AttackGrid()) + '\n';
        } else if((originstr == "A" || originstr == "a") && (targetstr == "A" || targetstr == "a")) {
        } else if((originstr == "B" || originstr == "b") && (targetstr == "B" || targetstr == "b")) {
			board.resetP1HitsAttackGrid();
        } else if((originstr == "C" || originstr == "c") && (targetstr == "c" || targetstr == "c")) {
			board.resetP1MissAttackGrid();
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
                throw std::invalid_argument("Comando non valido");
            } catch(const std::out_of_range& e) {
                throw std::invalid_argument("Comando non valido");
            }
            if((yOrigin < 13 && yOrigin > 0) && (yTarget < 13 && yTarget > 0)) {
                origin.yPos = yOrigin;
                target.yPos = yTarget;
                std::stringstream s; 
                s << static_cast<char>(tokens[0][0]) << origin.yPos << " " << static_cast<char>(tokens[1][0]) << target.yPos << '\n';
                output = s.str();
            } else throw std::invalid_argument("Coordinate non valide");
        }
    } else throw std::invalid_argument("Comando non valido");
    return output;
}
