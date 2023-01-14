#include "../../../../include/Board/Grid/DefenceGrid/DefenceGrid.h"

BattleShip::DefenceGrid::DefenceGrid() : BattleShip::Grid::Grid(), 
    _currIronclad {0}, _currSupport {0}, _currSubmarine {0} , _ironcladCenters {}, _supportCenters {}, _submarineCenters {} {}

void BattleShip::DefenceGrid::drawIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-2; i < 3; i++) {
            Grid::_grid[center.xPos+i][center.yPos] = IRONCLADUNIT;
		}
	} else {
		for(int i=-2; i < 3; i++) {
            Grid::_grid[center.xPos][center.yPos+i] = IRONCLADUNIT;
		}
	}
}

void BattleShip::DefenceGrid::drawSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	// tutte e due le coordinate vanno decremenetate dato che partono da 1 e l'array invece parte da 0
	if(direction == BattleShip::northsouth) {
		for(int i=-1; i < 2; i++) {
            Grid::_grid[center.xPos+i][center.yPos] = SUPPORTUNIT;
		}
	} else {
		for(int i=-1; i < 2; i++) {
            Grid::_grid[center.xPos][center.yPos+i] = SUPPORTUNIT;
		}
	}
}

void BattleShip::DefenceGrid::drawSubmarine(const BattleShip::point_t& center) {
	// Il sottomarino ha dimensione 1
    Grid::_grid[center.xPos][center.yPos] = SUBMARINEUNIT;
}

bool BattleShip::DefenceGrid::checkIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) const {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 2 < GRIDSIZE && center.yPos - 2 >= 0) && checkSupport(center, BattleShip::eastwest) &&
                    !(Grid::_grid[center.xPos][center.yPos-2] || Grid::_grid[center.xPos][center.yPos+2])) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 2 < GRIDSIZE && center.xPos - 2 >= 0) && checkSupport(center, BattleShip::northsouth) &&
                    !(Grid::_grid[center.xPos-2][center.yPos] || Grid::_grid[center.xPos+2][center.yPos])) return true;
        break;
    }
    return false;
}


bool BattleShip::DefenceGrid::checkSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) const {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 1 < GRIDSIZE && center.yPos - 1 >= 0) && checkSubmarine(center) &&
                    !(Grid::_grid[center.xPos][center.yPos-1] || Grid::_grid[center.xPos][center.yPos+1])) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 1 < GRIDSIZE && center.xPos - 1 >= 0) && checkSubmarine(center) &&
                    !(Grid::_grid[center.xPos-1][center.yPos] || Grid::_grid[center.xPos+1][center.yPos])) return true;
        break;
    }
    return false;
}


bool BattleShip::DefenceGrid::checkSubmarine(const BattleShip::point_t& center) const {
    if(!Grid::_grid[center.xPos][center.yPos]) return true;
    return false;
}


void BattleShip::DefenceGrid::deleteIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	if(direction == BattleShip::northsouth) {
		for(int i=-2; i < 3; i++) {
            Grid::_grid[center.xPos+i][center.yPos] = 0;
		}
	} else {
		for(int i=-2; i < 3; i++) {
            Grid::_grid[center.xPos][center.yPos+i] = 0;
		}
	}
}

void BattleShip::DefenceGrid::deleteSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
	if(direction == BattleShip::northsouth) {
		for(int i=-1; i < 2; i++) {
            Grid::_grid[center.xPos+i][center.yPos] = 0;
		}
	} else {
		for(int i=-1; i < 2; i++) {
            Grid::_grid[center.xPos][center.yPos+i] = 0;
		}
	}
}

void BattleShip::DefenceGrid::deleteSubmarine(const BattleShip::point_t& center) {
    Grid::_grid[center.xPos][center.yPos] = 0;
}

bool BattleShip::DefenceGrid::checkIroncladDestroyed(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 2 < GRIDSIZE && center.yPos - 2 >= 0) && checkSupportDestroyed(center, BattleShip::eastwest) &&
                    (Grid::_grid[center.xPos][center.yPos-2] && Grid::_grid[center.xPos][center.yPos+2])) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 2 < GRIDSIZE && center.xPos - 2 >= 0) && checkSupportDestroyed(center, BattleShip::northsouth) &&
                    (Grid::_grid[center.xPos-2][center.yPos] && Grid::_grid[center.xPos+2][center.yPos])) return true;
        break;
    }
    return false;
}

bool BattleShip::DefenceGrid::checkSupportDestroyed(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    switch(direction) {
        case BattleShip::eastwest:
            if((center.yPos + 1 < GRIDSIZE && center.yPos - 1 >= 0) && checkSubmarineDestroyed(center) &&
                    (Grid::_grid[center.xPos][center.yPos-1] && Grid::_grid[center.xPos][center.yPos+1])) return true;
        break;
        case BattleShip::northsouth:
            if((center.xPos + 1 < GRIDSIZE && center.xPos - 1 >= 0) && checkSubmarineDestroyed(center) &&
                    (Grid::_grid[center.xPos-1][center.yPos] && Grid::_grid[center.xPos+1][center.yPos])) return true;
        break;
    }
    return false;
}

bool BattleShip::DefenceGrid::checkSubmarineDestroyed(const BattleShip::point_t& center) {
    if(Grid::_grid[center.xPos][center.yPos]) return true;
    return false;
}

bool BattleShip::DefenceGrid::checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army) const {
    if((center.xPos >= 0 && center.xPos < GRIDSIZE) && (center.yPos >= 0 && center.yPos < GRIDSIZE)) {
        switch(army) {
            case BattleShip::ironclad:
                checkIronclad(center, direction);
            break;
            case BattleShip::support:
                checkSupport(center, direction);
            break;
            case BattleShip::submarine:
                checkSubmarine(center);
            break;
        }
    }
    return false;
}

bool BattleShip::DefenceGrid::checkHit(const BattleShip::point_t& target) const {
    char unit = Grid::_grid[target.xPos][target.yPos];
    if(unit == IRONCLADUNIT || unit == SUPPORTUNIT || unit == SUBMARINEUNIT) return true;
    return false;
}

bool BattleShip::DefenceGrid::hitPosition(const BattleShip::point_t& target) {
    if(checkHit(target)) {
        Grid::_grid[target.xPos][target.yPos] = char(Grid::_grid[target.xPos][target.yPos] + 32); // 32 e' la differenza tra i caratteri ascii maiuscoli e minuscoli
        return true;
    }
    return false;
}

void BattleShip::DefenceGrid::addIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    if(checkIronclad(center, direction) && _currIronclad < IRONCLAD) {
        _currIronclad++;
        drawIronclad(center, direction);
    } else throw std::invalid_argument("Posizione o direzione non valida per una corazzata");
}

void BattleShip::DefenceGrid::addSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) {
    if(checkSupport(center, direction) && _currSupport < SUPPORT) {
        _currSupport++;
        drawSupport(center, direction);
    } else throw std::invalid_argument("Posizione o direzione non valida per una nave di supporto");
}

void BattleShip::DefenceGrid::addSubmarine(const BattleShip::point_t& center) {
    if(checkSubmarine(center) && _currSubmarine < SUBMARINE) {
        _currSubmarine++;
        drawSubmarine(center);
    } else throw std::invalid_argument("Posizione non valida per un sottomarino");
}
