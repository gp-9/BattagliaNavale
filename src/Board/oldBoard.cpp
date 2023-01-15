#include <iostream>
#include <sstream>
#include "../../include/Board/oldBoard.h"
#include "../../include/Army/Ironclad/Ironclad.h"
#include "../../include/Army/Support/Support.h"
#include "../../include/Army/Submarine/Submarine.h"

BattleShip::Board::~Board() {
    for(int i=0; i < 8; i++) {
        delete p1Army[i];
        delete p2Army[i];
        p1Army[i] = nullptr;
        p2Army[i] = nullptr;
    }
}

void BattleShip::Board::drawIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-2; i < 3; i++) {
			p1DefenceGrid[center.xPos-1+i][center.yPos-1] = IRONCLADUNIT;
		}
	} else {
		for(int i=-2; i < 3; i++) {
			p1DefenceGrid[center.xPos-1][center.yPos-1+i] = IRONCLADUNIT;
		}
	}
}

void BattleShip::Board::drawSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-1; i < 2; i++) {
			p1DefenceGrid[center.xPos-1+i][center.yPos-1] = SUPPORTUNIT;
		}
	} else {
		for(int i=-1; i < 2; i++) {
			p1DefenceGrid[center.xPos-1][center.yPos-1+i] = SUPPORTUNIT;
		}
	}
}

void BattleShip::Board::drawSubmarine(const BattleShip::point_t& center) {
	// Il sottomarino ha dimensione 1
	p1DefenceGrid[center.xPos-1][center.yPos-1] = SUBMARINEUNIT;
}

void BattleShip::Board::emptyIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-2; i < 3; i++) {
			p1DefenceGrid[center.xPos-1+i][center.yPos-1] = EMPTY;
		}
	} else {
		for(int i=-2; i < 3; i++) {
			p1DefenceGrid[center.xPos-1][center.yPos-1+i] = EMPTY;
		}
	}
}

void BattleShip::Board::emptySupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-1; i < 2; i++) {
			p1DefenceGrid[center.xPos-1+i][center.yPos-1] = EMPTY;
		}
	} else {
		for(int i=-1; i < 2; i++) {
			p1DefenceGrid[center.xPos-1][center.yPos-1+i] = EMPTY;
		}
	}
}

void BattleShip::Board::emptySubmarine(const BattleShip::point_t& center) {
	// Il sottomarino ha dimensione 1
	p1DefenceGrid[center.xPos-1][center.yPos-1] = EMPTY;
}

void BattleShip::Board::emptyShip(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat) {
    switch(boat) {
        case BattleShip::ironclad:
			drawIronclad(center, direction);
            break;
        case BattleShip::support:
			drawSupport(center, direction);
            break;
        case BattleShip::submarine:
			drawSubmarine(center);
            break;
    }
}

void BattleShip::Board::drawShip(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat) {
    switch(boat) {
        case BattleShip::ironclad:
			drawIronclad(center, direction);
            break;
        case BattleShip::support:
			drawSupport(center, direction);
            break;
        case BattleShip::submarine:
			drawSubmarine(center);
            break;
    }
}

void BattleShip::Board::addP1Army(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat) {
    switch(boat) {
        case BattleShip::ironclad:
            if(BattleShip::Board::currP1Ironclad < 3) {
                try {
                    p1Army[currP1Ironclad] = new Ironclad(center, direction, *this);
                    currP1Ironclad++;
                    this->drawShip(center, direction, boat);
                } catch(const std::invalid_argument& e) {
                    throw;
                }
            } else throw std::invalid_argument("Too many Ironclad units");
            break;
        case BattleShip::support:
            if(BattleShip::Board::currP1Support < 3) {
                try {
                    p1Army[3 + currP1Support] = new Support(center, direction, *this);
                    currP1Support++;
                    this->drawShip(center, direction, boat);
                } catch(const std::invalid_argument& e) {
                    throw;
                }
            } else throw std::invalid_argument("Too many Support units");
            break;
        case BattleShip::submarine:
            if(BattleShip::Board::currP1Submarine < 2) {
                try {
                    p1Army[6 + currP1Submarine] = new Submarine(center, direction, *this);
                    currP1Submarine++;
                    this->drawShip(center, direction, boat);
                } catch(const std::invalid_argument& e) {
                    throw;
                }
            } else throw std::invalid_argument("Too many Submarine units");
            break;
    }
}

