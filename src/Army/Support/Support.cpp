#include <stdexcept>
#include "../../../include/Army/Support/Support.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Support::Support(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player) 
    : BattleShip::Army::Army(origin, direction, board, player) {
    if(!board.checkPosition(origin, direction, BattleShip::army_t::support, player)) {
        throw std::invalid_argument("Your support position is out of board or already taken!");
    }else{
        if(direction == BattleShip::northsouth) {
        int count = 0;
        for(int i=-1; i < 2; i++) {
            coords_position[count] = {center.xPos+i, center.yPos};
		}
	    } else {
        int count = 0;
		for(int i=-1; i < 2; i++) {
            coords_position[count] = {center.xPos+i, center.yPos};
		}
	    }
    }
}

bool BattleShip::Support::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player){
    board.makeAction(origin, target, player);
}

void BattleShip::Ironclad::armor_restore(){
    this->armor = SUPPORTARMOR;    
}

bool BattleShip::Ironclad::is_in_army(const BattleShip::point_t& coords){
    for (int i = 0; i < SUPPORTUNIT; i++)
    {
        if(coords.xPos == coords_position[i].xPos && coords.yPos == coords_position[i].yPos)
            return true;
    }

    return false;
}