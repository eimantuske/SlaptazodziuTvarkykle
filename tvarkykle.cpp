#include "tvarkykle.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <sstream>

using namespace std;

void tvarkykle::isvalytiAtminti() {
    paskyros.clear();
        }

void tvarkykle::skaitytiFaila() {
        paskyros.clear();
        
        ifstream ivestis(failas);

        if (!ivestis.is_open()) {
                cerr << "Nepavyko atidaryti failo: " << failas << endl;
                return;
            }
            Paskyra naujaPaskyra;
            while (ivestis >> naujaPaskyra.id >> naujaPaskyra.svetaine >> naujaPaskyra.vardas >> naujaPaskyra.slaptazodis) {
            paskyros.push_back(naujaPaskyra);
        }
        ivestis.close();
}

void tvarkykle::rasytiFaila() {
            ofstream isvestis(failas);

            if (!isvestis.is_open()) {
                cerr << "Nepavyko atidaryti failo rasyti: " << failas << endl;
                return;
            } else{
                for (const Paskyra& paskyra : paskyros) {
                    isvestis << paskyra.id << " "
                             << paskyra.svetaine << " "
                             << paskyra.vardas << " "
                             << paskyra.slaptazodis << endl;
                    }
                isvestis.close();
            }
            
        }

void tvarkykle::pridetiPaskyra(const Paskyra& paskyra) {
            paskyros.push_back(paskyra);   
            rasytiFaila();
        }
        
void tvarkykle::LogoPrint() {
                cout << "[=================================]"    << endl;
                cout << "|                                 |"     << endl;
                cout << "|       PASKYRU TVARKYKLE         |"     << endl;
                cout << "|          v1.0 (2026)            |"   << endl;
                cout << "|                                 |"     << endl;
                cout << "[=================================]"     << endl;
        }

void tvarkykle::meniuUI() {
                LogoPrint();
                cout << "[  1. Prideti nauja paskyra       ]" << endl;
                cout << "[  2. Perziureti visas paskyras   ]" << endl;
                cout << "[  3. Iseiti is programos         ]" << endl;
                cout << "[=================================]" << endl;
        }

void tvarkykle::perziuretiPaskyras() {
            skaitytiFaila();

            if (paskyros.empty()) {
                cout << "Nera paskyru." << endl;
                cout << "\nSpauskite ENTER, kad gryztumete i meniu...";
                cin.get();
            } else {
                cout << "Paskyros:" << endl;
                for (const Paskyra& paskyra : paskyros) {
                   cout << paskyra.id << ". [" << paskyra.svetaine << "] " << paskyra.vardas << " : " << paskyra.slaptazodis << endl;
                    }
                cout << "\nSpauskite ENTER, kad gryztumete i meniu...";
                cin.get();
            }
        }

int tvarkykle::gautiPasirinkima() {
    int pasirinkimas;
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // 1. Pirmiausia nupiešiame UI
        meniuUI();
        cout << "Pasirinkite veiksma (1-3): ";

        // 2. Tik dabar laukiame įvesties
        if (!(cin >> pasirinkimas)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // Išvalome Enter simbolį
        cin.ignore(1000, '\n');

        // 3. Apdorojame pasirinkimą
        switch (pasirinkimas) {
            case 1: {
                Paskyra naujaPaskyra;
                naujaPaskyra.id = paskyros.size() + 1;
                    cout << "Iveskite svetaine: ";
                    getline(cin, naujaPaskyra.svetaine);
                    cout << "Iveskite vartotojo varda: ";
                    getline(cin, naujaPaskyra.vardas);
                    cout << "Iveskite slaptazodi: ";
                    getline(cin, naujaPaskyra.slaptazodis);
                    pridetiPaskyra(naujaPaskyra);

                    cout << "Paskyra sekmingai prideta!" << endl;
                    cout << "\nSpauskite ENTER, kad gryztumete i meniu...";
                    cin.get();
                break;
            }
            case 2:
                perziuretiPaskyras();
                break;
            case 3:
                cout << "Aciu, kad naudojot programa. Iki!" << endl;
                return 3;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                // Leiskime vartotojui pamatyti klaidą prieš nuvalant ekraną
                #include <chrono>
                #include <thread>
                std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

        
        
