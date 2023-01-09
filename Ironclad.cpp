#include <stdexcept>
#include "../../../include/Army/Ironclad/Ironclad.h"

BattleShip::Ironclad::Ironclad(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board) 
    : BattleShip::Army::Army(origin, direction, board) {
    if(board.checkPosition(origin, direction, BattleShip::army_t::ironclad, board.getP1DefenceGrid())) {
    } else throw std::invalid_argument("Invalide position of Ironclad");
}
