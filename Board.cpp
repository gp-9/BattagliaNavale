#include <sstream>
#include "../../include/Board/Board.h"

BattleShip::Board* BattleShip::Board::_board = nullptr;

BattleShip::Board* BattleShip::Board::instance() {
    if(!_board) _board = new BattleShip::Board(); 
    return _board;
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

bool isInBoard(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army) {
    if(center.xPos < 1 || center.xPos > 12 || center.yPos < 1 || center.yPos > 12) return false;
    switch(army) {
        case BattleShip::ironclad:
            switch(direction) {
                case BattleShip::north:
                    if(center.yPos + 2 < 12 && center.yPos - 2 > 0) return true;
                    break;
                case BattleShip::south:
                    if(center.yPos + 2 < 12 && center.yPos - 2 > 0) return true;
                    break;
                case BattleShip::east:
                    if(center.xPos + 2 < 12 && center.xPos - 2 > 0) return true;
                    break;
                case BattleShip::west:
                    if(center.xPos + 2 < 12 && center.xPos - 2 > 0) return true;
                    break;
            }
            break;
        case BattleShip::support:
            break;
        case BattleShip::submarine:
            break;
    }
    return false;
}

bool BattleShip::Board::checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction,
                const BattleShip::army_t& army, const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& defencegrid) const {
    bool isValidPosition = false;
    return isValidPosition;
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
