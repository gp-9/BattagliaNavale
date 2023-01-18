#ifndef PROMPT_H_
#define PROMPT_H_
#include <chrono>
#include <ctime>
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
        bool setUpBoardHuman(const BattleShip::nplayer_t& player, std::ofstream& myFile);
        bool setUpBoardHumanForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile);
        bool setUpBoardBot(const BattleShip::nplayer_t& player, std::ofstream& myFile);
        bool setUpBoardBotForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile);
        bool playGame(const BattleShip::nplayer_t& player1, const BattleShip::player_t& player1type, const BattleShip::nplayer_t& player2, 
                const BattleShip::player_t& player2type, int starter, int moves, std::ofstream& myFile);
};

#endif // PROMPT_H_
