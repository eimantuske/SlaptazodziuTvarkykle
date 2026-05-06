#include "konfiguracija.h"
#include <fstream>
#include <iostream>


void Konfiguracija::sukurtiNumatytaji() {
    std::ofstream failas(configVardas);
    
    if (failas.is_open()) {
        // Įrašome standartines eilutes į diską
        failas << "rodytiLaika=true\n";
        failas << "sleptiSlaptazodzius=true\n";
        failas << "failas=paskyros.txt\n";
        failas.close();
        
        // Užkrauname tas pačias reikšmes ir į atmintį, kad iškart veiktų
        nst.rodytiLaika = true;
        nst.sleptiSlaptazodzius = true;
        nst.failas = "paskyros.txt";
    }
}

void Konfiguracija::uzkrauti() {
    std::ifstream failas(configVardas);

    // 1 PATIKRA: Ar failas apskritai egzistuoja?
    if (!failas.is_open()) {
        sukurtiNumatytaji(); // Jei ne - sukuriam default config
        return;              // Ir baigiam darbą, nes daugiau nėra ką veikti
    }

    // 2 SKAITYMAS: Jei failas yra, skaitom kiekvieną eilutę
    std::string eilute;
    while (std::getline(failas, eilute)) {
        size_t skirtukas = eilute.find('='); // Ieškom lygybės ženklo
        
        if (skirtukas == std::string::npos) continue; // Jei eilutė be '=', ją ignoruojam

        // Kerpam tekstą į dvi dalis: prieš lygybę ir po lygybės
        std::string nustatymoPavadinimas = eilute.substr(0, skirtukas);
        std::string nustatymoDuomenys = eilute.substr(skirtukas + 1);

        // Priskiriam reikšmes
        if (nustatymoPavadinimas == "rodytiLaika") {
            nst.rodytiLaika = (nustatymoDuomenys == "true");
        } 
        else if (nustatymoPavadinimas == "sleptiSlaptazodzius") {
            nst.sleptiSlaptazodzius = (nustatymoPavadinimas == "true");
        } 
        else if (nustatymoPavadinimas== "failas") {
            nst.failas = nustatymoDuomenys;
        }
    }
    failas.close();
}