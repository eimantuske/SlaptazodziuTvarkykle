#include "shifravimas.h"
#include "aes.hpp"
#include "bibliotekos.h"
#include "irankiai.h"
#include <iostream>
#include <fstream>
#include <vector>


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

#include <iostream>
#include <string>
#include <fstream>
#include "shifravimas.h"

using namespace std;

string raktovedimas() {
    string ivestasSlaptazodis;
    string seifas = "paskyros.enc";

    // SCENARIJUS A: Pirmas kartas (seifo nėra)
    if (!failasEgzistuoja(seifas)) {
        string patvirtinimas;
        cout << "Pirmas paleidimas. Sukurkite master slaptazodi." << endl;
        
        while (true) {

            valytiEkrana();

            cout << "Naujas slaptazodis: ";
            cin >> ivestasSlaptazodis;
            cout << "Pakartokite slaptazodi: ";
            cin >> patvirtinimas;

            if (ivestasSlaptazodis == patvirtinimas) {
                // Sukuriame pradinį failą
                ofstream f("paskyros.txt");
                f << "PASKYROS_OK" << endl; 
                f.close();

                // Užrakiname (tai sukurs paskyros.enc)
                apdorotiFaila("paskyros.txt", ivestasSlaptazodis);
                
                cout << "Seifas sukurtas. Galite dirbti." << endl;
                return ivestasSlaptazodis;
            }
            cout << "Slaptazodziai nesutampa!" << endl;
        }
    } 

    // SCENARIJUS B: Atidarymas
    while (true) {

         valytiEkrana();

        cout << "Iveskite slaptazodi: ";
        cin >> ivestasSlaptazodis;

        // Bandome atrakinti (tai sukurs paskyros.txt)
        if (isifruotiFaila(seifas, ivestasSlaptazodis)) {
            cout << "Atrakinta sėkmingai." << endl;
            return ivestasSlaptazodis;
        } else {
            cout << "Neteisingas slaptazodis! Bandykite dar karta." << endl;
        }
    }
}

// UŽRAKINIMAS (Encryption)
bool apdorotiFaila(const string& failoKelias, const string& slaptazodis) {
    uint8_t key[32] = {0};
    for(size_t i = 0; i < slaptazodis.length() && i < 32; i++) {
        key[i] = (uint8_t)slaptazodis[i];
    }

    uint8_t iv[16];
    std::random_device rd;
    for(int i=0; i<16; i++) iv[i] = rd() % 256;

    // Nuskaitome duomenis, kuriuos norime užrakinti
    ifstream in(failoKelias, ios::binary);
    if (!in) return false;
    vector<uint8_t> duomenys((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    // Įdedame parašą (16 baitų)
    uint8_t parasas[16] = {0};
    string pStr = "PASKYROS_OK";
    for(int i=0; i < pStr.length(); i++) parasas[i] = pStr[i];
    duomenys.insert(duomenys.begin(), parasas, parasas + 16);

    // Paddingas
    int paddingas = 16 - (duomenys.size() % 16);
    for (int i = 0; i < paddingas; i++) {
        duomenys.push_back((uint8_t)paddingas);
    }

    // Šifravimas
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, duomenys.data(), duomenys.size());

    // FIKSUOTAS VARDAS: Visada rašome į paskyros.enc
    ofstream out("paskyros.enc", ios::binary);
    if (!out) return false;
    out.write((char*)iv, 16);
    out.write((char*)duomenys.data(), duomenys.size());
    out.close();

    return true;
}
bool isifruotiFaila(const string& failoKelias, const string& slaptazodis) {
    // 1. Raktas
    uint8_t key[32] = {0};
    for(size_t i = 0; i < slaptazodis.length() && i < 32; i++) {
        key[i] = (uint8_t)slaptazodis[i];
    }

    // 2. Atidarymas
    ifstream in(failoKelias, ios::binary);
    if (!in) return false;

    // 3. IV nuskaitymas
    uint8_t iv[16];
    if (!in.read((char*)iv, 16)) {
        in.close();
        return false;
    }

    // 4. Duomenų nuskaitymas
    vector<uint8_t> turinys((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    if (turinys.empty()) return false;

    // 5. Dešifravimas
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, turinys.data(), turinys.size());

    // --- NAUJA DALIS: PATIKRA ---
    // Mes tikriname pirmuosius 11 simbolių, ar jie sutampa su "PASKYROS_OK"
    // Jei slaptažodis buvo blogas, čia bus atsitiktinės šiukšlės
    string patikra((char*)turinys.data(), 11); 
    if (patikra != "PASKYROS_OK") {
        // Slaptažodis neteisingas! 
        // Svarbu: grąžiname false dabar, kad neperrašytume failo šiukšlėmis
        return false; 
    }

    // Jei patikra praėjo, pašaliname tą "PASKYROS_OK" bloką (16 baitų)
    // kad liktų tik tavo tikrieji paskyrų duomenys
    turinys.erase(turinys.begin(), turinys.begin() + 16);
    // ----------------------------

    // 6. Padding šalinimas
    uint8_t padding = turinys.back();
    if (padding > 0 && padding <= 16) {
        turinys.resize(turinys.size() - padding);
    }

    // 7. Įrašymas
    string isvestiesFailas = failoKelias;
    if (isvestiesFailas.size() > 4) {
        isvestiesFailas.erase(isvestiesFailas.size() - 4); // Pašalina ".enc"
    }

    ofstream out("paskyros.txt", ios::binary); 
    if (!out) return false;
    out.write((char*)turinys.data(), turinys.size());
    out.close();

    return true;
}
