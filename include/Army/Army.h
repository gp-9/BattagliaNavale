#ifndef ARMY_H_
#define ARMY_H_
#include <cstddef>
#include "../BattleShip.h"
/*
#include "../Action/Action.h"

class BattleShip::Army {
    BattleShip::Action _action;
    std::size_t size;
    std::size_t armor;
    BattleShip::point_t center;
    BattleShip::direction_t direction;
    
    public:
        Army();
};
*/

class BattleShip::Army {
    std::size_t size;
    std::size_t armor;
    BattleShip::point_t center;
    BattleShip::direction_t direction;
    Army(const BattleShip::Army&) = delete;
    void operator=(const BattleShip::Army&) = delete;

    public:
        virtual bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board) = 0;

    protected:
        Army(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board) {}
};
#endif // ARMY_H_
