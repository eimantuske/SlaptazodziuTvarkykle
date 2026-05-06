#include "irankiai.h"

std::string dabartinisLaikas() { 
    time_t dabar = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&dabar);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", &tstruct);
    
    return std::string(buf); // Konvertuojame char masyvą į saugų C++ string
}

void zodzioTaisymas(std::string& svetaine) {

     if (svetaine.empty()) return;
    // Pirmą raidę darome didžiąją
    svetaine[0] = std::toupper(static_cast<unsigned char>(svetaine[0]));
    // Visas likusias raides darome mažąsias
    if (svetaine.size() > 1) {
        std::transform(svetaine.begin() + 1, svetaine.end(), svetaine.begin() + 1,
                       [](unsigned char c) { return std::tolower(c); });
    }
}