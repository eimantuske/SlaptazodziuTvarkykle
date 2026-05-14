#pragma once

#include <string>

class failoPagrindas {
    public:
        virtual ~failoPagrindas() {}

        virtual void skaityti() = 0;
};

class saugumoValdiklis {
    public:
        virtual ~saugumoValdiklis() {}
        virtual bool apdoroti(const std::string& kelias, const std::string& raktas) = 0;
};