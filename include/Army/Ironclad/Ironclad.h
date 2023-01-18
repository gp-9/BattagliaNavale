#ifndef IRONCLAD_H_
#define IRONCLAD_H_
#include "../Army.h"
#include <array>

#define IRONCLADARMOR 5

class BattleShip::Ironclad : public BattleShip::Army {
    protected:
        std::array<BattleShip::point_t, IRONCLADSIZE> coords_position;
    public:
        Ironclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
        ~Ironclad() {}
        //bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target) override;
        inline void armor_restore() override { Army::setArmor(IRONCLADARMOR); }
        bool is_in_army(const BattleShip::point_t& coords) override;
        inline bool isDamaged() const override { return Army::getArmor() != IRONCLADARMOR; }
};

#endif // IRONCLAD_H_
