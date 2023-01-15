#ifndef ATTACKGRID_H_
#define ATTACKGRID_H_
#include "../Grid.h"

#define HIT 'X'
#define MISS 'O'
#define DISCOVERED 'Y'

class BattleShip::AttackGrid : public BattleShip::Grid {
    public:
        AttackGrid();
        ~AttackGrid() {}
        bool hitPosition(const BattleShip::point_t& target, const char x);
        void sonar(const BattleShip::point_t& target, const std::array<std::array<char, 5>, 5>& surrounds);
        void resetActions(const char action);
};

#endif // ATTACKGRID_H_
