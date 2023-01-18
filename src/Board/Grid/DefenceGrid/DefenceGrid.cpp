#include "../../../../include/Board/Grid/DefenceGrid/DefenceGrid.h"

BattleShip::DefenceGrid::DefenceGrid() : BattleShip::Grid::Grid(), 
    _currIronclad {0}, _currSupport {0}, _currSubmarine {0} , _ironcladCenters {}, _supportCenters {}, _submarineCenters {}, _startgame {false} {}

void BattleShip::DefenceGrid::drawIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-2; i < 3; i++) {
            Grid::modifyGrid({center.xPos+i, center.yPos}, IRONCLADUNIT);
		}
	} else {
		for(int i=-2; i < 3; i++) {
            Grid::modifyGrid({center.xPos, center.yPos+i}, IRONCLADUNIT);
		}
	}
}

void BattleShip::DefenceGrid::drawSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-1; i < 2; i++) {
            Grid::modifyGrid({center.xPos+i, center.yPos}, SUPPORTUNIT);
		}
	} else {
		for(int i=-1; i < 2; i++) {
            Grid::modifyGrid({center.xPos, center.yPos+i}, SUPPORTUNIT);
		}
	}
}

void BattleShip::DefenceGrid::drawSubmarine(const BattleShip::point_t& center) {
	// Il sottomarino ha dimensione 1
    Grid::modifyGrid(center, SUBMARINEUNIT);
}

bool BattleShip::DefenceGrid::checkIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) const {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 2 < GRIDSIZE && center.yPos - 2 >= 0) && checkSupport(center, BattleShip::eastwest) &&
                    !(Grid::getGridPosition({center.xPos, center.yPos-2}) || Grid::getGridPosition({center.xPos, center.yPos+2}))) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 2 < GRIDSIZE && center.xPos - 2 >= 0) && checkSupport(center, BattleShip::northsouth) &&
                    !(Grid::getGridPosition({center.xPos-2, center.yPos}) || Grid::getGridPosition({center.xPos+2, center.yPos}))) return true;
        break;
    }
    return false;
}


bool BattleShip::DefenceGrid::checkSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) const {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 1 < GRIDSIZE && center.yPos - 1 >= 0) && checkSubmarine(center) &&
                    !(Grid::getGridPosition({center.xPos, center.yPos-1}) || Grid::getGridPosition({center.xPos, center.yPos+1}))) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 1 < GRIDSIZE && center.xPos - 1 >= 0) && checkSubmarine(center) &&
                    !(Grid::getGridPosition({center.xPos-1, center.yPos}) || Grid::getGridPosition({center.xPos+1, center.yPos}))) return true;
        break;
    }
    return false;
}


bool BattleShip::DefenceGrid::checkSubmarine(const BattleShip::point_t& center) const {
    return !Grid::getGridPosition(center);
}


void BattleShip::DefenceGrid::deleteIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	if(direction == BattleShip::northsouth) {
		for(int i=-2; i < 3; i++) {
            Grid::modifyGrid({center.xPos+i, center.yPos}, 0);
		}
	} else {
		for(int i=-2; i < 3; i++) {
            Grid::modifyGrid({center.xPos, center.yPos+i}, 0);
		}
	}
}

void BattleShip::DefenceGrid::deleteSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	if(direction == BattleShip::northsouth) {
		for(int i=-1; i < 2; i++) {
            Grid::modifyGrid({center.xPos+i, center.yPos}, 0);
		}
	} else {
		for(int i=-1; i < 2; i++) {
            Grid::modifyGrid({center.xPos, center.yPos+i}, 0);
		}
	}
}

void BattleShip::DefenceGrid::deleteSubmarine(const BattleShip::point_t& center) {
    Grid::modifyGrid(center, 0);
}

bool BattleShip::DefenceGrid::checkIroncladDestroyed(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 2 < GRIDSIZE && center.yPos - 2 >= 0) && Grid::assertCharEq(center, IRONCLADDAMAGE) && Grid::assertCharEq({center.xPos, center.yPos-1}, IRONCLADDAMAGE) && 
                Grid::assertCharEq({center.xPos, center.yPos+1}, IRONCLADDAMAGE) && Grid::assertCharEq({center.xPos, center.yPos-2}, IRONCLADDAMAGE) && 
                Grid::assertCharEq({center.xPos, center.yPos+2}, IRONCLADDAMAGE)) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 2 < GRIDSIZE && center.xPos - 2 >= 0) && Grid::assertCharEq(center, IRONCLADDAMAGE) && Grid::assertCharEq({center.xPos-1, center.yPos}, IRONCLADDAMAGE) && 
                Grid::assertCharEq({center.xPos+1, center.yPos}, IRONCLADDAMAGE) && Grid::assertCharEq({center.xPos-2, center.yPos}, IRONCLADDAMAGE) && 
                Grid::assertCharEq({center.xPos+2, center.yPos}, IRONCLADDAMAGE)) return true;
        break;
    }
    return false;
}

bool BattleShip::DefenceGrid::checkSupportDestroyed(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 1 < GRIDSIZE && center.yPos - 1 >= 0) && Grid::assertCharEq(center, SUPPORTDAMAGE) &&
                    Grid::assertCharEq({center.xPos, center.yPos-1}, SUPPORTDAMAGE) && Grid::assertCharEq({center.xPos, center.yPos+1},SUPPORTDAMAGE)) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 1 < GRIDSIZE && center.xPos - 1 >= 0) && Grid::assertCharEq(center, SUPPORTDAMAGE) &&
                    Grid::assertCharEq({center.xPos-1, center.yPos}, SUPPORTDAMAGE) && Grid::assertCharEq({center.xPos+1, center.yPos}, SUPPORTDAMAGE)) return true;
        break;
    }
    return false;
}

