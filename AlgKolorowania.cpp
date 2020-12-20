#include "AlgKolorowania.hpp"

AlgKolorowania::AlgKolorowania(std::vector<std::vector<int>> listy, bool debug /*=false*/) {
    for(std::vector<int>::size_type i = 0; i != listy.size(); i++) {
        listy_sasiedztwa.push_back(listy[i]);
    }
    this->n = (int)listy.size();
    if(debug) {
        for(std::vector<int>::size_type i = 0; i != listy_sasiedztwa.size(); i++) {
            std::cout << "[" << i << "]" << " ";
            for (std::vector<int>::size_type j = 0; j != listy_sasiedztwa[i].size(); j++) {
                std::cout << listy_sasiedztwa[i][j] << " ";
        }
        std::cout << std::endl;
        }
    }
}

bool AlgKolorowania::istnieje(int val1, int val2) {
    if (std::find(listy_sasiedztwa[val1].begin(), listy_sasiedztwa[val1].end(),val2)
    !=listy_sasiedztwa[val1].end()) {
        return true; }
    else return false;
}

int AlgKolorowania::zachlanny(int start_v, std::vector<int> tabu, bool debug /*=false*/) {
    //alokujemy potrzebne struktury
    bool* C  = new bool[n];  
    int i, v, max = 0;

    tab_colors.clear();
    for(i = 0; i < this->n; i++ ) {
        tab_colors.push_back({i+1,-1});
    }

    //uwzglednianie listy tabu
    for (auto v: tabu) {
        tab_colors[v][1] = 1;
    }
    //pierwszy wierzcholek start_v -> kolor 1
    tab_colors[start_v][1] = 1;     

    for(v = 0; v < n; v++ ) {
        if (tab_colors[v][1] > 0) continue;         // pomijamy kolor zadeklarowany wcześniej
        for(i = 0; i < n; i++ ) {                   // zerujemy kolory sasiadow
            C[i] = false;
        }
        for(std::vector<int>::size_type i = 0; i != listy_sasiedztwa[v].size(); i++) {      // przegladamy sasiadow
            if(tab_colors[listy_sasiedztwa[v][i]][1] > -1) {                                // jezeli sasiad ma przypisany kolor
                C[tab_colors[listy_sasiedztwa[v][i]][1]] = true;                            // kolor nr 'u' zaznaczamy jako zajęty
            }
        }
        for(i = 1; i <= n; i++) {                   // szukamy wolnego koloru
            if (C[i] == false) {
                tab_colors[v][1] = i;               // Kolorujemy wierzchołek v
                break;
            }
        }
    } 

    //wypisujemy wyniki
        if(debug) std::cout << std::endl;
        for(v = 0; v < n; v++) {
            if(debug) std::cout << v+1 << " ma kolor: " << tab_colors[v][1] << std::endl;
            if (tab_colors[v][1] > max) max=tab_colors[v][1];
        }

    std::cout <<  "Liczba kolorow: " << max << std::endl;

    delete [ ] C;
    return max;
}

int AlgKolorowania::tabu_search(bool debug /*=false*/) {
    //alokacja potrzebnych struktur
    std::vector <int> tabu_list;        // wierzcholki zapisane na sztywno z kolorem 1
    std::vector <int> candidates;       //kandydaci na nastepne wierzcholki do poprawy
    int ITER = 100;                      //liczba iteracji pętli
    int i, j;

    std::vector <int> temp;             //do sortowania
    int curr_colors, next_colors;       //najlepsza obecna l. kolorow oraz l. kolorow kandydata
    int candidate;
    bool improvement, incident;         //czy znaleziono mozliwa poprawe

    int start_col, end_col;             //kolor poczatkowego i koncowego rozw

    //generowanie początkowego rozwiązania v_0 -> 1
    curr_colors = zachlanny(0, tabu_list, debug);
    start_col = curr_colors;
    std::cout << "poczatkowe rozwiazanie " << curr_colors << std::endl;

    while (ITER > 0) { //petla przeszukiwań
        //poczatkowe wartosci zmiennych
        candidates.clear();
        improvement = false;
        incident = false;

        //sortowanie kandydatów po kolorach
        for (i = 0; i < n; i++) {
            for (j = i+1; j < n; j++) {
                if (tab_colors[i][1] > tab_colors[j][1]) {
                    temp = tab_colors[i];
                    tab_colors[i] = tab_colors[j];
                    tab_colors[j] = temp;
                }
            }
        }

        //aktualizacja stosu potencjalnych ruchów
        for (i = 0; i < n; i++) {
            candidates.push_back(tab_colors[i][0]-1);
        }
        if (debug) {
            std::cout << "kandydaci ";
            for(auto v: candidates) {
                std::cout << " " << v+1;
            }
            std::cout << std::endl;
        }

        //testowanie rozwiazan kandydatow
        while (!candidates.empty()) {
            candidate = candidates.back();
            candidates.pop_back();
            incident = false;

            //pomijamy wierzcholki incydentne z tymi w tabu lub te ktore juz sa w tabu
            //aby uniknac konfliktow
            for(auto v: tabu_list) {
                if (istnieje(v,candidate) || v == candidate) {
                    if(debug) std::cout << "konflikt " << v+1 << " " << candidate+1 << std::endl;
                    incident = true;
                    break;
                }
            }
            //pomijamy tego kandydata
            if(!incident) { 
                next_colors = zachlanny(candidate, tabu_list, debug);

                //funkcja kosztu
                if(next_colors < curr_colors) {
                    curr_colors = next_colors;
                    tabu_list.push_back(candidate);
                    if(debug) {
                        std::cout << "tabu list ";
                        for(auto v: tabu_list) {
                            std::cout << " " << v+1;
                        }
                    std::cout << std::endl;
                    }

                    improvement = true;
                    break;
                }
            }
        }

        //czy znaleziono lepsze rozwiazanie? jesli nie - otrzymalismy nasze optimum
        if (!improvement) break;

            /*
            TO DO
            V 1. posortuj wierzcholki po kolorach i zapisz je w kolejce candidates
            V 2. wybierz kandydata i pokoloruj zachlannie ustawiajac kolor kandydata na 1
            3. jezeli ilosc kolorow sie zmiejszyla zapisz kandydata z kolorem 1 w tabu_list
                - ponownie posortuj nowe pokolorowanie grafu i zaktualizuj liste kandydatow
                - w nastepnych krokach uwzgledniaj tabu_list przy kolorowaniu zachlannym
                - w nastepnych krokach przy doborze kandydata sprawdz czy nie jest incydentny z 
                  ktoryms wierzcholkiem w tabu_list, jezeli nie -> wroc do kroku 2.
            4. jezeli ilosc kolorow sie nie zmniejszyla usuwamy kandydata z kolejki i testujemy kolejnego
            5. w przypadku gdy kolejka zrobi sie pusta - nie ma wiecej mozliwosci obecne pokolorowanie jest 
            najoptymalniejsze dla tego algorytmu; zakoncz program
            */
        
        ITER--;
    }
    end_col = curr_colors;
    std::cout <<"------------------------------" << std::endl;
    std::cout << "Początkowa liczba kolorów: " << start_col << std::endl;
    std::cout << "Końcowa liczba kolorów: " << end_col << std::endl;
    std::cout <<"------------------------------" << std::endl;

    return curr_colors;
}
