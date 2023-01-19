#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

// Definizione di alcune costanti usate in tutto il programma
#define NPLAYER 2 // Numero  di giocatori
#define GRIDSIZE 12 // Dimensione della griglia
#define SPACESIZE 10 // Usato per quando si devono stampare le due griglie una vincino all'altra

// Costanti riferite alla corazzata
#define IRONCLAD 3
#define IRONCLADSIZE 5
#define IRONCLADARMOR 5
#define IRONCLADUNIT 'C'
#define IRONCLADDAMAGE 'c'

// Costanti riferite alla nave di supporto
#define SUPPORT 3
#define SUPPORTSIZE 3
#define SUPPORTARMOR 3
#define SUPPORTUNIT 'S'
#define SUPPORTDAMAGE 's'

// Costanti riferite al sottomarino
#define SUBMARINE 2
#define SUBMARINESIZE 1
#define SUBMARINEARMOR 1
#define SUBMARINEUNIT 'E'
#define SUBMARINEDAMAGE 'e'

// Costanti per la griglia di attacco
#define HIT 'X'
#define MISS 'O'
#define DISCOVERED 'Y'

// Numero totale di navi a disposizione di ogni giocatore
#define TOTALARMYCOUNT (IRONCLAD + SUPPORT + SUBMARINE)

namespace BattleShip {
    typedef enum { pc, cc } match_t;
    typedef enum { northsouth, eastwest } direction_t;
    typedef struct { int xPos; int yPos; } point_t;
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
