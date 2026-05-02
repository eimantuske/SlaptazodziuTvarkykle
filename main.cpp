#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

void LogoPrint() {
    cout << "[=================================]"    << endl;
    cout << "|                                 |"     << endl;
    cout << "|       PASKYRU TVARKYKLE         |"     << endl;
    cout << "|          v1.0 (2026)            |"   << endl;
    cout << "|                                 |"     << endl;
    cout << "[=================================]"     << endl;
};

void meniuUI() {
    LogoPrint();
    cout << "[  1. Prideti nauja paskyra       ]" << endl;
    cout << "[  2. Perziureti visas paskyras   ]" << endl;
    cout << "[  3. Iseiti is programos         ]" << endl;
    cout << "[=================================]" << endl;
};

int gautiPasirinkima() {
    int skaicius;
    
    while (true) {
        cout << "Iveskite skaiciu: ";
        cin >> skaicius;

        // 1. Patikriname, ar cin „nepasidavė“ (pvz., įvesta raidė)
        if (cin.fail()) {
            cin.clear(); // Panaikiname klaidos būseną
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Išmetame šiukšles iš atminties
            cout << "KLAIDA: Tai ne skaicius! Bandykite dar karta.\n" << endl;
        } 
        else {
            // Jei viskas gerai, grąžiname skaičių
            return skaicius;
        }
    }
};

 void Pasirinkimas() {

    int pasirinkimas = gautiPasirinkima();
    
    switch (pasirinkimas) {
        case 1:
            cout << "Pasirinkote: Prideti nauja paskyra\n" << endl;
            break;
        case 2:
            cout << "Pasirinkote: Perziureti visas paskyras\n" << endl;
            break;
        case 3:
            cout << "Pasirinkote: Iseiti is programos\n" << endl;
            break;
        default:
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n" << endl;
               break;  
    };
 };



int main() {
    meniuUI();
    Pasirinkimas();
    return 0;
};