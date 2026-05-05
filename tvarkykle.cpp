#include "tvarkykle.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <iomanip>
#include <algorithm>


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

                    string keitmasDidRaide = paskyra.svetaine;
                    zodzioTaisymas(keitmasDidRaide);

                    isvestis << paskyra.id << " "
                             << keitmasDidRaide << " "
                             << paskyra.vardas << " "
                             << paskyra.slaptazodis << endl;
                    }
                isvestis.close();
            }
            
        }

void tvarkykle::issaugotiPaskyra(const Paskyra& paskyra) {
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
                cout << "\n[!] Nera saugomu paskyru." << endl;
                lauktiEnter();
            } else {
                cout << "\n--- JUSU PASKYROS ---" << endl;

                cout << left << setw(5)  << "ID" 
                     << setw(18) << "SVETAINE" 
                     << setw(18) << "VARTOTOJAS" 
                     << setw(18) << "SLAPTAZODIS" << endl;
                cout << string(60, '-') << endl;

                for (const Paskyra& paskyra : paskyros) {
                    cout << left << setw(5)  << paskyra.id 
                         << setw(18) << paskyra.svetaine 
                         << setw(18) << paskyra.vardas 
                         << setw(18) << "************" << endl;
                }
                lauktiEnter();
            }
        }

int tvarkykle::gautiPasirinkima() {
    int pasirinkimas;

    skaitytiFaila();

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
            irasytiPaskyraUI();
            lauktiEnter();
            break;
        }
        case 2:
            perziuretiPaskyras();
            lauktiEnter();
            break;
        case 3:
            cout << "Aciu, kad naudojot programa. Iki!" << endl;
            return 3;
        default:
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
             // Leiskime vartotojui pamatyti klaidą prieš nuvalant ekraną
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

bool tvarkykle::tikrinimasSlaptazodzio(const std::string& slaptazodis) {
    if (slaptazodis.length() < 8) {
        return false;
    }
    bool turiDidziaja = false;
    bool turiMaziaja = false;
    bool turiSkaiciu = false;
    bool turiSpecialu = false;

    for (char c : slaptazodis) {

        if (isupper(c)) turiDidziaja = true;
        else if (islower(c)) turiMaziaja = true;
        else if (isdigit(c)) turiSkaiciu = true;
        else if (ispunct(c)) turiSpecialu = true; 
    }
    
    return turiDidziaja && turiMaziaja && turiSkaiciu && turiSpecialu;
}
        
void tvarkykle::irasytiPaskyraUI() {
    Paskyra naujaPaskyra;
    naujaPaskyra.id = paskyros.size() + 1;
    cout << "Iveskite svetaine: ";
    getline(cin, naujaPaskyra.svetaine);
    cout << "Iveskite vartotojo varda: ";
    getline(cin, naujaPaskyra.vardas);
    
    string slaptazodis;
    do {
        cout << "Iveskite slaptazodi: ";
        getline(cin, slaptazodis);
        if (!tikrinimasSlaptazodzio(slaptazodis)) {
            cout << "Slaptazodis turi buti bent 8 simboliu, ir tureti didziaja raide, maziaja raide, skaiciu ir specialu simboli." << endl;
        }
    } while (!tikrinimasSlaptazodzio(slaptazodis));
    
    naujaPaskyra.slaptazodis = slaptazodis;
    issaugotiPaskyra(naujaPaskyra);

    cout << "Paskyra sekmingai issaugota !" << endl;
}       

void tvarkykle::lauktiEnter() {
    cout << "\nSpauskite ENTER, kad gryztumete i meniu...";
    cin.ignore(1000, '\n');
    cin.get();
}

void tvarkykle::zodzioTaisymas(std::string& svetaine) {
     if (svetaine.empty()) return;
    // Pirmą raidę darome didžiąją
    svetaine[0] = std::toupper(static_cast<unsigned char>(svetaine[0]));
    // Visas likusias raides darome mažąsias
    if (svetaine.size() > 1) {
        std::transform(svetaine.begin() + 1, svetaine.end(), svetaine.begin() + 1,
                       [](unsigned char c) { return std::tolower(c); });
    }
}