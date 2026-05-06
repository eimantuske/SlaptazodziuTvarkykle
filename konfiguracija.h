#pragma once
#include <string>

struct nustatymai {
    bool rodytiLaika;
    bool sleptiSlaptazodzius;

    
    std::string failas = "paskyros.txt";
};

class Konfiguracija {
private:
    const std::string configVardas = "config.cfg";
    
    void sukurtiNumatytaji();

public:
   
    nustatymai nst;

    void uzkrauti();
};

