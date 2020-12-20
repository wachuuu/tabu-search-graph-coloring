#include <iostream>
#include "Graf.hpp"
#include "AlgKolorowania.hpp"

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
            std::cin >> n >> proc;    // n - wierzcholki, proc - gestosc grafu

            Graf graf(n, proc);
            AlgKolorowania algorytm(graf.listy_sasiedztwa);
            //algorytm.zachlanny(0,{});
            algorytm.tabu_search();

            /*tryb debug poprzez wpisanie ',true' na koncu polecenia
                -algorytm.tabu_search(true);
                -algorytm.zachlanny(0,{},true);
                -Graf graf(n, proc, true);
                -Graf graf(plik,true);*/
                
            break;
        }
        case 2: { //odczyt z pliku
            std::string plik;
            std::cout << "Podaj nazwe pliku do odczytu: ";
            std::cin >> plik;

            Graf graf(plik);
            AlgKolorowania algorytm(graf.listy_sasiedztwa);
            //algorytm.zachlanny(0,{});
            algorytm.tabu_search();

            break;
        }
        default: {
            std::cout << "Nieprawidłowy wybór";
            exit(1);
        }
    }
}