bool BattleShip::DefenceGrid::checkSubmarineDestroyed(const BattleShip::point_t& center) {
    return Grid::assertCharEq(center, SUBMARINEDAMAGE);
}

bool BattleShip::DefenceGrid::checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army) const {
    if((center.xPos >= 0 && center.xPos < GRIDSIZE) && (center.yPos >= 0 && center.yPos < GRIDSIZE)) {
        switch(army) {
            case BattleShip::ironclad:
                return checkIronclad(center, direction);
            break;
            case BattleShip::support:
                return checkSupport(center, direction);
            break;
            case BattleShip::submarine:
                return checkSubmarine(center);
            break;
        }
    }
    return false;
}

bool BattleShip::DefenceGrid::checkHit(const BattleShip::point_t& target) const {
    char unit = Grid::getGridPosition(target);
    if(unit == IRONCLADUNIT || unit == SUPPORTUNIT || unit == SUBMARINEUNIT) return true;
    return false;
}

bool BattleShip::DefenceGrid::hitPosition(const BattleShip::point_t& target) {
    if(checkHit(target)) {
        Grid::modifyGrid(target, char(Grid::getGridPosition(target) + 32)); // 32 e' la differenza tra i caratteri ascii maiuscoli e minuscoli
        return true;
    }
    return false;
}

void BattleShip::DefenceGrid::addIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    if(checkIronclad(center, direction) && _currIronclad < IRONCLAD) {
        _ironcladCenters[_currIronclad] = center;
        _currIronclad++;
        drawIronclad(center, direction);
        startGame();
    } else throw std::invalid_argument("Posizione o direzione non valida per una corazzata");
}

void BattleShip::DefenceGrid::addSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    if(checkSupport(center, direction) && _currSupport < SUPPORT) {
        _supportCenters[_currSupport] = center;
        _currSupport++;
        drawSupport(center, direction);
        startGame();
    } else throw std::invalid_argument("Posizione o direzione non valida per una nave di supporto");
}

void BattleShip::DefenceGrid::addSubmarine(const BattleShip::point_t& center) {
    if(checkSubmarine(center) && _currSubmarine < SUBMARINE) {
        _submarineCenters[_currSubmarine] = center;
        _currSubmarine++;
        drawSubmarine(center);
        startGame();
    } else throw std::invalid_argument("Posizione non valida per un sottomarino");
}

bool BattleShip::DefenceGrid::destroyIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    for(int i = 0; i < IRONCLAD; i++) {
        if(_ironcladCenters[i].xPos == center.xPos && _ironcladCenters[i].yPos == center.yPos) {
            if(checkIroncladDestroyed(center, direction)) {
                deleteIronclad(center, direction);
                _ironcladCenters[i] = {GRIDSIZE, GRIDSIZE};
                _currIronclad--;
                return true;
            }
        }
    }
    return false;
}

bool BattleShip::DefenceGrid::destroySupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    for(int i = 0; i < SUPPORT; i++) {
        if(_supportCenters[i].xPos == center.xPos && _supportCenters[i].yPos == center.yPos) {
            if(checkSupportDestroyed(center, direction)) {
                deleteSupport(center, direction);
                _supportCenters[i] = {GRIDSIZE, GRIDSIZE};
                _currSupport--;
                return true;
            }
        }
    }
    return false;
}

bool BattleShip::DefenceGrid::destroySubmarine(const BattleShip::point_t& center) {
    for(int i = 0; i < SUBMARINE; i++) {
        if(_submarineCenters[i].xPos == center.xPos && _submarineCenters[i].yPos == center.yPos) {
            if(checkSubmarineDestroyed(center)) {
                deleteSubmarine(center);
                _submarineCenters[i] = {GRIDSIZE, GRIDSIZE};
                _currSubmarine--;
                return true;
            }
        }
    }
    return false;
}

bool BattleShip::DefenceGrid::destroyShip(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army) {
    switch(army) {
        case BattleShip::ironclad:
            return destroyIronclad(center, direction);
        break;
        case BattleShip::support:
            return destroySupport(center, direction);
        break;
        case BattleShip::submarine:
            return destroySubmarine(center);
        break;
    }
}

void BattleShip::DefenceGrid::healShip(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army) {
    switch(army) {
        case BattleShip::ironclad:
            drawIronclad(center, direction);
        break;
        case BattleShip::support:
            drawSupport(center, direction);
        break;
        case BattleShip::submarine:
        break;
    }
}


const std::array<std::array<BattleShip::point_t, 3>, 3> BattleShip::DefenceGrid::getSupportSurrounds(const BattleShip::point_t& center) const {
    std::array<std::array<BattleShip::point_t, 3>, 3> surrounds {};
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if(center.xPos + i < 0 || center.xPos + i >= GRIDSIZE || center.yPos + j < 0 || center.yPos + j >= GRIDSIZE) {
                surrounds[i+1][j+1] = {GRIDSIZE, GRIDSIZE};
            } else {
                surrounds[i+1][j+1] = {center.xPos + i, center.yPos + j};
            }
        }
    }
    return surrounds;
}

const std::array<std::array<char, 5>, 5> BattleShip::DefenceGrid::getSonarSurrounds(const BattleShip::point_t& center) const {
    std::array<std::array<char, 5>, 5> surrounds {};
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
            if(center.xPos + i < 0 || center.xPos + i >= GRIDSIZE || center.yPos + j < 0 || center.yPos + j >= GRIDSIZE) {
                surrounds[i+2][j+2] = 0;
            } else {
                surrounds[i+2][j+2] = Grid::getGridPosition({center.xPos + i, center.yPos + j});
            }
        }
    }
    return surrounds;
}
