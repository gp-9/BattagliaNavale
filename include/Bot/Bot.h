#ifndef BOT_H_
#define BOT_H_
#include <array>
#include <random>
#include <stdexcept>
#include "../BattleShip.h"
#include "../Board/Board.h"

class BattleShip::Bot {
    std::random_device rnd;
	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> randomArmy;
	std::uniform_int_distribution<std::uint32_t> randomCoordinate;
    BattleShip::Board& _board;
    BattleShip::nplayer_t _player;
    std::array<BattleShip::Army*, 8> _army;

    
    public:
        Bot(BattleShip::Board& board, const BattleShip::nplayer_t& player);
        bool makeAction();
};

#endif // BOT_H_
