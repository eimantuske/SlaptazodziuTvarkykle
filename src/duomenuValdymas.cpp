#include "baze.h"
#include "duomenuValdymas.h"
#include "irankiai.h"
#include <iostream>
#include <fstream>

using namespace std;

// Svarbu: 'failas' kintamasis tavo klasėje turi būti "paskyros.txt"
void duomenuValdymas::skaityti() {
    paskyros.clear();
    
    // Skaitome iš iššifruoto laikino failo
    ifstream ivestis("paskyros.txt");

    if (!ivestis.is_open()) {
        // Jei failo nėra, tai normalu pirmą kartą paleidus
        return;
    }

    int tempId;
    string tempSvetaine, tempVardas, tempSlaptazodis, tempSukurta;
    
    // Skaitome duomenis (tikimės, kad tarp duomenų nėra tarpų)
    while (ivestis >> tempId >> tempSvetaine >> tempVardas >> tempSlaptazodis >> tempSukurta) {
        // Sukuriame objektą per konstruktorių ir įdedame į vektorių
        Paskyra naujaPaskyra(tempId, tempSvetaine, tempVardas, tempSlaptazodis, tempSukurta);
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
        string keitmasDidRaide = paskyra.getSvetaine();
        SaugumoIrankiai::zodzioTaisymas(keitmasDidRaide); // Tavo papildoma funkcija
        
        isvestis << paskyra.getId() << " "
                 << keitmasDidRaide << " "
                 << paskyra.getVardas() << " "
                 << paskyra.getSlaptazodis() << " "
                 << paskyra.getSukurta() << endl;
    }
    isvestis.close();
}

void duomenuValdymas::issaugotiPaskyra(const Paskyra& paskyra) {
    paskyros.push_back(paskyra);   
    rasytiFaila(); // Kiekvieną kartą pridedant paskyrą, atnaujiname .txt failą
}

void duomenuValdymas::rusiuotiPagalID() {
    std::sort(paskyros.begin(), paskyros.end(), [](const Paskyra& a, const Paskyra& b) {
        return a.getId() < b.getId();
    });
}

void duomenuValdymas::rusiuotiPagalSvetaine() {
    std::sort(paskyros.begin(), paskyros.end(), [](const Paskyra& a, const Paskyra& b) {
        return a.getSvetaine() < b.getSvetaine();
    });
}

