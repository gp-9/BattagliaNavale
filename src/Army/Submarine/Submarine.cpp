#include <stdexcept>
#include "../../../include/Army/Submarine/Submarine.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

//BattleShip::Submarine::Submarine(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player) 
BattleShip::Submarine::Submarine(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::nplayer_t& player) 
    : BattleShip::Army::Army(origin, direction, player) {
    //if(!board.checkPosition(origin, direction, BattleShip::army_t::submarine, player)) {
    //    throw std::invalid_argument("Your submarine position is out of board or already taken!");
    //} 
}

bool BattleShip::Submarine::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    return board.makeAction(origin, target, player);
}

bool BattleShip::Submarine::is_in_army(const BattleShip::point_t& coords){

    if(coords.xPos == this->center.xPos && coords.yPos == this->center.yPos)
        return true;
    else 
        return false;

}
