#include "shifravimas.h"
#include "aes.hpp"
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

string raktovedimas() {
    string raktas;
    cout << "Iveskite master slaptazodi: ";
    cin >> raktas;
    return raktas;
}

// UŽRAKINIMAS (Encryption)
bool apdorotiFaila(const string& failoKelias, const string& raktas) {
    uint8_t key[32] = {0};
    for(size_t i = 0; i < raktas.length() && i < 32; i++) key[i] = (uint8_t)raktas[i];

    ifstream in(failoKelias, ios::binary);
    if (!in) return false;
    string turinys((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    pridetiPadding(turinys);

    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    
    // Naudojame 3 argumentus: kontekstas, buferis, ilgis
    AES_CBC_encrypt_buffer(&ctx, (uint8_t*)turinys.data(), (size_t)turinys.length());

    ofstream out(failoKelias, ios::binary);
    out.write(turinys.data(), turinys.length());
    out.close();

    return true;
}

// ATRAKINIMAS (Decryption)
bool isifruotiFaila(const string& failoKelias, const string& raktas) {
    uint8_t key[32] = {0};
    for(size_t i = 0; i < raktas.length() && i < 32; i++) key[i] = (uint8_t)raktas[i];

    ifstream in(failoKelias, ios::binary);
    if (!in) return false;
    string turinys((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    if (turinys.empty()) return true;

    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    
    // Naudojame 3 argumentus: kontekstas, buferis, ilgis
    AES_CBC_decrypt_buffer(&ctx, (uint8_t*)turinys.data(), (size_t)turinys.length());

    // Padding šalinimas
    if (!turinys.empty()) {
        int padding = (int)(unsigned char)turinys.back();
        if (padding > 0 && padding <= 16) {
            turinys.erase(turinys.length() - padding);
        }
    }

    ofstream out(failoKelias, ios::binary);
    out.write(turinys.data(), turinys.length());
    out.close();

    return true;
}