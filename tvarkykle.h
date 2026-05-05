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
        const std::string configFailas = "config.txt";

        void isvalytiAtminti();
        void skaitytiFaila();
        void rasytiFaila();
        void issaugotiPaskyra(const Paskyra& paskyra);
        bool tikrinimasSlaptazodzio(const std::string& slaptazodis);
        void irasytiPaskyraUI();
        void lauktiEnter();
        void zodzioTaisymas(std::string& svetaine);
        void rusiuotiPaskyras();

    public:
        void LogoPrint();
        void meniuUI();
        void rusiavimoMeniuUI();
        void perziuretiPaskyras();
        int gautiPasirinkima();
};