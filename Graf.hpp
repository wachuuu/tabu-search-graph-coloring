#ifndef Graf_hpp
#define Graf_hpp

#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <Windows.h>
#include <vector>
#include <set>
#include <algorithm>


class Graf {
private:
int m;      //liczba krawedzi
int proc;   //procent zageszczenia grafu
bool *visited = NULL;

//operacje na listach sasiedztwa
void dodaj(int val1, int val2);
bool istnieje(int val1, int val2);
void DFS(int v);
void sprawdz_spojnosc(bool debug=false);
void zapisz_instancje(std::string plik);

public:
//struktura danych do przechowywania grafu
std::vector<std::vector<int>> listy_sasiedztwa;
int n;      //liczba wierzcholkow

//konstruktor generujacy instancje
Graf(int n, int proc, bool debug=false);
//konstruktor wczytujacy instancje
Graf(std::string plik, bool debug=false);
~Graf();

};
#endif