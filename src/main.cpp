#include "bibliotekos.h"
#include "tvarkykle.h"
#include "shifravimas.h"


using namespace std;

int main() {
    tvarkykle sistema;
    Konfiguracija config;

    // 1. Raktų vedimas: 

    string issaugotasRaktas = raktovedimas();

    // 2. Įkrauname duomenis iš jau iššifruoto "paskyros.txt" failo

    config.uzkrauti(); 
    sistema.vykdyti();


    if (apdorotiFaila("paskyros.txt", issaugotasRaktas)) {
        remove("paskyros.txt"); 
        cout << "Duomenys saugus." << endl;
    }
    return 0;
}