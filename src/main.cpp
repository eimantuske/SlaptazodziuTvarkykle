#include "bibliotekos.h"
#include "tvarkykle.h"
#include "shifravimas.h"


using namespace std;

int main() {
    tvarkykle sistema;
    Konfiguracija config;

    string issaugotasRaktas = raktovedimas();

    isifruotiFaila("paskyros.txt", issaugotasRaktas);
   
    config.uzkrauti();
    sistema.vykdyti();

    apdorotiFaila("paskyros.txt", issaugotasRaktas);
    
    return 0;
}