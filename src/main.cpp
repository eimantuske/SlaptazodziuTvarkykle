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

    // 3. Pabaigoje, prieš išeinant, vėl užšifruojame
    cout << "Uzsifruojama..." << endl;
    // Nurodome "paskyros.txt", o funkcija pati sukurs "paskyros.enc"
    if (apdorotiFaila("paskyros.txt", issaugotasRaktas)) {
        remove("paskyros.txt"); 
        cout << "Duomenys saugus." << endl;
    }
    return 0;
}