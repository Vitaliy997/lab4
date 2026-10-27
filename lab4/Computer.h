#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <fstream>
#include <string>

// Базовий клас ієрархії: КОМП'ЮТЕР (модель, ціна)
class Computer {
protected:
    std::string model;   // модель
    double      price;   // ціна, грн

public:
    // Якщо true, конструктори й деструктори виводять повідомлення
    static bool verbose;

    Computer();
    Computer(const std::string& model, double price);
    virtual ~Computer();

    // Успадковувані методи
    const std::string& getModel() const { return model; }
    double getPrice() const { return price; }
    void   setPrice(double p);

    // Виведення в потік (замінюється в похідних класах)
    virtual void print(std::ostream& out) const;

    // Рядкове подання об'єкта (рядковий потік)
    std::string toString() const;

    // Запис інформації в файл; режим відкриття задається параметром
    bool saveToFile(const std::string& filename,
        std::ios_base::openmode mode = std::ios::out | std::ios::trunc) const;

    friend std::ostream& operator<<(std::ostream& out, const Computer& c);
};

#endif