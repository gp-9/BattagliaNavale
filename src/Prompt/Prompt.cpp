#include "../../include/Prompt/Prompt.h"
#include <fstream>
#include <unistd.h>
#include <string>

const std::string BattleShip::Prompt::_prompt = "\033[36;1m>\033[35;1m>\033[0m ";
const std::string BattleShip::Prompt::_errorprompt = "\033[31;1m>>\033[0m ";

bool checkFirstElement(const std::string& input) {
    if((input[0] < 0x4d && input[0] > 0x40) || (input[0] > 0x60 && input[0] < 0x6d)) return true;
    return false;
}

bool checkIsCommand(const std::vector<std::string>& input, const char c) {
    if(input[0][0] == c && input[1][0] == c) return true;
    return false;
}

std::string BattleShip::Prompt::setupBoard(const std::string& input, const BattleShip::army_t& boat, const BattleShip::nplayer_t& player) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    std::string output = "";
    if(tokens.size() != 2) throw std::invalid_argument("Comando non valido");
    BattleShip::point_t head = {};
    BattleShip::point_t tail = {};
    if((checkFirstElement(tokens[0]) && checkFirstElement(tokens[1])) || ((checkIsCommand(tokens, 'X') || checkIsCommand(tokens, 'x')) && tokens[0].size() == 2 && tokens[1].size() == 2)) {
        std::string headstr = tokens[0].substr(1);
        std::string tailstr = tokens[1].substr(1);
        if((headstr == "X" || headstr == "x") && (tailstr == "X" || tailstr == "x")) {
            output = _board.getPlayerStringBoard(player) + '\n';
        } else {
            char firstX = tokens[0][0];
            char secondX = tokens[1][0];
            if(firstX < 0x4d && firstX > 0x40) {
                head.xPos = firstX - 0x41;
            }
            if(firstX < 0x6d && firstX > 0x60) {
                head.xPos = firstX - 0x61;
            }
            if(secondX < 0x4d && secondX > 0x40) {
                tail.xPos = secondX - 0x41;
            }
            if(secondX < 0x6d && secondX > 0x60) {
                tail.xPos = secondX - 0x61;
            }
            int yHead = 0;
            int yTail = 0;
            try {
                yHead = std::stoi(headstr);
                yTail = std::stoi(tailstr);
            } catch(const std::invalid_argument& e) {
                throw std::invalid_argument("Comando non valido");
            } catch(const std::out_of_range& e) {
                throw std::invalid_argument("Comando non valido");
            }
            if((yHead < 13 && yHead > 0) && (yTail < 13 && yTail > 0)) {
                head.yPos = yHead - 1;
                tail.yPos = yTail - 1;
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
                    _board.addArmy(player, center, shipdir, boat);
                } catch(const std::invalid_argument& e) {
                    throw;
                }
                std::stringstream s; 
                s << static_cast<char>(firstX) << head.yPos + 1 << " " << static_cast<char>(secondX) << tail.yPos + 1 << '\n';
                output = s.str();
            } else throw std::invalid_argument("Coordinate non valide");
        }
    } else throw std::invalid_argument("Comando non valido");
    return output;
}

std::string BattleShip::Prompt::evalHuman(const std::string& input, const BattleShip::nplayer_t& player) {
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
            output = _board.getPlayerStringBoard(player) + '\n';
        } else if((originstr == "A" || originstr == "a") && (targetstr == "A" || targetstr == "a")) {
            _board.resetSonarAttackGrid(player);
        } else if((originstr == "B" || originstr == "b") && (targetstr == "B" || targetstr == "b")) {
			_board.resetHitsAttackGrid(player);
        } else if((originstr == "C" || originstr == "c") && (targetstr == "c" || targetstr == "c")) {
			_board.resetMissAttackGrid(player);
		} else {
            origin.xPos = tokens[0][0];
            target.xPos = tokens[1][0];
            if(origin.xPos < 0x4d && origin.xPos > 0x40) {
                origin.xPos -= 0x41;
            }
            if(origin.xPos < 0x6d && origin.xPos > 0x60) {
                origin.xPos -= 0x61;
            }
            if(target.xPos < 0x4d && target.xPos > 0x40) {
                target.xPos -= 0x41;
            }
            if(target.xPos < 0x6d && target.xPos > 0x60) {
                target.xPos -= 0x61;
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
                origin.yPos = yOrigin - 1;
                target.yPos = yTarget - 1;
                if(_board.makeAction(origin, target, player)) {
                    std::stringstream s; 
                    s << static_cast<char>(tokens[0][0]) << origin.yPos << " " << static_cast<char>(tokens[1][0]) << target.yPos << '\n';
                    output = s.str();
                } else throw std::invalid_argument("Origine non valida");
            } else throw std::invalid_argument("Coordinate non valide");
        }
    } else throw std::invalid_argument("Comando non valido");
    return output;
}

