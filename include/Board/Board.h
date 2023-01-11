#ifndef BOARD_H_
#define BOARD_H_
#include <array>
#include <string>
#include "../BattleShip.h"
#include "../Army/Army.h"

#define SPACESIZE 10
#define IRONCLAD 3
#define SUPPORT 3
#define SUBMARINE 2
#define HIT 'X'
#define MISS 'O'
#define DISCOVERED 'Y'
#define IRONCLADUNIT 'C'
#define SUPPORTUNIT 'S'
#define SUBMARINEUNIT 'E'

class BattleShip::Board {
    static BattleShip::Board* _board;
    std::array<std::array<char, GRIDSIZE>, GRIDSIZE> p1DefenceGrid {};
    std::array<std::array<char, GRIDSIZE>, GRIDSIZE> p1AttackGrid {};
    std::array<std::array<char, GRIDSIZE>, GRIDSIZE> p2DefenceGrid {};
    std::array<std::array<char, GRIDSIZE>, GRIDSIZE> p2AttackGrid {};
    int currP1Ironclad {};
    int currP1Support {};
    int currP1Submarine {};
    int currP2Ironclad {};
    int currP2Support {};
    int currP2Submarine {};
    std::array<BattleShip::Army*, 8> p1Army = {nullptr};
    std::array<BattleShip::Army*, 8> p2Army = {nullptr};
    Board(const BattleShip::Board&) = delete;
    BattleShip::Board& operator=(const BattleShip::Board&) = delete;
    Board() {}
    ~Board() {}

    public:
        static BattleShip::Board* instance();
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP1AttackGrid() const { return p1AttackGrid; }
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP2AttackGrid() const { return p2AttackGrid; }
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP1DefenceGrid() const { return p1DefenceGrid; }
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP2DefenceGrid() const { return p2DefenceGrid; }
        inline int getCurrP1Iroclad() const { return currP1Ironclad; }
        inline int getCurrP1Support() const { return currP1Support; }
        inline int getCurrP1Submarine() const { return currP1Submarine; }
        inline int getCurrP2Iroclad() const { return currP2Ironclad; }
        inline int getCurrP2Support() const { return currP2Support; }
        inline int getCurrP2Submarine() const { return currP2Submarine; }
        inline void setCurrP1Iroclad(int ship) { if(ship > 0 && ship <= IRONCLAD) currP1Ironclad = ship; }
        inline void setCurrP1Support(int ship) { if(ship > 0 && ship <= SUPPORT) currP1Ironclad = ship; }
        inline void setCurrP1Submarine(int ship) { if(ship > 0 && ship <= SUBMARINE) currP1Ironclad = ship; }
        inline void setCurrP2Iroclad(int ship) { if(ship > 0 && ship <= IRONCLAD) currP1Ironclad = ship; }
        inline void setCurrP2Support(int ship) { if(ship > 0 && ship <= SUPPORT) currP1Ironclad = ship; }
        inline void setCurrP2Submarine(int ship) { if(ship > 0 && ship <= SUBMARINE) currP1Ironclad = ship; }
        bool checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction,
                const BattleShip::army_t& army, const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& defencegrid) const;
        bool hitBoard(BattleShip::point_t target, 
                      const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& pDefenceGrid, 
                      std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& pAttackGrid);
        std::string getStringBoard(const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& defencegrid, 
                                   const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& attackgrid) const;
};

#endif // BOARD_H_
