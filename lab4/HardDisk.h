#ifndef HARDDISK_H
#define HARDDISK_H

#include "Processor.h"

// ЖОРСТКИЙ ДИСК (обсяг) успадковує ПРОЦЕСОР, а той – КОМП'ЮТЕР
class HardDisk : public Processor {
protected:
    int capacity;   // обсяг, Гбайт

public:
    HardDisk();
    HardDisk(const std::string& model, double price,
        const std::string& brand, double frequency, int capacity);
    ~HardDisk() override;

    int  getCapacity() const { return capacity; }
    void setCapacity(int c);

    void print(std::ostream& out) const override;
};

#endif
