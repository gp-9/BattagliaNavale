#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <fstream>
#include <thread>
#include <ctime>
#include <chrono>
#include "../include/Prompt/Prompt.h"
#include "../include/Utils/Utils.h"
//#include "../include/Bot/Bot.h"

static void printTitle() {
    std::cout << "\033[2J\033[H" << R"(
  ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗      ███████╗███╗   ██╗██╗  ██╗ █████╗  ██████╗███████╗██████╗ 
  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗     ██╔════╝████╗  ██║██║  ██║██╔══██╗██╔════╝██╔════╝██╔══██╗
  ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝     █████╗  ██╔██╗ ██║███████║███████║██║     █████╗  ██║  ██║
  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝      ██╔══╝  ██║╚██╗██║██╔══██║██╔══██║██║     ██╔══╝  ██║  ██║
  ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║          ███████╗██║ ╚████║██║  ██║██║  ██║╚██████╗███████╗██████╔╝
  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝          ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚═════╝ 
                                                            
  ████████╗███╗   ███╗
  ╚══██╔══╝████╗ ████║
     ██║   ██╔████╔██║
     ██║   ██║╚██╔╝██║
     ██║   ██║ ╚═╝ ██║
     ╚═╝   ╚═╝     ╚═╝)" << '\n';

}

int main(void) {
    BattleShip::match_t typeofmatch = BattleShip::pc;
    BattleShip::Prompt prompt {};
    std::string line = "";
    std::string logDirectory = "../logFiles/";
    std::string filepath {};
    std::ofstream myFile;

    std::cout << "\033[2J\033[H" << "\033[33;1mSelezionare il tipo di partita che si intende giocare\033[0m\n"
              << std::setw(53) << "\033[35;1m-> \033[34;1mPC\033[0m: Giocatore contro computer;\n"
              << std::setw(52) << "\033[35;1m-> \033[34;1mCC\033[0m: Computer contro computer;\n"
              << std::setw(28) << "\033[35;1m-> \033[34;1mQ\033[0muit;\n"
              << "\033[36;1m>\033[35;1m>\033[0m ";
    while(true) {
        if(!std::getline(std::cin, line) || line == "Q" || line == "q" || line == "quit" || line == "Quit" || line == "QUIT") {
            if(line != "") {
                std::cout << "Uscendo da Battaglia Navale" << std::endl;
            } else {
                std::cout << "\nUscendo da Battaglia Navale" << std::endl;
            }
            return 0;
        } else {
            line = Utils::trim(line);
            if(line == "pc" || line == "PC" || line == "Pc" || line == "pC") {
                std::cout << "Selezionta partita Giocatore vs Computer" << std::endl;
                typeofmatch = BattleShip::pc;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            } else if(line == "cc" || line == "CC" || line == "Cc" || line == "cC") {
                std::cout << "Selezionata partita Computer vs Computer" << std::endl;
                typeofmatch = BattleShip::cc;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            } else {
                std::cerr << "Tipo di partita non valido\nPerfavore usare 'pc' per Giocatore vs Computer o 'cc' per Computer vs Computer\n\033[31;1m>>\033[0m ";
            }
        }
    }

    std::cout << "\033[2J\033[H" << "\033[33;1mSelezionare il file di log, se non ne verra' fornito uno\033[0m\n\033[36;1m>\033[35;1m>\033[0m ";

    while(true) {
        if(!std::getline(std::cin, line) || line == "Q" || line == "q" || line == "quit" || line == "Quit" || line == "QUIT") {
            if(line != "") {
                std::cout << "Uscendo da Battaglia Navale" << std::endl;
            } else {
                std::cout << "\nUscendo da Battaglia Navale" << std::endl;
            }
            return 0;
        } else {
            line = Utils::trim(line);
            if (line == "") {
                std::time_t now = std::time(nullptr);
                char timestr[100] = {};
                std::strftime(timestr, sizeof(timestr), "%F", std::localtime(&now));
                filepath = logDirectory + std::string(timestr) + "_log.txt";
                std::cout << "Il file " << filepath << " appena creato verra' usato per il logging dei comandi" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            } else {
                filepath = line;
                myFile.open(filepath);
                if(myFile.is_open()) {
                    std::cout << "Verra' usato il file " << line << " per il logging dei comandi" << std::endl;
                    myFile.close();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                } else {
                    std::cerr << "File inserito non valido o non esistente, Perfavore inserire un file valido\n\033[31;1m>>\033[0m ";
                }
            }
        }
    }
    printTitle();

	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> randomturn(0, 1);
	int startturn = randomturn(rng);
	std::uniform_int_distribution<std::mt19937::result_type> randomletter(65, 76);
	std::uniform_int_distribution<std::mt19937::result_type> randomnumber(1, 12);
    bool exited = false;
    myFile.open(filepath);
    myFile << "Hello there\n";
    myFile.close();
    BattleShip::nplayer_t player1 = BattleShip::nplayer_t(startturn);
    BattleShip::nplayer_t player2 = BattleShip::nplayer_t((startturn+1)%NPLAYER);

    if(typeofmatch == BattleShip::pc) {
        myFile.open(filepath);
        exited = prompt.setUpBoardHuman(player1, myFile); 
        if(!exited) {
            std::cout << "Aspettando che l'altro giocatore disponga le sue navi...\n";
            prompt.setUpBoardBot(player2, myFile);
        }

        //while(!exited) {
            //exited = prompt.playGame(BattleShip::p1, BattleShip::human, BattleShip::p2, BattleShip::bot, startturn);
        //}
        myFile.close();
        
    } else {
        std::cout << "Giocando partita Computer vs Computer\n";
        myFile.open(filepath);
        prompt.setUpBoardBot(player1, myFile);
        prompt.setUpBoardBot(player2, myFile);
        myFile.close();
    }
    
    return 0;
}
