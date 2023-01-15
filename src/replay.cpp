#include <iostream>
#include <string>
#include <fstream>
#define F_ARGUMENT "f"
#define V_ARGUMENT "v"

int main (int argc, char *argv[]){
    std::string argument = argv[1];
    std::ofstream myFile_pc;
    std::ofstream myFile_cc;
    myFile_pc.open("../logFiles/pcLogFile.txt");
    myFile_cc.open("../logFiles/pcLogFile.txt");


    if (argc == 1) {
        std::cout << "Nessun argomento fornito" << std::endl;
    }else if (argc == 2 && argument == F_ARGUMENT || argc == 2 && argument == V_ARGUMENT) {
        std::cout << "Nessun file fornito" << std::endl;
    }else if(argc == 3 && argument == V_ARGUMENT){
        
    }else if(argc == 4 && argument == F_ARGUMENT){

    }else{
        std::cout << "Comando non valido!" << std::endl;
    }

}