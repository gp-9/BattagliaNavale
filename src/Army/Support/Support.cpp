#include "../../../include/Army/Support/Support.h"

BattleShip::Support::Support(const BattleShip::point_t& center, const BattleShip::direction_t& direction) 
    : BattleShip::Army::Army(center, direction) {
    Army::setArmor(SUPPORTARMOR);
    Army::setSize(SUPPORTSIZE);
    Army::setType(BattleShip::support);
    if(direction == BattleShip::northsouth) {
        int count = 0;
        for(int i=-1; i < 2; i++) {
            coords_position[count] = {center.xPos+i, center.yPos};
            count++;
        }
    } else {
        int count = 0;
        for(int i=-1; i < 2; i++) {
            coords_position[count] = {center.xPos, center.yPos+i};
            count++;
        }
    }
}

//bool BattleShip::Support::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    //return board.makeAction(origin, target, player);
//}

bool BattleShip::Support::is_in_army(const BattleShip::point_t& coords){
    for (int i = 0; i < SUPPORTSIZE; i++)
    {
        if(coords.xPos == coords_position[i].xPos && coords.yPos == coords_position[i].yPos)
            return true;
    }

    return false;
}

void BattleShip::Support::move(const BattleShip::point_t& target) {
    BattleShip::direction_t dir = Army::getDirection();
    if(dir == BattleShip::northsouth) {
        int count = 0;
        for(int i=-1; i < 2; i++) {
            coords_position[count] = {target.xPos+i, target.yPos};
            count++;
        }
    } else {
        int count = 0;
        for(int i=-1; i < 2; i++) {
            coords_position[count] = {target.xPos, target.yPos+i};
            count++;
        }
    }
    Army::setCenter(target);
}
