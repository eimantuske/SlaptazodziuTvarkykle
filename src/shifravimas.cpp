#include "shifravimas.h"
#include "aes.hpp"
#include "bibliotekos.h"
#include "irankiai.h"
#include "tvarkykle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

void pridetiPadding(string &duomenys) {
    int paddingas = 16 - (duomenys.length() % 16);
    for (int i = 0; i < paddingas; i++) {
        duomenys += (char)paddingas;
    }
}

bool failasEgzistuoja(const string& vardas) {
    ifstream f(vardas.c_str());
    return f.good();
}

string raktovedimas() {
    tvarkykle ui;
    string ivestasSlaptazodis;
    string seifas = "paskyros.enc";

    // PAKEITIMAS: Sukuriame tavo naujosios klasės objektą!
    SifravimoValdiklis sifruotojas;

    // SCENARIJUS A: Pirmas kartas (seifo nėra)
    if (!failasEgzistuoja(seifas)) {
        string patvirtinimas;
        cout << "Pirmas paleidimas. Sukurkite master slaptazodi." << endl;
        
        while (true) {
            SaugumoIrankiai::valytiEkrana();
            ui.LogoPrint();

            cout << "Naujas slaptazodis: ";
            cin >> ivestasSlaptazodis;
            cout << "Pakartokite slaptazodi: ";
            cin >> patvirtinimas;

            if (ivestasSlaptazodis == patvirtinimas) {
                ofstream f("paskyros.txt");
                f << "PASKYROS_OK" << endl; 
                f.close();

                // PAKEITIMAS: Kviečiame šifravimą per klasės objektą
                sifruotojas.apdoroti("paskyros.txt", ivestasSlaptazodis);
                
                cout << "Seifas sukurtas. Galite dirbti.\n" << endl;
                return ivestasSlaptazodis;
            }
            cout << "Slaptazodziai nesutampa!" << endl;
        }
    } 

    // SCENARIJUS B: Atidarymas
    while (true) {
        SaugumoIrankiai::valytiEkrana();
        ui.LogoPrint();

        cout << "Iveskite slaptazodi: ";
        cin >> ivestasSlaptazodis;

        // PAKEITIMAS: Kviečiame iššifravimą per klasės objektą
        if (sifruotojas.isifruotiFaila(seifas, ivestasSlaptazodis)) {
            cout << "Atrakinta sėkmingai." << endl;
            return ivestasSlaptazodis;
        } else {
            cout << "Neteisingas slaptazodis! Bandykite dar karta." << endl;
        }
    }
}

// PAKEITIMAS: Funkcija dabar priklauso klasei (pridėta SifravimoValdiklis:: ir pavadinimas 'apdoroti')
bool SifravimoValdiklis::apdoroti(const string& failoKelias, const string& slaptazodis) {
    uint8_t key[32] = {0};
    for(size_t i = 0; i < slaptazodis.length() && i < 32; i++) {
        key[i] = (uint8_t)slaptazodis[i];
    }

    uint8_t iv[16];
    std::random_device rd;
    for(int i=0; i<16; i++) iv[i] = rd() % 256;

    ifstream in(failoKelias, ios::binary);
    if (!in) return false;
    vector<uint8_t> duomenys((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    uint8_t parasas[16] = {0};
    string pStr = "PASKYROS_OK";
    for(int i=0; i < pStr.length(); i++) parasas[i] = pStr[i];
    duomenys.insert(duomenys.begin(), parasas, parasas + 16);

    int paddingas = 16 - (duomenys.size() % 16);
    for (int i = 0; i < paddingas; i++) {
        duomenys.push_back((uint8_t)paddingas);
    }

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, duomenys.data(), duomenys.size());

    ofstream out("paskyros.enc", ios::binary);
    if (!out) return false;
    out.write((char*)iv, 16);
    out.write((char*)duomenys.data(), duomenys.size());
    out.close();

    return true;
}

// PAKEITIMAS: Funkcija dabar priklauso klasei (pridėta SifravimoValdiklis::)
bool SifravimoValdiklis::isifruotiFaila(const string& failoKelias, const string& slaptazodis) {
    uint8_t key[32] = {0};
    for(size_t i = 0; i < slaptazodis.length() && i < 32; i++) {
        key[i] = (uint8_t)slaptazodis[i];
    }

    ifstream in(failoKelias, ios::binary);
    if (!in) return false;

    uint8_t iv[16];
    if (!in.read((char*)iv, 16)) {
        in.close();
        return false;
    }

    vector<uint8_t> turinys((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    if (turinys.empty()) return false;

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, turinys.data(), turinys.size());

    string patikra((char*)turinys.data(), 11); 
    if (patikra != "PASKYROS_OK") {
        return false; 
    }

    turinys.erase(turinys.begin(), turinys.begin() + 16);

    uint8_t padding = turinys.back();
    if (padding > 0 && padding <= 16) {
        turinys.resize(turinys.size() - padding);
    }

    string isvestiesFailas = failoKelias;
    if (isvestiesFailas.size() > 4) {
        isvestiesFailas.erase(isvestiesFailas.size() - 4); 
    }

    ofstream out("paskyros.txt", ios::binary); 
    if (!out) return false;
    out.write((char*)turinys.data(), turinys.size());
    out.close();

    return true;
}