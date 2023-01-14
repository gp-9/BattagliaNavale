#ifndef DEFENCEGRID_H_
#define DEFENCEGRID_H_
#include <stdexcept>
#include "../Grid.h"

#define IRONCLAD 3
#define SUPPORT 3
#define SUBMARINE 2
#define IRONCLADUNIT 'C'
#define SUPPORTUNIT 'S'
#define SUBMARINEUNIT 'E'
#define IRONCLADDAMAGE 'c'
#define SUPPORTDAMAGE 's'
#define SUBMARINEDAMAGE 'e'

class BattleShip::DefenceGrid : public BattleShip::Grid {
    std::array<BattleShip::point_t, IRONCLAD> _ironcladCenters;
    std::array<BattleShip::point_t, SUPPORT> _supportCenters;
    std::array<BattleShip::point_t, SUBMARINE> _submarineCenters;
    int _currIronclad;
    int _currSupport;
    int _currSubmarine;
    bool _settingup = true;
    void drawIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
    void drawSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
    void drawSubmarine(const BattleShip::point_t& center);
    bool checkIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction) const;
    bool checkSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction) const;
    bool checkSubmarine(const BattleShip::point_t& center) const;
    void deleteIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
    void deleteSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
    void deleteSubmarine(const BattleShip::point_t& center);
    bool checkIroncladDestroyed(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
    bool checkSupportDestroyed(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
    bool checkSubmarineDestroyed(const BattleShip::point_t& center);
    bool checkHit(const BattleShip::point_t& target) const;
    inline void startGame() { if(_currIronclad == IRONCLAD && _currSupport == SUPPORT && _currSubmarine == SUBMARINE) _settingup = false; }

    public:
        DefenceGrid();
        ~DefenceGrid() {}
        inline int getIronclad() const { return _currIronclad; }
        inline int getSupport() const { return _currSupport; }
        inline int getSubmarine() const { return _currSubmarine; }
        bool checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army) const;
        bool hitPosition(const BattleShip::point_t& target);
        void addIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
        void addSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
        void addSubmarine(const BattleShip::point_t& center);
        void destroyIronclad(const BattleShip::point_t& center);
        void destroySupport(const BattleShip::point_t& center);
        void destroySubmarine(const BattleShip::point_t& center);
        inline bool matchTermianted() const { return (!_settingup && _currIronclad == 0 && _currSupport == 0 && _currSubmarine == 0); }

};

#endif // DEFENCEGRID_H_
