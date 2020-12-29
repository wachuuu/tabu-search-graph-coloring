#include "AlgKolorowania.hpp"

AlgKolorowania::AlgKolorowania(int n, std::vector<std::vector<int>> listy, bool debug /*=false*/) {
    for(std::vector<int>::size_type i = 0; i != listy.size(); i++) {
        listy_sasiedztwa.push_back(listy[i]);
    }
    this->n = n;
    if(debug) {
        std::cout << "n = " << n << std::endl;
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

int AlgKolorowania::tabu_search_greedy(bool debug /*=false*/) {
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

int AlgKolorowania::tabu_search_random(bool debug /*=false*/) {
    srand(time(NULL));
    int ITER = 7000;              //liczba iteracji algorytmu
    int tabu_length = 15;       //dlugosc listy tabu
    int reps = 500;              //dlugosc listy sasiednich rozwiazan
    int max_colors = 7;         //gorna granica kolorowania

    int conflicts, new_conflicts; //liczba konfliktow
    int candidate; //wybrany kandydat

    std::vector <int> tabu_list;        //lista tabu
    std::set <int> candidates_set;      //kandydaci bez powtorzen
    std::vector <int> candidates;       //kandydaci
    std::vector <int> tab_colors;       //obecne pokolorowanie grafu
    std::vector <int> cand_tab_colors;  //rozwiazanie sasiada

    /* generowanie rozw poczatkowego */
    for (int i=0; i<n; i++) tab_colors.push_back(rand()%(max_colors));
    if(debug) {
        std::cout << "Poczatkowe pokolorowanie:";
        for (int i=0; i<n; i++) std::cout << " " << tab_colors[i];
        std::cout << std::endl;
    }
    /* petla przeszukiwan */
    while(ITER > 0){
        candidates_set.clear();
        conflicts = 0;

        /*liczba konfliktow*/
        for(int i=0; i<n; i++) {
            for(auto v: listy_sasiedztwa[i]) {
                if(tab_colors[i] == tab_colors[v]) {
                    candidates_set.insert(v);
                    conflicts++;
                    if(debug) std::cout << "konflikt: " << i << " " << v << " - kolor " << tab_colors[i] << std::endl;
                }
            }
        }
        std::cout << "liczba konfliktow: " << conflicts << std::endl;
        if(debug) {
            std::cout << "kandydaci";
            for(auto x: candidates_set) std::cout << " " << x;
            std::cout << std::endl;
        }
        /*konwersja zbioru do wektora w celu indeksowania*/
        candidates.clear();
        std::copy(candidates_set.begin(), candidates_set.end(), std::back_inserter(candidates));

        if (conflicts == 0) break;  //rozw bezkonfliktowe pokolorowalismy na k kolorow

        /*generujemy x rozwiazan sasiadow*/
        for(int i=0; i < candidates.size(); i++) {
            //wybieramy losowo kandydata i zmieniamy mu kolor
            candidate = candidates[rand()%candidates.size()];
            cand_tab_colors.clear();
            cand_tab_colors = tab_colors;
            cand_tab_colors[candidate] = rand()%(max_colors-1);
            //jezeli wybralismy taki sam kolor <0, k-1> to obieramy k-ty kolor
            if (cand_tab_colors[candidate] == tab_colors[candidate]) cand_tab_colors[candidate] = max_colors;
            
            if(debug) std::cout << "kandydat " << candidate << " - zmiana koloru " << tab_colors[candidate]
                << " -> " << cand_tab_colors[candidate] << std::endl;

            /*sprawdzamy wygenerowane rozwiazanie sasiada*/
            new_conflicts = 0;
            for(int i=0; i<n; i++) {
                for(auto v: listy_sasiedztwa[i]) {
                    if(cand_tab_colors[i] == cand_tab_colors[v]) new_conflicts++;
                }
            }
            if(debug) std::cout << "liczba konfliktow sasiada: " << new_conflicts << std::endl;            
            
            if(new_conflicts < conflicts) { //znaleziono lepsze rozwiazanie
                bool in_tabu = false;
                //tu dodaj poziom aspiracji
                /*jezeli dany wierzcholek jest w tabu nie ruszamy go*/
                for(auto x: tabu_list) if(x==candidate) in_tabu = true;
                //jezeli kandydat w tabu szukaj nastepnego rozw w prz. przyp. zakoncz przeszukiwanie
                if(in_tabu) {
                    if(debug) std::cout << "niedozwolone, wierzcholek w tabu" << std::endl;
                    continue;
                }
                else {
                    if(debug) {
                    std::cout << "nowe rozwiazanie ";
                    for(auto x: cand_tab_colors) std::cout << " " << x;
                    std::cout << std::endl;
                    }
                    break;
                }
            }
        }
        /*do tego momentu albo znaleziono lepsze rozwiazanie albo skonczyli sie kandydaci*/

        tabu_list.push_back(candidate);
        //jezeli tabu list jest przepelniona zrob miejsce usuwajac pierwszy element
        if(tabu_list.size() > tabu_length) tabu_list.erase(tabu_list.begin());
        if(debug) {
            std::cout << "tabu list: ";
            for(auto x: tabu_list) std::cout << " " << x;
            std::cout << std::endl;
        }
        tab_colors = cand_tab_colors;
    ITER--;
    }
    std::cout << "ROZW KONCOWE" << std::endl;
    std::cout << std::endl;
    for (int i=0; i<n; i++) std::cout << " " << tab_colors[i];
    std::cout << std::endl;
    for(int i=0; i<n; i++) {
    for(auto v: listy_sasiedztwa[i]) {
        if(tab_colors[i] == tab_colors[v]) {
            std::cout << "konflikt: " << i << " " << v << " - kolor " << tab_colors[i] << std::endl;
        }
    }
}

    return 0;
}

/* 
TO DO LIST
-sprawdzanie czy cos isnieje w tabu list, eliminacja powtorzen po wyczerpaniu reps
-wyeliminowac
    konflikt: 4 7 - kolor 1
    konflikt: 7 4 - kolor 1

*/