#include "tvarkykle.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

// Konstruktorius (Reikalavimas!)
tvarkykle::tvarkykle() {
    // Konstruktoriuje inicijuojame duomenis
    konf.uzkrauti();
    saugykla.skaityti(); // Naudojame bazinės klasės metodą
    cout << "[SISTEMA]: Tvarkyklė sėkmingai inicijuota." << endl;
}

// Destruktorius (Reikalavimas!)
tvarkykle::~tvarkykle() {
    cout << "[SISTEMA]: Darbas baigiamas, resursai atlaisvinami." << endl;
}

void tvarkykle::isvalytiAtminti() {
    // Kadangi saugykla pati valdo vektorių, kreipiamės per metodą arba tiesiogiai,
    // jei duomenuValdymas klasėje paskyros yra protected/public
    // Šiuo atveju geriausia turėti valymo metodą saugykloje
}

void tvarkykle::LogoPrint() {
    cout << "[=================================]" << endl;
    cout << "|                                 |" << endl;
    cout << "|       PASKYRU TVARKYKLE         |" << endl;
    cout << "|          v1.0 (2026)            |" << endl;
    cout << "|                                 |" << endl;
    cout << "[=================================]" << endl;
}

void tvarkykle::meniuUI() {
    LogoPrint();
    cout << "[  1. Pridėti naują paskyrą       ]" << endl;
    cout << "[  2. Peržiūrėti/Rūšiuoti paskyras ]" << endl;
    cout << "[  3. Išeiti iš programos         ]" << endl;
    cout << "[=================================]" << endl;
    cout << "Pasirinkite veiksmą (1-3): ";
}

void tvarkykle::rusiavimoMeniuUI() {
    LogoPrint();
    cout << "[  1. Rūšiuoti pagal ID           ]" << endl;
    cout << "[  2. Rūšiuoti pagal Svetainę     ]" << endl;
    cout << "[     (nuo A iki Z)               ]" << endl;
    cout << "[  3. Grįžti                      ]" << endl;
    cout << "[=================================]" << endl;
    cout << "Pasirinkite veiksmą (1-3): ";
}

int tvarkykle::gautiPasirinkima() {
    int pasirinkimas;
    if (!(cin >> pasirinkimas)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    cin.ignore(1000, '\n');
    return pasirinkimas;
}

void tvarkykle::irasytiPaskyraUI() {

    string tempSvetaine, tempVardas, tempSlaptazodis;
    
    int naujasId = saugykla.gautiVisasPaskyras().size() + 1; // ID generuojame pagal esamų paskyrų kiekį

    cout << "Įveskite svetainę: ";

    getline(cin, tempSvetaine);

    cout << "Įveskite vartotojo vardą: ";

    getline(cin, tempVardas);

    
    do {
        cout << "Įveskite slaptažodį: ";
        getline(cin, tempSlaptazodis);
        // Naudojame tavo naują SaugumoIrankiai klasę
        if (!SaugumoIrankiai::tikrinimasSlaptazodzio(tempSlaptazodis)) {
            cout << "[!] Slaptažodis per silpnas (reikia 8 simb., didžiosios, mažosios raidžių, skaičiaus ir spec. ženklo)." << endl;
        }
    } while (!SaugumoIrankiai::tikrinimasSlaptazodzio(tempSlaptazodis));

   string tempSukurta = SaugumoIrankiai::dabartinisLaikas();
   
   Paskyra naujaPaskyra(naujasId, tempSvetaine, tempVardas, tempSlaptazodis, tempSukurta);

    saugykla.issaugotiPaskyra(naujaPaskyra);
    cout << "[V] Paskyra sėkmingai išsaugota!" << endl;
}

void tvarkykle::isvestiLentele() {
    // Gauname nustatymus iš konfigūracijos objekto
    bool sleptiSlaptazodi = konf.gautiLogini("sleptiSlaptazodzius", false);
    bool rodytiLaika = konf.gautiLogini("rodytiLaika", true);

    cout << "\n" << left << setw(5) << "ID"
         << setw(18) << "SVETAINE"
         << setw(18) << "VARTOTOJAS";

    if (!sleptiSlaptazodi) cout << setw(18) << "SLAPTAZODIS";
    else cout << setw(18) << "SLAPTAZODIS (***)";

    if (rodytiLaika) cout << setw(20) << "DATA";
    cout << endl;

    int linijosIlgis = 60 + (rodytiLaika ? 20 : 0);
    cout << string(linijosIlgis, '-') << endl;

    // Čia darome prielaidą, kad saugykla turi metodą gauti visoms paskyroms
    // arba paskyros yra prieinamos per getterį
    for (const auto& p : saugykla.gautiVisasPaskyras()) {
        cout << left << setw(5) << p.getId()
             << setw(18) << p.getSvetaine()
             << setw(18) << p.getVardas();

        if (sleptiSlaptazodi) cout << setw(18) << "********";
        else cout << setw(18) << p.getSlaptazodis();

        if (rodytiLaika) cout << setw(20) << p.getSukurta();
        cout << endl;
    }
}

// Pagrindinis programos ciklas (Polimorfizmas: override)
void tvarkykle::vykdyti() {
    while (true) {
        SaugumoIrankiai::valytiEkrana();
        meniuUI();

        int pasirinkimas = gautiPasirinkima();

        switch (pasirinkimas) {
            case 1:
                irasytiPaskyraUI();
                lauktiEnter();
                break;
            case 2:
               konf.uzkrauti(); // Perkrauname nustatymus, kad atspindėtų pakeitimus

                rusiuotiPaskyras();
                break;
            case 3:
                cout << "Ačiū, kad naudojotės programa. Iki!" << endl;
                return;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << endl;
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void tvarkykle::rusiuotiPaskyras() {
    // Čia turėtum patikrinti ar sąrašas ne tuščias per saugyklos metodą
    
    while (true) {
        SaugumoIrankiai::valytiEkrana();
        rusiavimoMeniuUI();

        int pasirinkimas = gautiPasirinkima();
        if (pasirinkimas == 3) return;

        // Rūšiavimo logika perkelta į saugyklą būtų dar geresnis OOP pavyzdys,
        // bet galime palikti ir čia, jei manipuliuojame duomenimis tiesiogiai.
        if (pasirinkimas == 1) {
            saugykla.rusiuotiPagalID();
            isvestiLentele();
            lauktiEnter();
            return;
        } 
        else if (pasirinkimas == 2) {
            saugykla.rusiuotiPagalSvetaine();
            isvestiLentele();
            lauktiEnter();
            return;
        }
        else {
            cout << "Neteisingas pasirinkimas." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void tvarkykle::lauktiEnter() {
    cout << "\nSpauskite ENTER, kad grįžtumėte į meniu...";
    cin.get();
}