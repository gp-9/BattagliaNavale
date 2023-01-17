#ifndef SUBMARINE_H_
#define SUBMARINE_H_
#include "../Army.h"

class BattleShip::Submarine : public BattleShip::Army {
    public:
        Submarine(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player);
        ~Submarine() {}
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player) override;
        bool is_in_army(const BattleShip::point_t& coords) override;
};

#endif // SUBMARINE_H_
