#include "../../../include/Board/Grid/Grid.h"

bool BattleShip::Grid::modifyGrid(const BattleShip::point_t& position, const char element) {
    if(verifiyPosition(position)) { 
        _grid[position.xPos][position.yPos] = element; 
        return true; 
    }
    return false; 
}
