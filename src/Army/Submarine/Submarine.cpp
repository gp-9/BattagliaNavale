#include "../../../include/Army/Submarine/Submarine.h"

BattleShip::Submarine::Submarine(const BattleShip::point_t& center, const BattleShip::direction_t& direction) 
    : BattleShip::Army::Army(center, direction) {
    Army::setArmor(SUBMARINEARMOR);
    Army::setType(BattleShip::submarine);
    Army::setSize(SUBMARINESIZE);
}

//bool BattleShip::Submarine::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    //return board.makeAction(origin, target, player);
//}

bool BattleShip::Submarine::is_in_army(const BattleShip::point_t& coords){
    BattleShip::point_t c = Army::getCenter(); 
    return (c.xPos == coords.xPos && c.yPos == coords.yPos);
}
