#ifndef PROMPT_H_
#define PROMPT_H_
#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include "../BattleShip.h"
#include "../Utils/Utils.h"
#include "../Board/Board.h"

class BattleShip::Prompt {
    const static std::string _prompt;
    const static std::string _errorprompt;
    int _currIronclad {};
    int _currSupport {};
    int _currSubmarine {};
    std::stringstream output {};
    std::string _line {};
    BattleShip::Board _board {};
    inline void resetCount() { _currIronclad = _currSupport = _currSubmarine = 0; }
    std::string setupBoard(const std::string& input, const BattleShip::army_t& boat, const BattleShip::nplayer_t& player);
    std::string evalHuman(const std::string& input, const BattleShip::nplayer_t& player);
    void evalBot(const std::string& input, const BattleShip::nplayer_t& player);

    public:
        Prompt();
        bool setUpBoardHuman(const BattleShip::nplayer_t& player);
        bool setUpBoardBot(const BattleShip::nplayer_t& player);
        bool playGame(const BattleShip::nplayer_t& player1, const BattleShip::player_t& player1type, const BattleShip::nplayer_t& player2, const BattleShip::player_t& player2type, int starter);
};

#endif // PROMPT_H_
