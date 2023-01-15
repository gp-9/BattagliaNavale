#include <stdexcept>
#include "../../../include/Army/Ironclad/Ironclad.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Ironclad::Ironclad(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player) 
    : BattleShip::Army::Army(origin, direction, board, player) {
    if(!board.checkPosition(origin, direction, BattleShip::army_t::ironclad, player)) {
        throw std::invalid_argument("Your ironclad position is out of board or already taken!");
    } 
}

bool BattleShip::Ironclad::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    board.makeAction(origin, target, player);
}