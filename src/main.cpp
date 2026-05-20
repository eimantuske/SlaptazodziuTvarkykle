#include "bibliotekos.h"
#include "tvarkykle.h"
#include "shifravimas.h"

using namespace std;

int main() {
    // 1. Raktas
    string issaugotasRaktas = raktovedimas();
    
    // 2. Polimorfizmas: kuriame tvarkyklę per bazinę klasę
    programosVariklis* sistema = new tvarkykle();
    
    Konfiguracija config;
    config.uzkrauti(); 
    sistema->vykdyti(); // Kviečiame per ->

    // 3. Polimorfizmas saugumui:
    saugumoValdiklis* saugumas = new SifravimoValdiklis();
    if (saugumas->apdoroti("paskyros.txt", issaugotasRaktas)) {
        remove("paskyros.txt");
        cout << "Duomenys saugus." << endl;
    }

    // 4. Atlaisviname atmintį (Destruktoriai!)
    delete saugumas;
    delete sistema;

    return 0;
}