#ifndef SUPPORT_H_
#define SUPPORT_H_
#include <array>
#include "../Army.h"

class BattleShip::Support : public BattleShip::Army {
    protected:
        std::array<BattleShip::point_t, SUPPORTSIZE> coords_position;
    public:
        Support(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
        ~Support() {}
        //bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target) override;
        inline void armor_restore() override { Army::setArmor(SUPPORTARMOR); }
        bool is_in_army(const BattleShip::point_t& coords) override;
        inline bool isDamaged() const override { return Army::getArmor() != SUPPORTARMOR; }
        void move(const BattleShip::point_t& target) override;
};

#endif // SUPPORT_H_
