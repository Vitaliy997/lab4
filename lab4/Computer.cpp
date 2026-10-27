#include "Computer.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

bool Computer::verbose = false;

Computer::Computer() : model(""), price(0.0) {
    if (verbose) std::cout << "  [Конструктор] Computer (за замовчуванням)\n";
}

Computer::Computer(const std::string& m, double p) : model(m), price(0.0) {
    if (m.empty())
        throw std::invalid_argument("Модель комп'ютера не може бути порожньою");
    setPrice(p);
    if (verbose) std::cout << "  [Конструктор] Computer: " << model << "\n";
}

Computer::~Computer() {
    if (verbose) std::cout << "  [Деструктор]  Computer: " << model << "\n";
}

void Computer::setPrice(double p) {
    if (p < 0.0)
        throw std::invalid_argument("Ціна не може бути від'ємною");
    price = p;
}

void Computer::print(std::ostream& out) const {
    std::ios_base::fmtflags f = out.flags();
    out << "Комп'ютер: модель " << model << ", ціна " << std::fixed
        << std::setprecision(2) << price << " грн";
    out.flags(f);
}

std::string Computer::toString() const {
    std::ostringstream os;
    print(os);
    return os.str();
}

bool Computer::saveToFile(const std::string& filename, std::ios_base::openmode mode) const {
    std::ofstream out(filename.c_str(), mode);
    if (!out.is_open()) return false;
    print(out);
    out << "\n----------------------------------------\n";
    return out.good();
}

std::ostream& operator<<(std::ostream& out, const Computer& c) {
    c.print(out);   // віртуальний виклик: виводиться інформація реального типу
    return out;
}