#include "bibliotekos.h"
#include "tvarkykle.h"
#include "duomenuValdymas.h"
#include "irankiai.h"
#include "konfiguracija.h"

using namespace std;

void tvarkykle::isvalytiAtminti() {
    saugykla.paskyros.clear();
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
                cout << "Pasirinkite veiksma (1-3): ";
        }

void tvarkykle::rusiavimoMeniuUI() {
    LogoPrint();
        cout << "[  1. Rusuoti pagal Id            ]" << endl;
        cout << "[  2. Rusuoti pagal Svetaine      ]" << endl;
        cout << "[     (nuo A iki Z)               ]" << endl;
        cout << "[  3. Grizti                      ]" << endl;
        cout << "[=================================]" << endl;
       

}

void tvarkykle::perziuretiPaskyras() {
            
            if (saugykla.paskyros.empty()) {
                cout << "\n[!] Nera saugomu paskyru." << endl;
                lauktiEnter();
            } else {
                cout << "\n--- JUSU PASKYROS ---" << endl;

                cout << left << setw(5)  << "ID" 
                     << setw(18) << "SVETAINE" 
                     << setw(18) << "VARTOTOJAS" 
                     << setw(18) << "SLAPTAZODIS"
                     << setw(18) << "SUKURIMO DATA" << endl;
                cout << string(80, '-') << endl;

                for (const Paskyra& paskyra : saugykla.paskyros) {
                    cout << left << setw(5)  << paskyra.id 
                         << setw(18) << paskyra.svetaine 
                         << setw(18) << paskyra.vardas 
                         << setw(18) << "************" 
                         << setw(18) << paskyra.sukurta << endl;
                }
            }
        }

int tvarkykle::gautiPasirinkima() {
    int pasirinkimas;
    if (!(cin >> pasirinkimas)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1; // Grąžiname -1, jei vartotojas įvedė nesąmonę (pvz., raidę)
    }
    cin.ignore(1000, '\n'); // Išvalome Enter simbolį
    return pasirinkimas;
}
   
void tvarkykle::irasytiPaskyraUI() {

    saugykla.skaitytiFaila();

    Paskyra naujaPaskyra;

    naujaPaskyra.id = saugykla.paskyros.size() + 1;
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
    naujaPaskyra.sukurta = dabartinisLaikas();
    saugykla.issaugotiPaskyra(naujaPaskyra);

    cout << "Paskyra sekmingai issaugota !" << endl;
}       

void tvarkykle::lauktiEnter() {
    cout << "\nSpauskite ENTER, kad gryztumete i meniu...";
    cin.get();
}
    
     tvarkykle::tvarkykle() {
        konf.uzkrauti();
        saugykla.skaitytiFaila();
}

void tvarkykle::isvestiLentele() {
    
    konf.uzkrauti();
    
    // 1. Antraštė (Header)
    cout << left << setw(5) << "ID" 
         << setw(18) << "SVETAINE" 
         << setw(18) << "VARTOTOJAS";
    
    if (!konf.nst.sleptiSlaptazodzius) {
        cout << setw(18) << "SLAPTAZODIS";
    } else {
        cout << setw(18) << "SLAPTAZODIS (PASLEPTAS)";
    }

    if (konf.nst.rodytiLaika) cout << setw(20) << "DATA";
    cout << endl;

    // 2. Linija (priklauso nuo nustatymų ilgio)
    int linijosIlgis = 60 + (konf.nst.rodytiLaika ? 20 : 0);
    cout << string(linijosIlgis, '-') << endl;

    // 3. Duomenys
    for (const auto& p : saugykla.paskyros) {
        cout << left << setw(5) << p.id 
             << setw(18) << p.svetaine 
             << setw(18) << p.vardas;

        if (konf.nst.sleptiSlaptazodzius) {
            cout << setw(18) << "********";
        } else {
            cout << setw(18) << p.slaptazodis;
        }

        if (konf.nst.rodytiLaika) cout << setw(20) << p.sukurta;
        cout << endl;
    }
}

void tvarkykle::vykdyti() {
    // Failą nuskaitome TIK VIENĄ KARTĄ startuojant programai
    saugykla.skaitytiFaila();

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        meniuUI(); // 1. Parodome meniu

        int pasirinkimas = gautiPasirinkima(); // 2. Gauname vartotojo įvestį

        // 3. Reaguojame į įvestį
        switch (pasirinkimas) {
            case 1:
                irasytiPaskyraUI();
                lauktiEnter();
                break;
            case 2:
                rusiuotiPaskyras(); // Iškviečiame rūšiavimo / peržiūros meniu
                break;
            case 3:
                cout << "Aciu, kad naudojot programa. Iki!" << endl;
                return; // Baigiame programą
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void tvarkykle::rusiuotiPaskyras() {
    if (saugykla.paskyros.empty()) {
        cout << "\n[!] Nerasta paskyru rusiavimui." << endl;
        lauktiEnter();
        return; // Grįžtame atgal, jei tuščia
    }

    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        rusiavimoMeniuUI();

        int pasirinkimasRusiavimo = gautiPasirinkima(); // NAUDOJAME MŪSŲ ŠVARIĄ FUNKCIJĄ

        if (pasirinkimasRusiavimo == 3) return; // Grįžti atgal į pagrindinį meniu

        switch (pasirinkimasRusiavimo) {
            case 1: 
                sort(saugykla.paskyros.begin(), saugykla.paskyros.end(), [](const Paskyra& a, const Paskyra& b) {
                    return a.id < b.id;
                }); 
                isvestiLentele(); // NAUDOJAME TVARKINGĄ LENTELĘ SU NUSTATYMAIS
                lauktiEnter();
                return;
            
            case 2:
                sort(saugykla.paskyros.begin(), saugykla.paskyros.end(), [](const Paskyra& a, const Paskyra& b) {
                    return a.svetaine < b.svetaine;
                }); 
                isvestiLentele(); // NAUDOJAME TVARKINGĄ LENTELĘ SU NUSTATYMAIS
                lauktiEnter();
                return;

            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

