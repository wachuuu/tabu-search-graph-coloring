#include "Graf.hpp"

Graf::Graf(){}

Graf::Graf(int n, int proc) {
    srand(time(NULL));

    int val1, val2;
    this->n = n;
    this->m = (n*(n-1)/2)*proc/100; 

    this->listy_sasiedztwa = new lista * [n];
    this->visited = new bool[n]; 

    // ustawiamy poczatkowy stan tablic
    for(int i=0; i<n; i++ ) {           
        listy_sasiedztwa[i] = NULL;
        visited[i] = false;
    }

    for (int i = 0; i < m; i++)
    {
        do
        {
            val1 = (int)rand() % n;
            val2 = (int)rand() % n;
        // eliminacja petli wlasnych i powtarzajacych sie wierzcholkow
        } while (val1 == val2 || istnieje(val1, val2)); 
        
        std::cout << val1+1 << " " << val2+1 << std::endl;
        dodaj(val1, val2);
    }
    sprawdz_spojnosc();
    std::cout << "Liczba krawedzi: " << this->m << std::endl;
    zapisz_instancje("instancja.txt");

}

Graf::Graf(std::string plik) {
    std::ifstream odczyt;
    int val1, val2; //krawedzie grafu
    odczyt.open(plik);
    odczyt >> n;

    //tworzenie struktury danych
    listy_sasiedztwa = new lista* [n]; // tworzymy liste list

    for(int i=0; i<n; i++ ) {          // ustawiamy poczatkowy stan tablicy
        listy_sasiedztwa[i] = NULL;
    }

    while (!odczyt.eof())
    {
        odczyt >> val1 >> val2;
        //std::cout << val1 << " " << val2 << std::endl;
        dodaj(val1-1, val2-1);
    }

    odczyt.close();
}

Graf::~Graf() {
    lista* p, *r;   //wskazniki pomocnicze
    //usuwanie podlist

    //dodac usuwanie tab_colors
    for(int i = 0; i < n; i++ ) {
        p = listy_sasiedztwa [i];
        while(p) {
            r = p;
            p = p->next;
            delete r;
        }
    }
    delete [] listy_sasiedztwa;
    if(visited != NULL) delete [] visited;
}

void Graf::dodaj(int val1, int val2) {
    lista* p;       //wskaznik na nowy element
    p = new lista;
    p->value = val2;
    p->next = listy_sasiedztwa[val1];
    listy_sasiedztwa[val1] = p;
    p = new lista;
    p->value = val1;
    p->next =listy_sasiedztwa[val2];
    listy_sasiedztwa[val2] = p;
}

bool Graf::istnieje(int val1, int val2) {
    lista* p;
    p = listy_sasiedztwa[val1];
    for(p = listy_sasiedztwa[val1]; p; p = p->next) {
          if (p->value == val2) return true;    
    }
    return false;
}

lista* Graf::sortuj_pom(lista* a, lista* b) {
    lista* wynik = NULL; 
    if (a == NULL) return (b); 
    else if (b == NULL) return (a); 
    if (a->value <= b->value) { 
        wynik = a; 
        wynik->next = sortuj_pom(a->next, b); 
    } 
    else { 
        wynik = b; 
        wynik->next = sortuj_pom(a, b->next); 
    } 
    return (wynik); 
}

void Graf::sortuj(lista** li) {
    lista* head = *li; 
    lista* a; 
    lista* b; 
    if ((head == NULL) || (head->next == NULL)) return;
    lista* li1; 
    lista* li2; 
    li1 = head; 
    li2 = head->next; 
    while (li2 != NULL) { 
        li2 = li2->next; 
        if (li2 != NULL) { 
            li2 = li2->next; 
            li1 = li1->next; 
        } 
    } 
    a = head; 
    b = li1->next; 
    li1->next = NULL; 
    sortuj(&a); 
    sortuj(&b); 
    *li = sortuj_pom(a, b); 
}

void Graf::DFS(int v) {
    lista *p;
    visited[v] = true;
    p = listy_sasiedztwa[v]; // ustawiamy wskaznik
    for( p = listy_sasiedztwa[v]; p; p = p->next ) {
        if (!visited[p->value]) {
            DFS(p->value);
        }
    }
}

void Graf::sprawdz_spojnosc() {
    DFS(0);
    for (int j = 0; j < this->n; j++) {
        if (!visited[j]) {
            if (j != 0) {
                dodaj(j - 1, j);
                std::cout << j << " " << j+1 << std::endl;
                //zwiekszmy ilosc krawedzi w naszym grafie
                this->m++;
            }
            else {
                dodaj(0, 1);
                std::cout << 0 << " " << 1 << std::endl;
                this->m++;
            }
            //sprawdzamy czy teraz graf jest spojny
            for (int i = 0; i < n; i++) visited[i] = false;
            DFS(0);
        }
    }
}

