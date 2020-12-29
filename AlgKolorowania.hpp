#ifndef AlgKolorowania_hpp
#define AlgKolorowania_hpp

#include <iostream>
#include "Graf.hpp"

class AlgKolorowania {
private:
//struktura danych do przechowywania grafu
std::vector<std::vector<int>> listy_sasiedztwa;
int n;  //liczba wierzcholkow

//metody pomocnicze
bool istnieje(int val1, int val2);

/*zachlanny*/
//kolory wierzcholkow grafu
std::vector<std::vector<int>> tab_colors;
/*tabusearch*/
//lista tabu
std::vector<int> tabu_list; 

public:
//Pobranie instancji grafu
AlgKolorowania(int n, std::vector<std::vector<int>> listy, bool debug=false);
//Algorytm zachłanny
int zachlanny(int start_v, std::vector<int> tabu, bool debug=false);
//Algorytm tabu search oparty na zachlannym
int tabu_search_greedy(bool debug=false);
//Algorytm tabu search oparty na błedach
int tabu_search_random(bool debug=false);
};

#endif