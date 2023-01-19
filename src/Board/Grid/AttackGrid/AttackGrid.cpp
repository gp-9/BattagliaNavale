#include "../../../../include/Board/Grid/AttackGrid/AttackGrid.h"
#include <iostream>

BattleShip::AttackGrid::AttackGrid() : BattleShip::Grid::Grid() {}

bool BattleShip::AttackGrid::hitPosition(const BattleShip::point_t& target, const char x) {
    if(x == HIT || x == MISS) {
        Grid::modifyGrid(target, x); 
        return true;
    }
    return false;
}

void BattleShip::AttackGrid::sonar(const BattleShip::point_t& target, const std::array<std::array<char, 5>, 5>& surrounds) {
    for(int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
            if(surrounds[x][y]) Grid::modifyGrid({target.xPos + x - 2, target.yPos + y - 2}, DISCOVERED);
        }
    }
}

void BattleShip::AttackGrid::resetActions(const char action) {
    for(std::uint32_t y = 0; y < GRIDSIZE; y++) {
        for(std::uint32_t x = 0; x < GRIDSIZE; x++) {
            if(Grid::getGridPosition({x, y}) == action) Grid::modifyGrid({x, y}, 0);
        }
    }
}
