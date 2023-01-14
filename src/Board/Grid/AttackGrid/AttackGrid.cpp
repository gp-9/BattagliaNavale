#include "../../../../include/Board/Grid/AttackGrid/AttackGrid.h"

BattleShip::AttackGrid::AttackGrid() : BattleShip::Grid::Grid() {}

bool BattleShip::AttackGrid::hitPosition(const BattleShip::point_t& target, const char x) {
    if(x == HIT || x == MISS) {
        Grid::modifyGrid(target, x); 
        return true;
    }
    return false;
}

void BattleShip::AttackGrid::resetActions(const char action) {
    for(std::uint32_t y = 0; y < GRIDSIZE; y++) {
        for(std::uint32_t x = 0; x < GRIDSIZE; x++) {
            if(Grid::getGridPosition({x, y}) == action) Grid::modifyGrid({x, y}, 0);
        }
    }
}
