#ifndef SUPPORT_H_
#define SUPPORT_H_
#include "../Army.h"

class BattleShip::Support : public BattleShip::Army {
    protected:
        point_t coords_position[];
    public:
        Support(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::Board& board, const BattleShip::nplayer_t& player);
        ~Support() {}
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, BattleShip::Board& board, const BattleShip::nplayer_t& player) override;
        void armor_restore() override;
        bool is_in_army(const BattleShip::point_t& coords) override;
};

#endif // SUPPORT_H_
