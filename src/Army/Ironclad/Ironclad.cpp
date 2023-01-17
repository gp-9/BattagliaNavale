#include <stdexcept>
#include "../../../include/Army/Ironclad/Ironclad.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"


//BattleShip::Ironclad::Ironclad(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player) 
BattleShip::Ironclad::Ironclad(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::nplayer_t& player) 
    : BattleShip::Army::Army(origin, direction, player) {
    //if(!board.checkPosition(origin, direction, BattleShip::army_t::ironclad, player)) {
      //  throw std::invalid_argument("Your ironclad position is out of board or already taken!");
    //}else{
        if(direction == BattleShip::northsouth) {
            int count = 0;
		for(int i=-2; i < 3; i++) {
            coords_position[count] = {center.xPos+i, center.yPos};
            count++;
		}
	    } else {
        int count = 0;
		for(int i=-2; i < 3; i++) {
            coords_position[count] = {center.xPos+i, center.yPos};
            count++;
		}
	    }
    //}
}

bool BattleShip::Ironclad::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    return board.makeAction(origin, target, player);
}

void BattleShip::Ironclad::armor_restore(){
    this->armor = IRONCLADARMOR;    
}

bool BattleShip::Ironclad::is_in_army(const BattleShip::point_t& coords){
    for (int i = 0; i < IRONCLADUNIT; i++)
    {
        if(coords.xPos == coords_position[i].xPos && coords.yPos == coords_position[i].yPos)
            return true;
    }

    return false;
}
