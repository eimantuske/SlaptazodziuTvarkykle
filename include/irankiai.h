#pragma once
#include <string>

class SaugumoIrankiai {
    public:
        static bool tikrinimasSlaptazodzio(const std::string& slaptazodis);
        static void zodzioTaisymas(std::string& svetaine);
        static std::string dabartinisLaikas();
        static void valytiEkrana();
};