#pragma once

#include "baze.h"
#include <string>

void pridetiPadding(std::string &duomenys);

bool failasEgzistuoja(const std::string & vardas);

std::string raktovedimas();

bool apdorotiFaila(const std::string& failoKelias, const std::string& slaptazodis);

bool isifruotiFaila(const std::string& failoKelias, const std::string& raktas);

class SifravimoValdiklis : public saugumoValdiklis {
    public:
        bool apdoroti(const std::string& failoKelias, const std::string& slaptazodis) override;
        bool isifruotiFaila(const std::string& failoKelias, const std::string& raktas);
};