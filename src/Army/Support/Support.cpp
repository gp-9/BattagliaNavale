#include <stdexcept>
#include "../../../include/Army/Support/Support.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Support::Support(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board) 
    : BattleShip::Army::Army(origin, direction, board) {
    if(board.checkPosition(origin, direction, BattleShip::army_t::support, board.getP1DefenceGrid())) {
    } else throw std::invalid_argument("Invalide position of Support");
}

bool BattleShip::Support::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board){
    
}
