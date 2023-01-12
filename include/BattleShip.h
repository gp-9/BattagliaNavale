#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_
#include <cstdint>

#define GRIDSIZE 12

namespace BattleShip {
    typedef enum { pc, cc } match_t;
    typedef enum { northsouth, eastwest } direction_t;
    typedef struct { std::uint32_t xPos; std::uint32_t yPos; } point_t;
    typedef enum { submarine, support, ironclad } army_t;

    class Army;
    class Board;
    class Ironclad;
    class Support;
    class Submarine;
}

#endif // BATTLESHIP_H_
