#include <iostream>
#include "Graf.hpp"

int main() {
    std::cout << "Wybierz opcje wpisujac 1 lub 2:" << std::endl; 
    std::cout << "1. Wygeneruj graf" << std::endl; 
    std::cout << "2. Wczytaj graf z pliku" << std::endl; 
    std::cout << "WYBOR: ";

    int wybor;
    std::cin >> wybor;

    switch(wybor) {
        case 1: { //generowanie instancji
            int n, proc;
            std::cout << "Podaj liczbe wierzcholkow i procent zageszczenia grafu <0,100>:" << std::endl;
            std::cin >> n >> proc;            // n - wierzcholki, m - krawedzi, proc - gestosc grafu

            Graf graf(n, proc);
            graf.koloruj_graf();
            break;
        }
        case 2: { //odczyt z pliku
            std::string plik;
            std::cout << "Podaj nazwe pliku do odczytu: ";
            std::cin >> plik;

            Graf graf(plik);
            graf.koloruj_graf();
            break;
        }
        default: {
            std::cout << "Nieprawidłowy wybór";
            exit(1);
        }
    }
}