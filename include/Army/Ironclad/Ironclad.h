#ifndef IRONCLAD_H_
#define IRONCLAD_H_
#include "../Army.h"

class BattleShip::Ironclad : public BattleShip::Army {
    public:
        Ironclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board);
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board) override;
};

#endif // IRONCLAD_H_
