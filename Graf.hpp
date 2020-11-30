#ifndef Graf_hpp
#define Graf_hpp

#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <Windows.h>


//struktura listy jednokierunkowej
struct lista {
    lista* next;
    int value;
};

class Graf {
private:
bool *visited = NULL;
int n;      //liczba wierzcholkow
int m;      //liczba krawedzi
int proc;   //procent zageszczenia grafu
lista **listy_sasiedztwa;

//dodaj wierzcholek
void dodaj(int val1, int val2);
//sprawdz czy istnieje krawedz
bool istnieje(int val1, int val2);
//sortowanie
lista* sortuj_pom(lista* a, lista* b);
void sortuj(lista** li);
//DFS
void DFS(int v);
//sprawdzanie spojnosci grafu
void sprawdz_spojnosc();
//zapisywanie instancji do pliku
void zapisz_instancje(std::string plik);

public:
//konstruktor generujacy instancje
Graf(int n, int proc);
//konstruktor wczytujacy instancje
Graf(std::string plik);
~Graf();

//algorytm zachlanny kolorowanie grafu
void koloruj_graf();
};
#endif