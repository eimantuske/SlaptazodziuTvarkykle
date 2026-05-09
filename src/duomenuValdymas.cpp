#include "duomenuValdymas.h"
#include "irankiai.h"

using namespace std;

void duomenuValdymas::skaitytiFaila() {
        paskyros.clear();
        
        ifstream ivestis(failas);

        if (!ivestis.is_open()) {
                cerr << "Nepavyko atidaryti failo: " << failas << endl;
                return;
            }
            Paskyra naujaPaskyra;
            while (ivestis >> naujaPaskyra.id >> naujaPaskyra.svetaine >> naujaPaskyra.vardas >> naujaPaskyra.slaptazodis >> naujaPaskyra.sukurta) {
            paskyros.push_back(naujaPaskyra);
        }
        ivestis.close();
}

void duomenuValdymas::rasytiFaila() {
    ofstream isvestis(failas);
    
    if (!isvestis.is_open()) {
        cerr << "Nepavyko atidaryti failo rasyti: " << failas << endl;
        return;
    } else{
        for (const Paskyra& paskyra : paskyros) {
            
            string keitmasDidRaide = paskyra.svetaine;
            zodzioTaisymas(keitmasDidRaide);
            
            isvestis << paskyra.id << " "
            << keitmasDidRaide << " "
            << paskyra.vardas << " "
            << paskyra.slaptazodis << " "
            << paskyra.sukurta << endl;
        }
        isvestis.close();
    }
    
}

void duomenuValdymas::issaugotiPaskyra(const Paskyra& paskyra) {
            paskyros.push_back(paskyra);   
            rasytiFaila();
        }