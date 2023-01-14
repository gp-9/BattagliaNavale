#include <stdexcept>
#include "../../../include/Army/Support/Support.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Support::Support(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board) 
    : BattleShip::Army::Army(origin, direction, board) {
    if(!board.checkPosition(origin, direction, BattleShip::army_t::support, board.getP1DefenceGrid())){
        throw std::invalid_argument("Your support is out of board!");
    }
}

bool BattleShip::Support::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board){
    bool supported = false;
    if(board.checkPosition(target, this->direction, support, board.getP1DefenceGrid())){
        bool free_cells = false;
        if(this->direction == northsouth) {
		    for(int i=-1; i < 2; i++) {
			    if(board.getP1DefenceGrid()[center.xPos-1+i][center.yPos-1] == EMPTY){
                    free_cells = true;
                }else free_cells = false;
		    }
	    }else {
		for(int i=-1; i < 2; i++) {
			if(board.getP1DefenceGrid()[center.xPos-1][center.yPos-1+i] == EMPTY){
                free_cells = true;
            }else free_cells = false;
		}
	    }

        if(free_cells){                                                                     //check if new cells are empty
            board.drawSupport(target, this->direction);                                     //move support in the given position
            board.emptySupport(origin, this->direction);                                    //empty the prev support cells
            for (int i = this->center.yPos - 2; i < (this->center.yPos - 2) + 3; i++)
            {
                for (int j = this->center.xPos - 2; j < (this->center.xPos - 2) + 3; j++)
                {
                    if (board.getP1DefenceGrid()[i][j] != EMPTY)
                    {
                        switch (board.getP1DefenceGrid()[i][j])
                        {
                        case IRONCLADUNIT:
                            //Ripristina la corazza della corazzata
                            break;
                        
                        case SUPPORTUNIT:
                            //Ripristina la corazza della nave
                            break;
                        default:
                            break;
                        }
                        supported = true;
                    }
                    if(j + 1 > 11) break;
                }
                if(i + 1 > 11) break;
            }
            
        }else throw std::invalid_argument("There's another army in this cell!");
    }else throw std::invalid_argument("Your submarine is out of board!");

    return supported;
}