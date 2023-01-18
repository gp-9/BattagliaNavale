#ifndef GRID_H_
#define GRID_H_
#include <array>
#include "../../BattleShip.h"
#define GRIDSIZE 12

class BattleShip::Grid {
    std::array<std::array<char, GRIDSIZE>, GRIDSIZE> _grid {};
    constexpr bool verifiyPosition(const BattleShip::point_t& position) const { return (position.xPos >= 0 && position.xPos < GRIDSIZE) && (position.yPos >= 0 && position.yPos < GRIDSIZE); }

    public:
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getGrid() const { return _grid; }

    protected:
        Grid() {}
        virtual ~Grid() {}
        inline char getGridPosition(const BattleShip::point_t& position) const { if(verifiyPosition(position)) return _grid[position.xPos][position.yPos]; return -1;}
        bool modifyGrid(const BattleShip::point_t& position, const char element);
        inline bool assertCharEq(const BattleShip::point_t& position, const char element) const { return _grid[position.xPos][position.yPos] == element; }
};

#endif // GRID_H_
