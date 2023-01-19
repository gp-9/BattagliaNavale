#ifndef PROMPT_H_
#define PROMPT_H_
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <thread>
#include "../BattleShip.h"
#include "../Utils/Utils.h"
#include "../Board/Board.h"

// Struct usato per ottenere l'effetto di una tupla
struct ptuple { std::string output; bool done; };

class BattleShip::Prompt {
    const static std::string _prompt;
    const static std::string _errorprompt;
    std::array<BattleShip::player_t, NPLAYER> _players {};
	std::random_device _rnd;
	std::mt19937 _rng;
	std::uniform_int_distribution<std::mt19937::result_type> _randomletter;
	std::uniform_int_distribution<std::mt19937::result_type> _randomnumber;
    int _currIronclad {};
    int _currSupport {};
    int _currSubmarine {};
    std::stringstream output {};
    std::string _line {};
    BattleShip::Board _board {};
    inline void resetCount() { _currIronclad = _currSupport = _currSubmarine = 0; }
    std::string setupBoard(const std::string& input, const BattleShip::army_t& boat, const BattleShip::nplayer_t& player);
    ptuple evalHuman(const std::string& input, const BattleShip::nplayer_t& player);
    void evalBot(const std::string& input, const BattleShip::nplayer_t& player);

    public:
        Prompt();
        bool setUpBoardHuman(const BattleShip::nplayer_t& player, std::ofstream& myFile);
        bool setUpBoardHumanForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile);
        bool setUpBoardBot(const BattleShip::nplayer_t& player, std::ofstream& myFile);
        bool setUpBoardBotForReplay(const BattleShip::nplayer_t& player, std::ifstream& myFile);
        bool playGameForReplay(const BattleShip::nplayer_t& player1, const BattleShip::player_t& player1type, const BattleShip::nplayer_t& player2, 
                const BattleShip::player_t& player2type, int starter, int moves, std::ifstream& myFile);
        void setUpGamePC(int starter);
        void setUpGameCC(int stater);
        bool makeTurnPC(int moves, std::ofstream& myFile);
        void makeTurnCC(int moves, std::ofstream& myFile);
        inline bool checkVictory() const { return _board.isGameOver(); }
};

#endif // PROMPT_H_
