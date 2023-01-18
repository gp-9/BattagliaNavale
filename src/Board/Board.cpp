#include "../../include/Board/Board.h"
#include <iostream>

BattleShip::Board::Board() {
    for(int i = 0; i < NPLAYER; i++) {
        _defenceGrids[i].reset(new BattleShip::DefenceGrid());
        _attackGrids[i].reset(new BattleShip::AttackGrid());
    }
}

void BattleShip::Board::resetHitsAttackGrid(const BattleShip::nplayer_t& player) {
    _attackGrids[player]->resetActions(HIT);
}

void BattleShip::Board::resetMissAttackGrid(const BattleShip::nplayer_t& player) {
    _attackGrids[player]->resetActions(MISS);
}

void BattleShip::Board::resetSonarAttackGrid(const BattleShip::nplayer_t& player) {
    _attackGrids[player]->resetActions(DISCOVERED);
}

void BattleShip::Board::addArmy(const BattleShip::nplayer_t& player, const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat) {
    // Si usa il numero di navi massime come una sorta di frame pointer alla parte di array dedicata al tipo di nave voluta e all'interno 
    // di questa parte vi si accede tramite il numero di navi che si hanno
    // *this da rimuover in seguito, visto che bisogna rifare le classi delle navi
    switch(boat) {
        case BattleShip::ironclad: {
            try {
                _armies[_defenceGrids[player]->getIronclad()][player].reset(new BattleShip::Ironclad(center, direction));
                _defenceGrids[player]->addIronclad(center, direction);
            } catch(const std::invalid_argument& e) {
                throw;
            }
            break;
        }
        case BattleShip::support: {
            try {
                _armies[IRONCLAD+_defenceGrids[player]->getSupport()][player].reset(new BattleShip::Support(center, direction));
                _defenceGrids[player]->addSupport(center, direction);
            } catch(const std::invalid_argument& e) {
                throw;
            }
            break;
        }
        case BattleShip::submarine: {
            try {
                _armies[IRONCLAD+SUPPORT+_defenceGrids[player]->getSubmarine()][player].reset(new BattleShip::Submarine(center, direction));
                _defenceGrids[player]->addSubmarine(center);
            } catch(const std::invalid_argument& e) {
                throw;
            }
            break;
        }
    }
}

bool BattleShip::Board::checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army, const BattleShip::nplayer_t& player) const {
    return _defenceGrids[player]->checkPosition(center, direction, army);
}

bool BattleShip::Board::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, const BattleShip::nplayer_t& player) {
    for(int i = 0; i < TOTALARMYCOUNT; i++) {
        // Esempio di come si possa implementare l'azione coordinata da board
        /*
        BattleShip::point_t center = _armies[i][player]->getCenter();
        if(center.xPos == origin.xPos && center.yPos == origin.yPos) { 
            BattleShip::army_t boatt = _armies[i][player]->getType();
            switch(boatt) {
                case BattleShip::ironclad:
                    if(_defenceGrids[(player+1)%NPLAYER]->hitPosition(target)) {
                        _attackGrids[player]->hitPosition(target, HIT);
                        for(int j = 0; j < TOTALARMYCOUNT; j++) {
                            std::unique_ptr<BattleShip::Army> boat = _armies[j][(player+1)%NPLAYER]
                            if(boat->hasPoint(target)) {
                                _defenceGrids[(player+1)%NPLAYER]->destroyShip(baot->getCenter(), boat->getDirection(), boat->getType());
                                boat->destroy();
                                break;
                            }
                        }
                    } else _attackGrids[player]->hitPosition(target, MISS);
                    _armies[i][player]->makeAction(target);
                    return true;
                break;
                case BattleShip::support:
                    if(_defenceGrids[player]->checkPosition(target, _armies[i][player]->getDirection(), BattleShip::support)) {
                        _armies[i][player]->makeAction(target); 
                        std::array<std::array<BattleShip::point_t, 3>, 3> surr = _defenceGrids[player]->getSupportSurrounds(target);
                        for(std::array<BattleShip::point_t, 3>& x : surr) {
                            for(BattleShip::point_t y : x) {
                                for(int j = 0; j < TOTALARMYCOUNT; j++) {
                                    if(_armies[j][player]->getType() != BattleShip::support && _armies[j][player]->isDamaged() && _armies[j][player]->hasPoint(y)) {
                                        _defenceGrids[player]->healShip(_armies[j][player]->getCenter(), _armies[j][player]->getDirection(), _armies[j][player]->getType());
                                        _armies[j][player]->heal();
                                    }
                                }
                            }
                        }
                        return true;
                    }
                break;
                case BattleShip::submarine:
                    if(_defenceGrids[player]->checkPosition(target, _armies[i][player]->getDirection(), BattleShip::submarine)) {
                        _armies[i][player]->makeAction(target); 
                        _attackGrids[player]->sonar(target, _defenceGrids[(player+1)%NPLAYER]->getSonarSurrounds(target));
                        return true;
                    }
                break;
            } 
        }
        */
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

std::string BattleShip::Board::getPlayerStringBoard(const BattleShip::nplayer_t& player) const {
    std::stringstream stringout; 
    addTopBorderGrid(stringout);
    char yCoor = 'A';
    int i = 0;
    for(; i < GRIDSIZE-1; i++) {
        addLineGrid(stringout, yCoor+i, i, _defenceGrids[player]->getGrid(), _attackGrids[player]->getGrid());
        addLineSeparatorGrid(stringout);
    }
    addLineGrid(stringout, yCoor+i, i, _defenceGrids[player]->getGrid(), _attackGrids[player]->getGrid());
    addBottomBorderGrid(stringout);
    addBottomXLegend(stringout);
    return stringout.str();
}
