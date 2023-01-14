#include "../../include/Bot/Bot.h"

BattleShip::Bot::Bot(BattleShip::Board& board, const BattleShip::nplayer_t& player) 
    : _board {board}, _player {player} {
    if(_player == BattleShip::p1) _army = _board.getP1Army();
    else _army = _board.getP2Army();
    rng.seed(rnd());
    randomArmy = std::uniform_int_distribution<std::mt19937::result_type>(0, 7);
    randomCoordinate = std::uniform_int_distribution<std::uint32_t>(1, 12);
}

bool BattleShip::Bot::makeAction() {
    int narmy = randomArmy(rng);
    bool done = false;
    while(!done) {
        BattleShip::point_t origin = { randomCoordinate(rng), randomCoordinate(rng) };
        BattleShip::point_t target = { randomCoordinate(rng), randomCoordinate(rng) };
        try {
            _army[narmy]->makeAction(origin, target ,_board); 
            done = true;
        } catch(const std::invalid_argument& e) {
        }
    }
    return done;
}
