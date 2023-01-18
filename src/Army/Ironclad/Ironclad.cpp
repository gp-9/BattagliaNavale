#include "../../../include/Army/Ironclad/Ironclad.h"


BattleShip::Ironclad::Ironclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) 
    : BattleShip::Army::Army(center, direction) {
    Army::setArmor(IRONCLADARMOR);
    Army::setType(BattleShip::ironclad);
    Army::setSize(IRONCLADSIZE);
    if(direction == BattleShip::northsouth) {
        int count = 0;
        for(int i=-2; i < 3; i++) {
            coords_position[count] = {center.xPos+i, center.yPos};
            count++;
        }
    } else {
        int count = 0;
        for(int i=-2; i < 3; i++) {
            coords_position[count] = {center.xPos, center.yPos+i};
            count++;
        }
    }
}

//bool BattleShip::Ironclad::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    //return board.makeAction(origin, target, player);
//}

bool BattleShip::Ironclad::is_in_army(const BattleShip::point_t& coords){
    for (int i = 0; i < IRONCLADSIZE; i++)
    {
        if(coords.xPos == coords_position[i].xPos && coords.yPos == coords_position[i].yPos)
            return true;
    }

    return false;
}
