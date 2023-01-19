#ifndef SUBMARINE_H_
#define SUBMARINE_H_
#include "../Army.h"

class BattleShip::Submarine : public BattleShip::Army {
    public:
        Submarine(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
        ~Submarine() {}
        //bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target) override;
        bool is_in_army(const BattleShip::point_t& coords) override;
        void armor_restore() override {}
        inline bool isDamaged() const override { return Army::getArmor() != SUBMARINEARMOR; }
        inline void move(const BattleShip::point_t& target) override { Army::setCenter(target); }
};

#endif // SUBMARINE_H_
