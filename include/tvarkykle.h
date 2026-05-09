#pragma once
#include "bibliotekos.h"
#include "duomenuValdymas.h"
#include "irankiai.h"
#include "konfiguracija.h"

class tvarkykle {
    private:
        duomenuValdymas saugykla;  
        Konfiguracija konf;  

        void isvalytiAtminti();
        void irasytiPaskyraUI();
        void lauktiEnter();
        void rusiuotiPaskyras();

    public:
        void LogoPrint();
        void meniuUI();
        void rusiavimoMeniuUI();
        void perziuretiPaskyras();
        int gautiPasirinkima();
        tvarkykle();
        void isvestiLentele();
        void vykdyti();
        
};