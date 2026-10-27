#include "HardDisk.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    const string FILE_NAME = "computers.txt";

    cout << "=== 1. Порядок виклику конструкторів і деструкторів ===\n";
    Computer::verbose = true;
    {
        cout << "Створюємо об'єкт HardDisk:\n";
        HardDisk hd("Acer Aspire", 24300.00, "Intel Core i3-1115G4", 3.0, 512);
        cout << "Об'єкт створено, виходимо з блоку:\n";
    }
    Computer::verbose = false;

    cout << "\n=== 2. Комплект 1: виведення на екран ===\n";
    Computer  c1("Dell XPS 15", 42500.00);
    Processor p1("Lenovo ThinkPad", 31900.00, "Intel Core i5-1235U", 3.30);
    HardDisk  h1("ASUS ROG", 58700.00, "AMD Ryzen 7 7700X", 4.50, 1000);
    cout << c1 << endl << p1 << endl << h1 << endl;

    cout << "\n=== 3. Успадковані методи ===\n";
    cout << "h1.getModel()     = " << h1.getModel() << endl;
    cout << "h1.getBrand()     = " << h1.getBrand() << endl;
    cout << "h1.getFrequency() = " << h1.getFrequency() << " ГГц" << endl;
    cout << "h1.getCapacity()  = " << h1.getCapacity() << " Гбайт" << endl;
    h1.setPrice(h1.getPrice() * 0.9);
    cout << fixed << setprecision(2)
        << "Ціна h1 після знижки 10%: " << h1.getPrice() << " грн" << endl;
    cout << defaultfloat;

    cout << "\n=== 4. Доступ через вказівник на базовий клас ===\n";
    vector<Computer*> list;
    list.push_back(new Computer("HP Pavilion", 27800.00));
    list.push_back(new Processor("MSI Modern", 33400.00, "AMD Ryzen 5 5600H", 3.30));
    list.push_back(new HardDisk("Apple MacBook Air", 52900.00, "Apple M2", 3.49, 256));
    for (const Computer* c : list) cout << *c << endl;
    for (Computer* c : list) delete c;   // віртуальний деструктор

    cout << "\n=== 5. Запис у файл " << FILE_NAME << " ===\n";
    // Комплект 1: режим ios::out | ios::trunc (файл створюється заново)
    bool ok = c1.saveToFile(FILE_NAME);
    // Комплект 2 дописується в кінець файлу: режим ios::app
    HardDisk h2("Gigabyte Aero", 61200.00, "Intel Core i7-12700H", 4.70, 2000);
    Processor p2("Acer Nitro", 36900.00, "AMD Ryzen 5 6600H", 3.30);
    ok = p1.saveToFile(FILE_NAME, ios::out | ios::app) && ok;
    ok = h1.saveToFile(FILE_NAME, ios::out | ios::app) && ok;
    ok = p2.saveToFile(FILE_NAME, ios::out | ios::app) && ok;
    ok = h2.saveToFile(FILE_NAME, ios::out | ios::app) && ok;
    cout << (ok ? "Дані успішно записано у файл\n" : "Помилка запису у файл\n");

    cout << "\n=== 6. Читання з файлу ===\n";
    ifstream in(FILE_NAME.c_str());
    if (!in.is_open()) {
        cout << "Не вдалося відкрити файл\n";
    }
    else {
        string line;
        int n = 0;
        while (getline(in, line)) {
            ++n;
            cout << line << "\n";
        }
        cout << "Прочитано рядків: " << n << endl;
        in.clear();                 // скидаємо ознаку кінця файлу
        in.seekg(0, ios::end);      // довільний доступ: перехід у кінець
        cout << "Розмір файлу: " << in.tellg() << " байт" << endl;
        in.close();
    }

    cout << "\n=== 7. Рядкові потоки ===\n";
    string text = h2.toString();
    istringstream iss(text);
    string firstLine;
    getline(iss, firstLine);
    int lines = 1;
    string tmp;
    while (getline(iss, tmp)) ++lines;
    cout << "Рядок із ostringstream містить " << lines << " рядки\n";
    cout << "Перший рядок: " << firstLine << endl;

    cout << "\n=== 8. Виняткові ситуації ===\n";
    try { Computer bad("Lenovo", -100.0); }
    catch (const invalid_argument& e) { cout << "[invalid_argument] " << e.what() << endl; }

    Computer::verbose = true;
    try {
        cout << "Створюємо HardDisk з обсягом 0:\n";
        HardDisk bad("Dell", 20000.0, "Intel Core i3", 3.0, 0);
    }
    catch (const invalid_argument& e) { cout << "[invalid_argument] " << e.what() << endl; }
    Computer::verbose = false;

    ifstream missing("no_such_file.txt");
    if (!missing.is_open()) cout << "Файл no_such_file.txt відкрити неможливо\n";

    cout << "\n=== Завершення програми (знищення об'єктів) ===\n";
    return 0;
}