void BattleShip::Prompt::evalBot(const std::string& input, const BattleShip::nplayer_t& player) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    BattleShip::point_t origin = {};
    BattleShip::point_t target = {};
    origin.xPos = tokens[0][0];
    target.xPos = tokens[1][0];
    if(origin.xPos < 0x4d && origin.xPos > 0x40) {
        origin.xPos -= 0x41;
    }
    if(origin.xPos < 0x6d && origin.xPos > 0x60) {
        origin.xPos -= 0x61;
    }
    if(target.xPos < 0x4d && target.xPos > 0x40) {
        target.xPos -= 0x41;
    }
    if(target.xPos < 0x6d && target.xPos > 0x60) {
        target.xPos -= 0x61;
    }
    origin.yPos = std::stoi(tokens[0].substr(1));
    target.yPos = std::stoi(tokens[1].substr(1));
}

bool BattleShip::Prompt::setUpBoardHuman(const BattleShip::nplayer_t& player, std::ofstream& myFile) {

    output << _prompt;
    while(!_board.isPlayerSetup(player)) {
        BattleShip::army_t boat;
        if(_currIronclad < IRONCLAD) {
            boat = BattleShip::ironclad;
            output << "Quali sono le coordinate per la corazzata " << (_currIronclad + 1) << '\n' << _prompt;
        } else if(_currSupport < SUPPORT) {
            boat = BattleShip::support;
            output << "Quali sono le coordinate per la nave di supporto " << (_currSupport + 1) << '\n' << _prompt;
        } else if(_currSubmarine < SUBMARINE) {
            boat = BattleShip::submarine;
            output << "Quali sono le coordinate per il sottomarino " << (_currSubmarine + 1) << '\n' << _prompt;
        }
        std::cout << output.str();
        output.str("");
        if(!std::getline(std::cin, _line)) {
            
            myFile << _line << std::endl;
            std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
            resetCount();
            output.str("");
            return true;
        } else {

            myFile << _line << std::endl;
            try {   
                output << setupBoard(_line, boat, player) << _prompt;
                _currIronclad = _board.getCurrIronclad(player);
                _currSupport = _board.getCurrSupport(player);
                _currSubmarine = _board.getCurrSubmarine(player);
            } catch(const std::invalid_argument& e) {
                output << e.what() << ". Perfavore reinserire il comando\n" << _errorprompt;
            }
        }
    }
    resetCount();
    output.str("");
    return false;
}

bool BattleShip::Prompt::setUpBoardHumanForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile) {

    output << _prompt;
    while(!_board.isPlayerSetup(player)) {
        BattleShip::army_t boat;
        if(_currIronclad < IRONCLAD) {
            boat = BattleShip::ironclad;
            output << "Quali sono le coordinate per la corazzata " << (_currIronclad + 1) << '\n' << _prompt;
        } else if(_currSupport < SUPPORT) {
            boat = BattleShip::support;
            output << "Quali sono le coordinate per la nave di supporto " << (_currSupport + 1) << '\n' << _prompt;
        } else if(_currSubmarine < SUBMARINE) {
            boat = BattleShip::submarine;
            output << "Quali sono le coordinate per il sottomarino " << (_currSubmarine + 1) << '\n' << _prompt;
        }
        std::cout << output.str();
        output.str("");
        if(!std::getline(myFile, _line)) {
            std::cout << _line << std::endl;
            std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
            resetCount();
            output.str("");
            return true;
        } else {
            std::cout << _line << std::endl;
            try {   
                output << setupBoard(_line, boat, player) << _prompt;
                _currIronclad = _board.getCurrIronclad(player);
                _currSupport = _board.getCurrSupport(player);
                _currSubmarine = _board.getCurrSubmarine(player);
                std::cout << _board.getPlayerStringBoard(player) + '\n';
                unsigned int microsecond = 1000000;
                usleep(1 * microsecond);            //sleeps for 1 second
            } catch(const std::invalid_argument& e) {
                output << e.what() << ". Perfavore reinserire il comando\n" << _errorprompt;
            }
        }

    }
    resetCount();
    output.str("");
    return false;
}

