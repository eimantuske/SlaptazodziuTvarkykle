#pragma once
#include "bibliotekos.h"

class duomenuValdymas {
    public:
        void skaitytiFaila();
        void rasytiFaila();
        void issaugotiPaskyra(const Paskyra& paskyra);

        std::string failas = "paskyros.txt";
        std::vector<Paskyra> paskyros;
};