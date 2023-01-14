#include <stdexcept>
#include "../../../include/Army/Submarine/Submarine.h"
#include "../../../include/BattleShip.h"
#include "../../../include/Board/Board.h"

BattleShip::Submarine::Submarine(const BattleShip::point_t& origin, const BattleShip::direction_t& direction, const BattleShip::Board& board) 
    : BattleShip::Army::Army(origin, direction, board) {
    if(!board.checkPosition(origin, direction, BattleShip::army_t::submarine, board.getP1DefenceGrid())) {
        throw std::invalid_argument("Your submarine is out of board!");
    } 
}

bool BattleShip::Submarine::makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board){
    bool sonar = false;
    if(board.checkPosition(target, this->direction, submarine, board.getP1DefenceGrid())){
        if(board.getP1DefenceGrid()[target.xPos - 1][target.yPos - 1] == EMPTY){                //check if new cell is empty
            board.emptySubmarine(origin);                                                       //empty the prev submarine cell
            board.drawSubmarine(target);                                                        //move the support in target pos
            for (int i = origin.yPos - 3; i < (origin.yPos - 3) + 5; i++)
            {
                for (int j = origin.xPos - 3; j < (origin.xPos - 3) + 5; j++)
                {
                    
                    if (board.getP2DefenceGrid()[i][j] != EMPTY)
                    {
                        board.getP1AttackGrid()[i][j] = DISCOVERED;
                        sonar = true;
                    }
                    if(j + 1 > 11) break;
                }
                if(i + 1 > 11) break;
            }
            
        }else throw std::invalid_argument("There's another army in this cell!");
    }else throw std::invalid_argument("Your submarine is out of board!");

    return sonar;
}