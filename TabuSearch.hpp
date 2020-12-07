#ifndef TabuSearch_hpp
#define TabuSearch_hpp

#include <iostream>
#include "Graf.hpp"

class TabuSearch{
private:
int *tabu_list;         //lista tabu
int **tab_colors;        //wynikowa lista kolorów (zrobilbym kolekcje)
int color_count;        //na ile kolorow pokolorowalismy graf

public:
//wlasciwy algorytm Tabu Search
TabuSearch(Graf & graf);
};

#endif