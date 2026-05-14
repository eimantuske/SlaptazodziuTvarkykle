#pragma once
#include <baze.h>
#include "bibliotekos.h"
#include "duomenuValdymas.h"
#include "irankiai.h"
#include "konfiguracija.h"

class programosVariklis {
    public:
        virtual ~programosVariklis() {}
        virtual void vykdyti() = 0;

};

class tvarkykle : public programosVariklis {
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

        ~tvarkykle() override;

        void isvestiLentele();
        void vykdyti() override;
        
};