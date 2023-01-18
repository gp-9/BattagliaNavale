#ifndef ARMY_H_
#define ARMY_H_
#include <cstddef>
#include "../BattleShip.h"

class BattleShip::Army {
    Army(const BattleShip::Army&) = delete;
    void operator=(const BattleShip::Army&) = delete;
    std::size_t size;
    std::size_t armor;
    BattleShip::point_t center;
    BattleShip::direction_t direction;    
    BattleShip::army_t type;

    public:
        //virtual bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target) = 0; 
        virtual ~Army() {}
        virtual void armor_restore() = 0;
        inline void hitUnit() { if(armor > 0) armor--; }
        inline std::size_t getArmor() const { return this->armor; }
        virtual bool is_in_army(const BattleShip::point_t& coords) = 0;
        inline BattleShip::point_t getCenter() const { return center; }
        inline BattleShip::army_t getType() const { return type; }
        inline BattleShip::direction_t getDirection() const { return direction; }

    protected:
        Army(const BattleShip::point_t& center, const BattleShip::direction_t& direction) : center {center}, direction {direction} {}
        void setArmor(const std::size_t& armor) { if(armor <= IRONCLADSIZE) this->armor = armor; }
        void setType(const BattleShip::army_t& type)  { this->type = type; }
        void setSize(const std::size_t& size) { if(size <= IRONCLADSIZE) this->size = size; }
};
#endif // ARMY_H_
