#ifndef SUPPORT_H_
#define SUPPORT_H_
#include "../Army.h"

class BattleShip::Support : public BattleShip::Army {
    public:
        Support(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board);
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target) override;
};

#endif // SUPPORT_H_
