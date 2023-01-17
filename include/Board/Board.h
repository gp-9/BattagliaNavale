#ifndef BOARD_H_
#define BOARD_H_
#include <array>
#include <memory>
#include <string>
#include <sstream>
#include "../BattleShip.h"
#include "../Army/Army.h"
#include "../Army/Ironclad/Ironclad.h"
#include "../Army/Support/Support.h"
#include "../Army/Submarine/Submarine.h"
#include "Grid/Grid.h"
#include "Grid/AttackGrid/AttackGrid.h"
#include "Grid/DefenceGrid/DefenceGrid.h"

#define SPACESIZE 10
#define TOTALARMYCOUNT (IRONCLAD + SUPPORT + SUBMARINE)

class BattleShip::Board {
    // Si usa il numer del giocatore per determinare l'offset e quindi a chi appartiene la board voluta
    std::array<std::unique_ptr<BattleShip::DefenceGrid>, NPLAYER> _defenceGrids = {nullptr};
    std::array<std::unique_ptr<BattleShip::AttackGrid>, NPLAYER> _attackGrids = {nullptr};
    // Matrice di pointer alle navi, la stessa coordinata in TOTALARMYCOUNT indica la stessa n-esima nave dei giocatori
    // a cui si fa l'accesso tramite l'enum nplayer_t, che avendo valori da 0 al massimo numero di giocatori, viene usato come offset per 
    // determinare di quale giocatore sia l'unita' n
    std::array<std::array<std::unique_ptr<BattleShip::Army>, NPLAYER>, TOTALARMYCOUNT> _armies;
    Board(const BattleShip::Board&) = delete;
    BattleShip::Board& operator=(const BattleShip::Board&) = delete;
	Board(const BattleShip::Board&&) = delete;
	BattleShip::Board& operator=(const BattleShip::Board&&) = delete;

    public:
        Board();
        ~Board() {}
		void resetHitsAttackGrid(const BattleShip::nplayer_t& player);
		void resetMissAttackGrid(const BattleShip::nplayer_t& player);
        void resetSonarAttackGrid(const BattleShip::nplayer_t& player);
        void addArmy(const BattleShip::nplayer_t& player, const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& boat);
        bool checkPosition(const BattleShip::point_t& center, const BattleShip::direction_t& direction, const BattleShip::army_t& army, const BattleShip::nplayer_t& player) const;
        bool makeAction(const BattleShip::point_t& origin, const BattleShip::point_t& target, const BattleShip::nplayer_t& player);
        inline int getCurrIronclad(const BattleShip::nplayer_t& player) const { return _defenceGrids[player]->getIronclad(); }
        inline int getCurrSupport(const BattleShip::nplayer_t& player) const { return _defenceGrids[player]->getSupport(); }
        inline int getCurrSubmarine(const BattleShip::nplayer_t& player) const { return _defenceGrids[player]->getSubmarine(); }
        inline bool isPlayerSetup(const BattleShip::nplayer_t& player) const { return _defenceGrids[player]->isGameStarted(); }
        inline bool isGameStarted() const { return _defenceGrids[BattleShip::p1]->isGameStarted() && _defenceGrids[BattleShip::p2]->isGameStarted(); }
        inline bool isGameOver() const { return _defenceGrids[BattleShip::p1]->matchTermianted() || _defenceGrids[BattleShip::p2]->matchTermianted(); }
        std::string getPlayerStringBoard(const BattleShip::nplayer_t& player) const;
};

#endif // BOARD_H_
