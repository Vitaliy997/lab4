#include "HardDisk.h"
#include <stdexcept>

HardDisk::HardDisk() : Processor(), capacity(0) {
    if (verbose) std::cout << "  [Конструктор] HardDisk (за замовчуванням)\n";
}

HardDisk::HardDisk(const std::string& m, double p, const std::string& b, double f, int c)
    : Processor(m, p, b, f), capacity(0) {
    setCapacity(c);
    if (verbose) std::cout << "  [Конструктор] HardDisk: " << capacity << " Гбайт\n";
}

HardDisk::~HardDisk() {
    if (verbose) std::cout << "  [Деструктор]  HardDisk: " << capacity << " Гбайт\n";
}

void HardDisk::setCapacity(int c) {
    if (c <= 0 || c > 100000)
        throw std::invalid_argument("Обсяг диска має бути в межах 1..100000 Гбайт");
    capacity = c;
}

void HardDisk::print(std::ostream& out) const {
    Processor::print(out);   // дані Computer + Processor
    out << "\n  Жорсткий диск: " << capacity << " Гбайт";
}
