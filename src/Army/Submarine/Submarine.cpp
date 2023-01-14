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
        if(board.getP1DefenceGrid()[target.xPos - 1][target.yPos - 1] == EMPTY){              //check if new cell is empty
            board.getP1DefenceGrid()[target.xPos - 1][target.yPos - 1] = SUBMARINEUNIT;     //move submarine in the given position
            board.getP1DefenceGrid()[origin.xPos - 1][origin.yPos - 1] = EMPTY;   //empty the prev submarine cell
            this->center.xPos = target.xPos;
            this->center.yPos = target.yPos;
            for (int i = origin.yPos - 3; i < 5; i++)
            {
                for (int j = origin.yPos - 3; j < 5; j++)
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