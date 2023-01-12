#include <stdexcept>
#include "../../../include/Army/Submarine/Submarine.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Submarine::Submarine(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board) 
    : BattleShip::Army::Army(origin, direction, board) {
    if(board.checkPosition(origin, direction, BattleShip::army_t::submarine, board.getP1DefenceGrid())) {
    } else throw std::invalid_argument("Invalide position of Submarine");
}

bool BattleShip::Submarine::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board){
    
}