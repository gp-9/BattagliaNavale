#include <stdexcept>
#include "../../../include/Army/Ironclad/Ironclad.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Ironclad::Ironclad(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board) 
    : BattleShip::Army::Army(origin, direction, board) {
    if(!board.checkPosition(origin, direction, BattleShip::army_t::ironclad, board.getP1DefenceGrid())) {
        throw std::invalid_argument("Your ironclad is out of board!");
    } 
}

bool BattleShip::Ironclad::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board){
    board.hitBoard(target, board.getP2DefenceGrid(), board.getP1AttackGrid());
}