void BattleShip::Board::addP2Army(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat) {
    switch(boat) {
        case BattleShip::ironclad:
            if(BattleShip::Board::currP2Ironclad < 3) {
                try {
                    p2Army[currP2Ironclad] = new Ironclad(center, direction, *this);
                    currP2Ironclad++;
                } catch(const std::invalid_argument& e) {
                    throw;
                }
            } else throw std::invalid_argument("Too many Ironclad units");
            break;
        case BattleShip::support:
            if(BattleShip::Board::currP2Support < 3) {
                try {
                    p2Army[3 + currP2Support] = new Support(center, direction, *this);
                    currP2Support++;
                } catch(const std::invalid_argument& e) {
                    throw;
                }
            } else throw std::invalid_argument("Too many Support units");
            break;
        case BattleShip::submarine:
            if(BattleShip::Board::currP2Submarine < 2) {
                try {
                    p2Army[6 + currP2Submarine] = new Submarine(center, direction, *this);
                    currP2Submarine++;
                } catch(const std::invalid_argument& e) {
                    throw;
                }
            } else throw std::invalid_argument("Too many Submarine units");
            break;
    }
}

void BattleShip::Board::resetP1HitsAttackGrid() {
	for(int y=0; y < GRIDSIZE; y++) {
		for(int x=0; x < GRIDSIZE; x++) {
			if(p1AttackGrid[y][x] ==  HIT) {
				p1AttackGrid[y][x] = ' ';
			}
		}
	}
}

void BattleShip::Board::resetP1MissAttackGrid() {
	for(int y=0; y < GRIDSIZE; y++) {
		for(int x=0; x < GRIDSIZE; x++) {
			if(p1AttackGrid[y][x] ==  MISS) {
				p1AttackGrid[y][x] = ' ';
			}
		}
	}
}

void BattleShip::Board::resetP2HitsAttackGrid() {
	for(int y=0; y < GRIDSIZE; y++) {
		for(int x=0; x < GRIDSIZE; x++) {
			if(p2AttackGrid[y][x] ==  HIT) {
				p2AttackGrid[y][x] = ' ';
			}
		}
	}
}

void BattleShip::Board::resetP2MissAttackGrid() {
	for(int y=0; y < GRIDSIZE; y++) {
		for(int x=0; x < GRIDSIZE; x++) {
			if(p2AttackGrid[y][x] ==  MISS) {
				p2AttackGrid[y][x] = ' ';
			}
		}
	}
}

bool BattleShip::Board::hitBoard(BattleShip::point_t target, 
        const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& pDefenceGrid, 
        std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& pAttackGrid) {
    bool hit = false;
    if(pDefenceGrid[target.yPos][target.xPos]) {
        hit = true;
        pAttackGrid[target.yPos][target.xPos] = HIT;
    } else {
        pAttackGrid[target.yPos][target.xPos] = MISS;
    }
    return hit;
}

bool BattleShip::Board::checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction,
                const BattleShip::army_t& army, const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& defencegrid) const {
    if((center.xPos > 0 && center.xPos < 13) && (center.yPos > 0 && center.yPos < 13)) {
        switch(army) {
            case BattleShip::ironclad:
                switch(direction) {
                    case BattleShip::eastwest:
                        if((center.yPos + 2 < 13 && center.yPos - 2 > 0) && 
                                !(defencegrid[center.xPos-1][center.yPos-1] || defencegrid[center.xPos-1][center.yPos-2] || defencegrid[center.xPos-1][center.yPos] 
                                    || defencegrid[center.xPos-1][center.yPos-3] || defencegrid[center.xPos-1][center.yPos+1])) return true;
                        break;
                    case BattleShip::northsouth:
                        if((center.xPos + 2 < 13 && center.xPos - 2 > 0) && 
                                !(defencegrid[center.xPos-1][center.yPos-1] || defencegrid[center.xPos-2][center.yPos-1] || defencegrid[center.xPos][center.yPos-1] 
                                    || defencegrid[center.xPos-3][center.yPos-1] || defencegrid[center.xPos+1][center.yPos-1])) return true;
                        break;
                }
                break;
            case BattleShip::support:
                switch(direction) {
                    case BattleShip::eastwest:
                        if((center.yPos + 1 < 13 && center.yPos - 1 > 0) && 
                                !(defencegrid[center.xPos-1][center.yPos-1] || defencegrid[center.xPos-1][center.yPos-2] || defencegrid[center.xPos-1][center.yPos])) return true;
                        break;
                    case BattleShip::northsouth:
                        if((center.xPos + 1 < 13 && center.xPos - 1 > 0) && 
                                !(defencegrid[center.xPos-1][center.yPos-1] || defencegrid[center.xPos-2][center.yPos-1] || defencegrid[center.xPos][center.yPos-1])) return true;
                        break;
                }
                break;
            case BattleShip::submarine:
                if(!defencegrid[center.xPos-1][center.yPos-1]) return true;
                break;
        }
    }
    return false;
}