void Graf::zapisz_instancje(std::string plik) {
std::ofstream zapis;
lista *sorted;      // glowa listy i wejscoiwej i posortowanej
lista *p;           // iterator petli

zapis.open("instancja.txt");
// sortowanie 
for(int i=0; i<n; i++ ) {
   sortuj(&listy_sasiedztwa[i]);
}
// wpisywanie
zapis << n << std::endl;
for(int i=0; i<n; i++ ) {
    for( p = listy_sasiedztwa[i]; p; p = p->next ) {
        if (i < p->value) {
            zapis << i+1 << " " << p->value+1 << std::endl;
        }
    }
}
zapis.close();
}

int Graf::koloruj_graf(int start_v, std::vector<int> tabu) {
    //alokujemy potrzebne struktury
    lista* p;
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
    tab_colors[start_v][1] = 1;     //pierwszy wierzcholek start_v -> kolor 1

    for(v = 0; v < n; v++ ) {
        if (tab_colors[v][1] > 0) continue;                              // pomijamy kolor zadeklarowany wcześniej
        for(i = 0; i < n; i++ ) {                   // zerujemy kolory sasiadow
            C[i] = false;
        }
        for(p = listy_sasiedztwa[v]; p; p = p->next) {    // przegladamy sasiadow
            if(tab_colors[p->value][1] > -1) {           // jezeli sasiad ma przypisany kolor
                C[tab_colors[p->value][1]] = true;         // kolor nr 'u' zaznaczamy jako zajęty
            }
        }
        for(i = 1; i <= n; i++) {                    // szukamy wolnego koloru
            if (C[i] == false) {
                tab_colors[v][1] = i;                      // Kolorujemy wierzchołek v
                break;
            }
        }
    } 

    //wypisujemy wyniki
    std::cout << std::endl;
    for(v = 0; v < n; v++) {
        std::cout << v+1 << " ma kolor: " << tab_colors[v][1] << std::endl;
        if (tab_colors[v][1] > max) max=tab_colors[v][1];
    }
    std::cout << std::endl << "Liczba kolorow: " << max << std::endl;

    delete [ ] C;
    return max;
}

int Graf::tabu_search() {
    //alokacja potrzebnych struktur
    std::vector <int> tabu_list;        // wierzcholki zapisane na sztywno z kolorem 1
    std::vector <int> candidates;       //kandydaci na nastepne wierzcholki do poprawy
    int ITER = 100;                      //liczba iteracji pętli
    int i, j;

    std::vector <int> temp;             //do sortowania
    int curr_colors, next_colors;       //najlepsza obecna l. kolorow oraz l. kolorow kandydata
    int candidate;
    bool improvement, incident;         //czy znaleziono mozliwa poprawe
    /*
    - przydaloby sie zamienic tab_colors na tablice dwuwymiarowa
      klucz = nr wierzcholka, wartosc = kolor
    - algorytm kolorowania grafu przeniósłbym do klasy TabuSearch
    - zmienilbym tablice tab_colors na kolekcje klucz-wartosc i zrobil ją jako 
    pole tej klasy
    */

    //generowanie początkowego rozwiązania v_0 -> 1
    curr_colors = koloruj_graf(0, tabu_list);
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
        std::cout << "kandydaci ";
        for(auto v: candidates) {
            std::cout << " " << v+1;
        }
        std::cout << std::endl;

        //testowanie rozwiazan kandydatow
        while (!candidates.empty()) {
            candidate = candidates.back();
            candidates.pop_back();
            incident = false;

            //pomijamy wierzcholki incydentne z tymi w tabu lub te ktore juz sa w tabu
            //aby uniknac konfliktow
            for(auto v: tabu_list) {
                if (istnieje(v,candidate) || v == candidate) {
                    std::cout << "konflikt " << v+1 << " " << candidate+1 << std::endl;
                    incident = true;
                    break;
                }
            }
            //pomijamy tego kandydata
            if(!incident) { 
                next_colors = koloruj_graf(candidate, tabu_list);

                //funkcja kosztu
                if(next_colors < curr_colors) {
                    curr_colors = next_colors;
                    tabu_list.push_back(candidate);
                    std::cout << "tabu list ";
                    for(auto v: tabu_list) {
                        std::cout << " " << v+1;
                    }
                    std::cout << std::endl;
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
    return curr_colors;
}