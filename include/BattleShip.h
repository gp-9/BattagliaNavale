#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_
#include <cstdint>

#define NPLAYER 2
#define IRONCLADSIZE 5
#define SUPPORTSIZE 3
#define SUBMARINESIZE 1

namespace BattleShip {
    typedef enum { pc, cc } match_t;
    typedef enum { northsouth, eastwest } direction_t;
    typedef struct { std::uint32_t xPos; std::uint32_t yPos; } point_t;
    typedef enum { submarine, support, ironclad } army_t;
	typedef enum { p1, p2 } nplayer_t;
    typedef enum { bot, human } player_t;

    class Army;
    class Board;
    class Ironclad;
    class Support;
    class Submarine;
    class Grid;
    class AttackGrid;
    class DefenceGrid;
	class Bot;
    class Prompt;
}

#endif // BATTLESHIP_H_
