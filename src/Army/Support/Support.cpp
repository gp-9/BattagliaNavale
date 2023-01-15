#include <stdexcept>
#include "../../../include/Army/Support/Support.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Support::Support(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player) 
    : BattleShip::Army::Army(origin, direction, board, player) {
    if(!board.checkPosition(origin, direction, BattleShip::army_t::support, player)) {
        throw std::invalid_argument("Your support position is out of board or already taken!");
    } 
}

bool BattleShip::Support::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    board.makeAction(origin, target, player);
}