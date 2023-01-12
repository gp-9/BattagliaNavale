#ifndef SUBMARINE_H_
#define SUBMARINE_H_
#include "../Army.h"

class BattleShip::Submarine : public BattleShip::Army {
    public:
        Submarine(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board);
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board) override;
};

#endif // SUBMARINE_H_
