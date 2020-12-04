#include "Graf.hpp"

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
    odczyt >> n >> m;

    //tworzenie struktury danych
    listy_sasiedztwa = new lista* [n]; // tworzymy liste list

    for(int i=0; i<n; i++ ) {          // ustawiamy poczatkowy stan tablicy
        listy_sasiedztwa[i] = NULL;
    }

    for (int i = 0; i < m; i++)
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
zapis << n << " " << m << std::endl;
for(int i=0; i<n; i++ ) {
    for( p = listy_sasiedztwa[i]; p; p = p->next ) {
        if (i < p->value) {
            zapis << i+1 << " " << p->value+1 << std::endl;
        }
    }
}
zapis.close();
}

void Graf::koloruj_graf(int start_v) {
    //alokujemy potrzebne struktury
    lista* p;
    int* tab_colors = new int[n]; 
    bool* C  = new bool[n];  
    int max = 0;

    for(int i=1; i<this->n; i++ ) {
      tab_colors[i] = -1;                               // -1 == brak koloru
    }

    tab_colors[start_v] = 1;                            // pierwszy wierzcholek 0 -> kolor 1
    for(int v=0; v<n; v++ ) {
        if (v>0) continue;                              // pomijamy kolor zadeklarowany wcześniej
        for(int i = 0; i < n; i++ ) {                   // zerujemy kolory sasiadow
            C[i] = false;
        }
        for( p=listy_sasiedztwa[v]; p; p=p->next ) {    // przegladamy sasiadow
            if( tab_colors[p->value] > -1 ) {           // jezeli sasiad ma przypisany kolor
                C[tab_colors[p->value]] = true;         // kolor nr 'u' zaznaczamy jako zajęty
            }
        }
        for(int i = 1; i<=n; i++ ) {                    // szukamy wolnego koloru
            if (C[i] == false) {
                tab_colors[v] = i;                      // Kolorujemy wierzchołek v
                break;
            }
        }
    } 

    //wypisujemy wyniki
    std::cout << std::endl;
    for(int v = 0; v < n; v++ ) {
        std::cout << v+1 << " ma kolor: " << tab_colors[v] << std::endl;
        if (tab_colors[v] > max) max=tab_colors[v];
    }

    std::cout << std::endl;
    std::cout << "Liczba kolorow: " << max << std::endl;

    delete [ ] tab_colors;
    delete [ ] C;
}