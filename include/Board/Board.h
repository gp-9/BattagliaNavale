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
	Board(const BattleShip::Board&&) = delete;
	BattleShip::Board& operator=(const BattleShip::Board&&) = delete;
    Board() {}
    ~Board() {}
	void drawIronclad(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
	void drawSupport(const BattleShip::point_t& center, const BattleShip::direction_t& direction);
	void drawSubmarine(const BattleShip::point_t& center);
    void drawShip(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat);
    void updateP1AttackGrid(const BattleShip::point_t& origin, const BattleShip::point_t& target, const BattleShip::army_t& boat);
    void updateP2AttackGrid(const BattleShip::point_t& origin, const BattleShip::point_t& target, const BattleShip::army_t& boat);

    public:
        static BattleShip::Board* instance();
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP1AttackGrid() const { return p1AttackGrid; }
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP2AttackGrid() const { return p2AttackGrid; }
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP1DefenceGrid() const { return p1DefenceGrid; }
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP2DefenceGrid() const { return p2DefenceGrid; }
        inline std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP1AttackGrid() { return p1AttackGrid; }
        inline std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP2AttackGrid() { return p2AttackGrid; }
        inline std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP1DefenceGrid() { return p1DefenceGrid; }
        inline std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getP2DefenceGrid() { return p2DefenceGrid; }
		void resetP1HitsAttackGrid();
		void resetP1MissAttackGrid();
		void resetP2HitsAttackGrid();
		void resetP2MissAttackGrid();
        inline int getCurrP1Iroclad() const { return currP1Ironclad; }
        inline int getCurrP1Support() const { return currP1Support; }
        inline int getCurrP1Submarine() const { return currP1Submarine; }
        inline int getCurrP2Iroclad() const { return currP2Ironclad; }
        inline int getCurrP2Support() const { return currP2Support; }
        inline int getCurrP2Submarine() const { return currP2Submarine; }
		inline const std::array<BattleShip::Army*, 8>& getP1Army() const { return p1Army; }
		inline const std::array<BattleShip::Army*, 8>& getP2Army() const { return p2Army; }
        void addP1Army(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat);
        void addP2Army(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat);
        bool checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction,
                const BattleShip::army_t& army, const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& defencegrid) const;
        bool hitBoard(BattleShip::point_t target, 
                      const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& pDefenceGrid, 
                      std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& pAttackGrid);
        std::string getStringBoard(const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& defencegrid, 
                                   const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& attackgrid) const;
};

#endif // BOARD_H_
