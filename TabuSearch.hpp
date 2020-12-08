#ifndef TabuSearch_hpp
#define TabuSearch_hpp

#include <iostream>
#include <algorithm>
#include "Graf.hpp"

class TabuSearch{
private:
std::vector<int> tabu_list; //lista tabu
int **tab_colors;           //wynikowa lista kolorów
int color_count;            //na ile kolorow pokolorowalismy graf

public:
//wlasciwy algorytm Tabu Search
TabuSearch(Graf & graf);
};

#endif