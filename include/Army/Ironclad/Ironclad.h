#ifndef IRONCLAD_H_
#define IRONCLAD_H_
#include "../Army.h"

class BattleShip::Ironclad : public BattleShip::Army {
    protected:
        point_t coords_position[];
    public:
        Ironclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player);
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player) override;
};

#endif // IRONCLAD_H_
