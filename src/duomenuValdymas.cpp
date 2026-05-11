#include "duomenuValdymas.h"
#include "irankiai.h"
#include <iostream>
#include <fstream>

using namespace std;

// Svarbu: 'failas' kintamasis tavo klasėje turi būti "paskyros.txt"
void duomenuValdymas::skaitytiFaila() {
    paskyros.clear();
    
    // Skaitome iš iššifruoto laikino failo
    ifstream ivestis("paskyros.txt");

    if (!ivestis.is_open()) {
        // Jei failo nėra, tai normalu pirmą kartą paleidus
        return;
    }

    Paskyra naujaPaskyra;
    // Skaitome duomenis (tikimės, kad tarp duomenų nėra tarpų)
    while (ivestis >> naujaPaskyra.id >> naujaPaskyra.svetaine >> naujaPaskyra.vardas >> naujaPaskyra.slaptazodis >> naujaPaskyra.sukurta) {
        paskyros.push_back(naujaPaskyra);
    }
    ivestis.close();
}

void duomenuValdymas::rasytiFaila() {
    // Rašome į laikiną tekstinį failą
    ofstream isvestis("paskyros.txt");
    
    if (!isvestis.is_open()) {
        cerr << "KLAIDA: Nepavyko įrašyti laikino failo!" << endl;
        return;
    }

    for (const Paskyra& paskyra : paskyros) {
        string keitmasDidRaide = paskyra.svetaine;
        zodzioTaisymas(keitmasDidRaide); // Tavo papildoma funkcija
        
        isvestis << paskyra.id << " "
                 << keitmasDidRaide << " "
                 << paskyra.vardas << " "
                 << paskyra.slaptazodis << " "
                 << paskyra.sukurta << endl;
    }
    isvestis.close();
}

void duomenuValdymas::issaugotiPaskyra(const Paskyra& paskyra) {
    paskyros.push_back(paskyra);   
    rasytiFaila(); // Kiekvieną kartą pridedant paskyrą, atnaujiname .txt failą
}

