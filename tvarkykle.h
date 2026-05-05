#pragma once
#include <string>
#include <vector>

struct Paskyra {
    int id;
    std::string svetaine;
    std::string vardas;
    std::string slaptazodis;
};

class tvarkykle {
    private:
        std::vector<Paskyra> paskyros;
        const std::string failas = "paskyros.txt";

        void isvalytiAtminti();
        void skaitytiFaila();
        void rasytiFaila();
        void issaugotiPaskyra(const Paskyra& paskyra);
        bool TikrinimasSlaptazodzio(const std::string& slaptazodis);
        void irasytiPaskyraUI();
        void lauktiEnter();

    public:
        void LogoPrint();
        void meniuUI();
        void perziuretiPaskyras();
        int gautiPasirinkima();
};