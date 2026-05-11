#pragma once
#include <string>
#include <unordered_map>

class Konfiguracija {
private:
    const std::string configVardas = "config.cfg";

    std::unordered_map<std::string, std::string> nustatymai;
    
    void sukurtiNumatytaji();
    std::string nuimtiTarpus(const std::string& tekstas);

public:

    void uzkrauti();

    std::string gautiTeksta(const std::string& raktas, const std::string& numatytoji = "");
    bool gautiLogini(const std::string& raktas, bool numatytoji );

};

