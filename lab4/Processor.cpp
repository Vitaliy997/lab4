#include "Processor.h"
#include <iomanip>
#include <stdexcept>

Processor::Processor() : Computer(), brand(""), frequency(0.0) {
    if (verbose) std::cout << "  [Конструктор] Processor (за замовчуванням)\n";
}

Processor::Processor(const std::string& m, double p, const std::string& b, double f)
    : Computer(m, p), brand(b), frequency(0.0) {
    if (b.empty())
        throw std::invalid_argument("Марка процесора не може бути порожньою");
    setFrequency(f);
    if (verbose) std::cout << "  [Конструктор] Processor: " << brand << "\n";
}

Processor::~Processor() {
    if (verbose) std::cout << "  [Деструктор]  Processor: " << brand << "\n";
}

void Processor::setFrequency(double f) {
    if (f <= 0.0 || f > 10.0)
        throw std::invalid_argument("Тактова частота має бути в межах 0.1..10 ГГц");
    frequency = f;
}

void Processor::print(std::ostream& out) const {
    Computer::print(out);   // спочатку виводимо дані базового класу
    std::ios_base::fmtflags fl = out.flags();
    out << "\n  Процесор: " << brand << ", " << std::fixed << std::setprecision(2)
        << frequency << " ГГц";
    out.flags(fl);
}
