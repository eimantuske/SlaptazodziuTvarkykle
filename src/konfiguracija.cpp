#include "konfiguracija.h"
#include "bibliotekos.h"
#include <fstream>
#include <iostream>
#include <unordered_map>


void Konfiguracija::sukurtiNumatytaji() {

    std::ofstream failas(configVardas);

    if(failas.is_open()){
        failas << "# ==========================================\n";
        failas << "# Pagrindiniai programos nustatymai\n";
        failas << "# ==========================================\n\n";

        failas << "rodytiLaika=true\n";
        failas << "sleptiSlaptazodzius=false\n";
        failas << "failas=paskyros.txt\n";
        failas.close();
    }else {
        // Jei dėl kažkokių priežasčių failo sukurti nepavyko (pvz., Windows neleidžia)
        std::cout << "KLAIDA: Nepavyko sukurti konfigūracijos failo: " << configVardas << std::endl;
    }
}

void Konfiguracija::uzkrauti() {
    std::ifstream failas(configVardas);

    // 1. Patikra: Jei failo nėra, sukuriam jį
    if (!failas.is_open()) {
        sukurtiNumatytaji(); 
        failas.open(configVardas); 

        if(!failas.is_open()){
            return;
        }
    } 

    // 2. SKAITYMAS: Šis kodas turi būti IŠORĖJE, kad veiktų VISADA
    std::string eilute;
    
    // Labai svarbu: išvalome senus nustatymus prieš kraunant naujus, 
    // kad neliktų senų šiukšlių atmintyje
    nustatymai.clear(); 

    while (std::getline(failas, eilute)) {
        eilute = nuimtiTarpus(eilute);
        
        if (eilute.empty() || eilute[0] == '#') continue;

        size_t skirtukas = eilute.find('=');
        if (skirtukas == std::string::npos) continue;

        std::string raktas = nuimtiTarpus(eilute.substr(0, skirtukas));
        std::string reiksme = nuimtiTarpus(eilute.substr(skirtukas + 1));

        nustatymai[raktas] = reiksme;
    }
    
    failas.close();
}

bool Konfiguracija::gautiLogini(const std::string& raktas, bool numatytoji) {
    // Tikriname, ar žodyne 'nustatymai' yra toks raktas
    if (nustatymai.find(raktas) != nustatymai.end()) {
        return nustatymai[raktas] == "true";
    }
    return numatytoji; // Jei nerasta, grąžiname tai, ką nurodei skliausteliuose
}

std::string Konfiguracija::nuimtiTarpus(const std::string& tekstas) {
    // Randame pirmą simbolį, kuris nėra tarpas ar nauja eilutė
    size_t pradzia = tekstas.find_first_not_of(" \t\r\n");
    
    // Jei visa eilutė tuščia
    if (pradzia == std::string::npos) return "";
    
    // Randame paskutinį simbolį, kuris nėra tarpas
    size_t pabaiga = tekstas.find_last_not_of(" \t\r\n");
    
    // Grąžiname „apkarpytą“ tekstą
    return tekstas.substr(pradzia, pabaiga - pradzia + 1);
}