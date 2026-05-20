#pragma once
//visos programos bibliotekos
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <vector>
#include <random>

class Paskyra {
    private:
        int id;
        std::string svetaine;
        std::string vardas;
        std::string slaptazodis;
        std::string sukurta;
    public:
        Paskyra() : id(0), svetaine(""), vardas(""), slaptazodis(""), sukurta("") {}
        Paskyra(int _id, const std::string& _svetaine, const std::string& _vardas, const
    std::string& _slaptazodis, const std::string& _sukurta)
                : id(_id), svetaine(_svetaine), vardas(_vardas), slaptazodis(_slaptazodis), sukurta(_sukurta) {} 
        int getId() const { return id; }
        
        std::string getSvetaine() const { return svetaine; }
        std::string getVardas() const { return vardas; }
        std::string getSlaptazodis() const { return slaptazodis; }
        std::string getSukurta() const { return sukurta; }
        
        void setId(int _id) { id = _id; }
        void setSvetaine(const std::string& _svetaine) { svetaine = _svetaine; }
        void setVardas(const std::string& _vardas) { vardas = _vardas; }
        void setSlaptazodis(const std::string& _slaptazodis) { slaptazodis = _slaptazodis; }
        void setSukurta(const std::string& _sukurta) { sukurta = _sukurta; }        
};