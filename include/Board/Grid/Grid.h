#ifndef GRID_H_
#define GRID_H_
#include <array>
#include "../../BattleShip.h"
#define GRIDSIZE 12

class BattleShip::Grid {
    public:
        inline const std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getGrid() const { return _grid; }
        inline std::array<std::array<char, GRIDSIZE>, GRIDSIZE>& getGrid() { return _grid; }

    protected:
        std::array<std::array<char, GRIDSIZE>, GRIDSIZE> _grid {};
        Grid() {}
        virtual ~Grid() {}
};

#endif // GRID_H_
