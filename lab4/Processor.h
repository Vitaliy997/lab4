#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Computer.h"

// ПРОЦЕСОР (марка, тактова частота) успадковує КОМП'ЮТЕР
class Processor : public Computer {
protected:
    std::string brand;       // марка процесора
    double      frequency;   // тактова частота, ГГц

public:
    Processor();
    Processor(const std::string& model, double price,
        const std::string& brand, double frequency);
    ~Processor() override;

    const std::string& getBrand() const { return brand; }
    double getFrequency() const { return frequency; }
    void   setFrequency(double f);

    void print(std::ostream& out) const override;
};

#endif