bool BattleShip::Prompt::setUpBoardBot(const BattleShip::nplayer_t& player, std::ofstream& myFile) {
	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomletter(65, 76);
	std::uniform_int_distribution<std::mt19937::result_type> randomnumber(1, 12);
    while(!_board.isPlayerSetup(player)) {
        BattleShip::army_t boat;
        if(_currIronclad < IRONCLAD) {
            boat = BattleShip::ironclad;
        } else if(_currSupport < SUPPORT) {
            boat = BattleShip::support;
        } else if(_currSubmarine < SUBMARINE) {
            boat = BattleShip::submarine;
        }
        output << static_cast<char>(randomletter(rng)) << randomnumber(rng) << " " << static_cast<char>(randomletter(rng)) << randomnumber(rng);
        try {   
            setupBoard(output.str(), boat, player);
            _currIronclad = _board.getCurrIronclad(player);
            _currSupport = _board.getCurrSupport(player);
            _currSubmarine = _board.getCurrSubmarine(player);
            myFile << output.str() << std::endl;
        } catch(const std::invalid_argument& e) {
        }
        output.str("");
    }
    resetCount();
    output.str("");
    return false;
}

bool BattleShip::Prompt::setUpBoardBotForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile) {
	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomletter(65, 76);
	std::uniform_int_distribution<std::mt19937::result_type> randomnumber(1, 12);
    while(!_board.isPlayerSetup(player)) {
        BattleShip::army_t boat;
        if(_currIronclad < IRONCLAD) {
            boat = BattleShip::ironclad;
        } else if(_currSupport < SUPPORT) {
            boat = BattleShip::support;
        } else if(_currSubmarine < SUBMARINE) {
            boat = BattleShip::submarine;
        }
        output << static_cast<char>(randomletter(rng)) << randomnumber(rng) << " " << static_cast<char>(randomletter(rng)) << randomnumber(rng);
        try {   
            std::string line;
            getline(myFile, line);
            setupBoard(line, boat, player);
            _currIronclad = _board.getCurrIronclad(player);
            _currSupport = _board.getCurrSupport(player);
            _currSubmarine = _board.getCurrSubmarine(player);
            std::cout << _board.getPlayerStringBoard(player) + '\n';
        } catch(const std::invalid_argument& e) {
        }
        output.str("");
    }
    resetCount();
    output.str("");
    return false;
}
bool BattleShip::Prompt::playGame(const BattleShip::nplayer_t& player1, const BattleShip::player_t& player1type, const BattleShip::nplayer_t& player2, const BattleShip::player_t& player2type, int starter) {
    if(!_board.isGameStarted()) throw std::invalid_argument("I giocatori devono ancora finire di posizionare le navi");
    std::array<BattleShip::nplayer_t, NPLAYER> turns {};
    std::array<BattleShip::player_t, NPLAYER> players {};
    turns[starter] = player1;
    players[starter] = player1type;
    turns[(starter+1)%NPLAYER] = player2;
    players[(starter+1)%NPLAYER] = player2type;
    int p = 0;
    while(!_board.isGameOver()) {
        if(p == 2) p = 0;
        switch(players[p]) {
            case BattleShip::human:
            break;
            case BattleShip::bot:
            break;
        }
        p++;
    }
    /*
    if(startturn) {
        while(!_board.isGameOver()) {
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
            //myFile << line << '\n';
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
            //myFile << line << '\n';
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
    */
}
