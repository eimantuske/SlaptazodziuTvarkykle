#pragma once
#include "bibliotekos.h"
#include "baze.h" // BŪTINA įtraukti, kad veiktų paveldėjimas

// Paveldim iš FailoSąsajos (arba kito pavadinimo, kurį pasirinkai Baze.h faile)
class duomenuValdymas : public failoPagrindas {
    private:
        std::string failas = "paskyros.txt";
        std::vector<Paskyra> paskyros;
    public:
        // 1. Pervadiname arba pridedame skaityti(), kad atitiktų Bazinę klasę
        void skaityti() override; 
        
        void rasytiFaila();
        void issaugotiPaskyra(const Paskyra& paskyra);

        // 2. Metodai, kurių trūksta tvarkyklei
        void rusiuotiPagalID();
        void rusiuotiPagalSvetaine();
        
        // 3. Leidžiame tvarkyklei saugiai gauti paskyras
        const std::vector<Paskyra>& gautiVisasPaskyras() const { return paskyros; }


};