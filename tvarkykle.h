#pragma once
#include "bibliotekos.h"
#include "duomenuValdymas.h"
#include "irankiai.h"

class tvarkykle {
    private:
        duomenuValdymas saugykla;    

        const std::string configFailas = "config.txt";

        void isvalytiAtminti();
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
        tvarkykle();
};