void addTopBorder(std::stringstream& input) {
    input << "╔";
    for(int i=0; i < GRIDSIZE-1; i++) {
        input << "═══╤";
    }
    input << "═══╗";
}

void addSpaces(std::stringstream& input) {
    for(int i=0; i < SPACESIZE; i++) {
        input << " ";
    }
}
void addLine(std::stringstream& input, int yPos, const std::array<std::array<char, 12>, 12>& grid) {
    input << "║";
    int i = 0;
    for(; i < GRIDSIZE-1; i++) {
        if(!grid[yPos][i]) input << ' ' << ' ' << " │";
        else input << ' ' << grid[yPos][i] << " │";
    }
    if(!grid[yPos][i]) input << ' ' << ' ' << " ║";
    else input << ' ' << grid[yPos][i] << " ║";
}

void addLineSeparator(std::stringstream& input) {
    input << "╟";
    for(int j=0; j < GRIDSIZE-1; j++) {
        input << "───┼";
    }
    input << "───╢";
}

void addBottomBorder(std::stringstream& input) {
    input << "╚";
    for(int i=0; i < GRIDSIZE-1; i++) {
        input << "═══╧";
    }
    input << "═══╝";
}

void addTopBorderGrid(std::stringstream& input) {
    input << "   ";
    addTopBorder(input);
    addSpaces(input);
    input << "   ";
    addTopBorder(input);
    input << '\n';
}

void addLineGrid(std::stringstream& input,const int yCoor, const int yPos, 
        const std::array<std::array<char, 12>, 12>& defencegrid, 
        const std::array<std::array<char, 12>, 12>& attackgrid) {
    input << ' ' << static_cast<char>(yCoor) << ' ';
    addLine(input, yPos, defencegrid);
    addSpaces(input);
    input << ' ' << static_cast<char>(yCoor) << ' ';
    addLine(input, yPos, attackgrid);
    input << '\n';
}

void addLineSeparatorGrid(std::stringstream& input) {
    input << "   ";
    addLineSeparator(input);
    addSpaces(input);
    input << "   ";
    addLineSeparator(input);
    input << '\n';
}

void addBottomBorderGrid(std::stringstream& input) {
    input << "   ";
    addBottomBorder(input);
    addSpaces(input);
    input << "   ";
    addBottomBorder(input);
    input << '\n';
}
void addBottomXLegend(std::stringstream& input) {
    input << "    ";
    for(int i=1; i <= GRIDSIZE; i++) {
        if(i < 10) input << " " << i << "  ";
        else input << i << "  ";
    }
    addSpaces(input);
    input << "    ";
    for(int i=1; i <= GRIDSIZE; i++) {
        if(i < 10) input << " " << i << "  ";
        else input << i << "  ";
    }
}

std::string BattleShip::Board::getStringBoard(const std::array<std::array<char, 12>, 12>& defencegrid, 
        const std::array<std::array<char, 12>, 12>& attackgrid) const {
    std::stringstream stringout; 
    addTopBorderGrid(stringout);
    char yCoor = 'A';
    int i = 0;
    for(; i < GRIDSIZE-1; i++) {
        addLineGrid(stringout, yCoor+i, i, defencegrid, attackgrid);
        addLineSeparatorGrid(stringout);
    }
    addLineGrid(stringout, yCoor+i, i, defencegrid, attackgrid);
    addBottomBorderGrid(stringout);
    addBottomXLegend(stringout);
    return stringout.str();
}
