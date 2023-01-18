#include "../../include/Prompt/Prompt.h"
#include <fstream>
#include <string>
#include <unistd.h>
#include <iomanip>

const std::string BattleShip::Prompt::_prompt = "\033[36;1m>\033[35;1m>\033[0m ";
const std::string BattleShip::Prompt::_errorprompt = "\033[31;1m>>\033[0m ";

BattleShip::Prompt::Prompt() 
    : _currIronclad {0}, _currSupport {0}, _currSubmarine {0} {
    _rng.seed(_rnd());
    _randomletter = std::uniform_int_distribution<std::mt19937::result_type>(65, 76);
    _randomnumber = std::uniform_int_distribution<std::mt19937::result_type>(1, 12);
}

bool checkFirstElement(const std::string& input) {
    return (input[0] < 0x4d && input[0] > 0x40) || (input[0] > 0x60 && input[0] < 0x6d);
}

bool checkIsCommand(const std::vector<std::string>& input, const char c) {
    return input[0][0] == c && input[1][0] == c;
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


struct ret BattleShip::Prompt::evalHuman(const std::string& input, const BattleShip::nplayer_t& player) {
    std::vector<std::string> tokens = Utils::split(Utils::trim(input), " ");
    struct ret rettuple = { "", false };
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
            rettuple.output = _board.getPlayerStringBoard(player) + '\n';
            rettuple.done = false;
        } else if((originstr == "A" || originstr == "a") && (targetstr == "A" || targetstr == "a")) {
            _board.resetSonarAttackGrid(player);
            rettuple.done = false;
        } else if((originstr == "B" || originstr == "b") && (targetstr == "B" || targetstr == "b")) {
			_board.resetHitsAttackGrid(player);
            rettuple.done = false;
        } else if((originstr == "C" || originstr == "c") && (targetstr == "c" || targetstr == "c")) {
			_board.resetMissAttackGrid(player);
            rettuple.done = false;
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
                    s << static_cast<char>(tokens[0][0]) << origin.yPos + 1 << " " << static_cast<char>(tokens[1][0]) << target.yPos + 1 << '\n';
                    rettuple.output = s.str();
                    rettuple.done = true;
                } else throw std::invalid_argument("Origine non valida");
            } else throw std::invalid_argument("Coordinate non valide");
        }
    } else throw std::invalid_argument("Comando non valido");
    return rettuple;
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
    origin.yPos = std::stoi(tokens[0].substr(1)) - 1;
    target.yPos = std::stoi(tokens[1].substr(1)) - 1;
    bool done = _board.makeAction(origin, target, player);
    if(!done) throw std::invalid_argument("Coordinate non valide");
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
            
            //myFile << _line << std::endl;
            std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
            resetCount();
            output.str("");
            return true;
        } else {
            
            try {   
                output << setupBoard(_line, boat, player) << _prompt;
                _currIronclad = _board.getCurrIronclad(player);
                _currSupport = _board.getCurrSupport(player);
                _currSubmarine = _board.getCurrSubmarine(player);
                myFile << "p" << player+1 << ":" << _line << std::endl;
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
    while(!_board.isPlayerSetup(player)) {
        BattleShip::army_t boat;
        if(_currIronclad < IRONCLAD) {
            boat = BattleShip::ironclad;
        } else if(_currSupport < SUPPORT) {
            boat = BattleShip::support;
        } else if(_currSubmarine < SUBMARINE) {
            boat = BattleShip::submarine;
        }
        output << static_cast<char>(_randomletter(_rng)) << _randomnumber(_rng) << " " << static_cast<char>(_randomletter(_rng)) << _randomnumber(_rng);
        try {   
            setupBoard(output.str(), boat, player);
            _currIronclad = _board.getCurrIronclad(player);
            _currSupport = _board.getCurrSupport(player);
            _currSubmarine = _board.getCurrSubmarine(player);
            myFile << "p" << player+1 << ":" << output.str() << std::endl;
        } catch(const std::invalid_argument& e) {
        }
        output.str("");
    }
    std::cout << _board.getPlayerStringBoard(player) << std::endl;
    resetCount();
    output.str("");
    return false;
}

bool BattleShip::Prompt::setUpBoardBotForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile) {
    while(!_board.isPlayerSetup(player)) {
        BattleShip::army_t boat;
        if(_currIronclad < IRONCLAD) {
            boat = BattleShip::ironclad;
        } else if(_currSupport < SUPPORT) {
            boat = BattleShip::support;
        } else if(_currSubmarine < SUBMARINE) {
            boat = BattleShip::submarine;
        }
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
    }
    resetCount();
    return false;
}

void BattleShip::Prompt::setUpGamePC(int starter) {
    _players[starter] = BattleShip::human;
    _players[(starter+1)%NPLAYER] = BattleShip::bot;
}

void BattleShip::Prompt::setUpGameCC(int starter) {
    _players[starter] = BattleShip::bot;
    _players[(starter+1)%NPLAYER] = BattleShip::bot;
}

bool BattleShip::Prompt::makeTurnPC(int moves, std::ofstream& myFile) {
    if(!_board.isGameOver()) {
        switch(_players[moves%NPLAYER]) {
            case BattleShip::human: 
            {
                std::cout << _prompt;
                bool done = false;
                while(!done) {
                    if(!std::getline(std::cin, _line)) {
                        std::cout << "\nUscendo dal prompt di Battaglia Navale" << std::endl;
                        return true;
                    } else {
                        try {
                            struct ret rettuple = evalHuman(_line, BattleShip::nplayer_t(moves%NPLAYER));
                            myFile << "p" << (moves%NPLAYER)+1 << ":" << _line << std::endl;
                            std::cout << rettuple.output << std::endl;
                            done = rettuple.done;
                            if(!done) std::cout << _prompt;
                        } catch(const std::invalid_argument& e) {
                            std::cout << e.what() << ". Perfavore reinserire il comando\n" << _errorprompt;
                        }
                    }
                }
                break;
            }
            case BattleShip::bot: 
            {
                bool done = false;
                while(!done) {
                    output << static_cast<char>(_randomletter(_rng)) << _randomnumber(_rng) << " " << static_cast<char>(_randomletter(_rng)) << _randomnumber(_rng);
                    try {
                        evalBot(output.str(), BattleShip::nplayer_t(moves%NPLAYER));
                        std::cout << output.str();
                        myFile << "p" << (moves%NPLAYER)+1 << ":" << output.str() << std::endl;
                        done = true;
                    } catch(const std::invalid_argument& e) {
                    }
                    output.str("");
                }
                break;
            }
        }
        std::cout << std::endl << _board.getPlayerStringBoard(BattleShip::nplayer_t(moves%NPLAYER)) << std::endl;
        std::cout << std::endl << _board.getPlayerStringBoard(BattleShip::nplayer_t((moves+1)%NPLAYER)) << std::endl;
    }
    return false;
}

void BattleShip::Prompt::makeTurnCC(int moves, std::ofstream& myFile) {
    if(!_board.isGameOver()) {
        bool done = false;
        while(!done) {
            output << static_cast<char>(_randomletter(_rng)) << _randomnumber(_rng) << " " << static_cast<char>(_randomletter(_rng)) << _randomnumber(_rng);
            try {
                evalBot(output.str(), BattleShip::nplayer_t(moves%NPLAYER));
                myFile << "p" << (moves%NPLAYER)+1 << ":" << output.str() << std::endl;
                done = true;
            } catch(const std::invalid_argument& e) {
            }
            output.str("");
        }
    }
}
