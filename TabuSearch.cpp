#include "TabuSearch.hpp"

TabuSearch::TabuSearch( Graf & graf) {
    // //alokacja potrzebnych struktur
    // //lista tabu -- pole klasy jako wektor
    // std::vector <int> candidates;       //kandydaci na nastepne wierzcholki do poprawy
    // this->tab_colors = graf.tab_colors; //przekopiowanie wyniku alg zachlannego
    // int ITER = 1;                      //liczba iteracji pętli
    // int* temp;

    // // int** tab_colors = new int*[12];
    // // for(int i=0; i<12; i++) {
    // //     tab_colors[i] = new int[2];
    // //     //tab_colors[i][0] = i+1;
    // //     tab_colors[i] = graf.tab_colors[i];
    // // }

    // /*
    // - przydaloby sie zamienic tab_colors na tablice dwuwymiarowa
    //   klucz = nr wierzcholka, wartosc = kolor
    // - algorytm kolorowania grafu przeniósłbym do klasy TabuSearch
    // - zmienilbym tablice tab_colors na kolekcje klucz-wartosc i zrobil ją jako 
    // pole tej klasy
    // */


    // //generowanie początkowego rozwiązania v_0 -> 1
    // this->color_count = graf.koloruj_graf(0);
    // std::cout << "poczatkowe rozwiazanie " << this->color_count << std::endl;

    // while (ITER > 0) { //petla przeszukiwań
    //     //sortowanie kandydatów po kolorach
    //     // for (int i=0; i<graf.n; i++) {
    //     //     for (int j=i+1; j<graf.n; j++) {
    //     //         if (tab_colors[i][1] > tab_colors[j][1]) {
    //     //             temp = tab_colors[i];
    //     //             tab_colors[i] = tab_colors[j];
    //     //             tab_colors[j] = temp;
    //     //         }
    //     //     }
    //     // }
    //     // for (int i=0; i<graf.n; i++) {
    //     //     std::cout << "wierzhch " << graf.tab_colors[i][0] << " kolor " << graf.tab_colors[i][1] <<std::endl;
    //     // }

    //         /*
    //         TO DO
    //         1. posortuj wierzcholki po kolorach i zapisz je w kolejce candidates
    //         2. wybierz kandydata i pokoloruj zachlannie ustawiajac kolor kandydata na 1
    //         3. jezeli ilosc kolorow sie zmiejszyla zapisz kandydata z kolorem 1 w tabu_list
    //             - ponownie posortuj nowe pokolorowanie grafu i zaktualizuj liste kandydatow
    //             - w nastepnych krokach uwzgledniaj tabu_list przy kolorowaniu zachlannym
    //             - w nastepnych krokach przy doborze kandydata sprawdz czy nie jest incydentny z 
    //               ktoryms wierzcholkiem w tabu_list, jezeli nie -> wroc do kroku 2.
    //         4. jezeli ilosc kolorow sie nie zmniejszyla usuwamy kandydata z kolejki i testujemy kolejnego
    //         5. w przypadku gdy kolejka zrobi sie pusta - nie ma wiecej mozliwosci obecne pokolorowanie jest 
    //         najoptymalniejsze dla tego algorytmu; zakoncz program
    //         */
        
    //     ITER--;
    // }

}