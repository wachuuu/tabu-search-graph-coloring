/*tryb debug poprzez wpisanie ',true' na koncu polecenia
    -algorytm.tabu_search(true);
    -algorytm.zachlanny(0, {}, true);
    -Graf graf(n, proc, true);
    -Graf graf(plik, true);
*/

#include <iostream>
#include "Graf.hpp"
#include "AlgKolorowania.hpp"

int main() {
    int wybor_alg, wybor_debug, wybor_gen_instancji;
    bool debug = false;

    std::cout << "Wybierz opcje wpisujac 1 lub 2:" << std::endl; 
    std::cout << "1. Wygeneruj graf" << std::endl; 
    std::cout << "2. Wczytaj graf z pliku" << std::endl; 
    std::cout << "WYBOR: ";
    std::cin >> wybor_gen_instancji;
    std::cout << "Czy chcesz wlaczyc tryb debug? (domyslnie: Nie):" << std::endl; 
    std::cout << "1. Tak" << std::endl; 
    std::cout << "2. Nie" << std::endl; 
    std::cout << "WYBOR: ";
    std::cin >> wybor_debug;
    if(wybor_debug == 1) {debug = true;}

    switch(wybor_gen_instancji) {
        case 1: { //generowanie instancji
            int n, proc;
            std::cout << "Podaj liczbe wierzcholkow i procent zageszczenia grafu <0,100>:" << std::endl;
            std::cin >> n >> proc;    // n - wierzcholki, proc - gestosc grafu

            Graf graf(n, proc);
            AlgKolorowania algorytm(graf.n, graf.listy_sasiedztwa);

            std::cout << "Wybierz algorytm kolorujacy:" << std::endl; 
            std::cout << "1. Tabu search" << std::endl; 
            std::cout << "2. Algorytm zachlanny" << std::endl; 
            std::cout << "3. Algorytm hybrydowy (Tabu + zachlanny)" << std::endl; 
            std::cout << "WYBOR: ";
            std::cin >> wybor_alg;

            switch(wybor_alg) {
                case 1: {
                    algorytm.tabu_search_random(debug);
                    break;
                }
                case 2: {
                    algorytm.zachlanny(0,{},debug);
                    break;
                }
                case 3: {
                    algorytm.tabu_search_greedy(debug);
                    break;
                }
                default: {
                    std::cout << "Nieprawidlowy wybor";
                    exit(1);
                }
            }
            break;
        }
        case 2: { //odczyt z pliku
            std::string plik;
            std::cout << "Podaj nazwe pliku do odczytu: ";
            std::cin >> plik;

            Graf graf(plik);
            AlgKolorowania algorytm(graf.n, graf.listy_sasiedztwa);

            std::cout << "Wybierz algorytm kolorujacy:" << std::endl; 
            std::cout << "1. Tabu search" << std::endl; 
            std::cout << "2. Algorytm zachlanny" << std::endl; 
            std::cout << "3. Algorytm hybrydowy (Tabu + zachlanny)" << std::endl; 
            std::cout << "WYBOR: ";
            std::cin >> wybor_alg;

            switch(wybor_alg) {
                case 1: {
                    algorytm.tabu_search_random(debug);
                    break;
                }
                case 2: {
                    algorytm.zachlanny(0,{},debug);
                    break;
                }
                case 3: {
                    algorytm.tabu_search_greedy(debug);
                    break;
                }
                default: {
                    std::cout << "Nieprawidlowy wybor";
                    exit(1);
                }
            }
            break;
        }
        default: {
            std::cout << "Nieprawidlowy wybor";
            exit(1);
        }
    }
}