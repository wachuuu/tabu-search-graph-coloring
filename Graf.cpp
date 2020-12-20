#include "Graf.hpp"

Graf::Graf(int n, int proc, bool debug /*=false*/) {
    srand(time(NULL));

    int val1, val2;
    this->n = n;
    this->m = (n*(n-1)/2)*proc/100; 

    // alokujemy miejsca na listy danych krawedzi
    for(int i=0; i<n; i++ ) {
        listy_sasiedztwa.push_back({});
    }

    for (int i = 0; i < m; i++)
    {
        do
        {
            val1 = (int)rand() % n;
            val2 = (int)rand() % n;
        // eliminacja petli wlasnych i powtarzajacych sie wierzcholkow
        } while (val1 == val2 || istnieje(val1, val2)); 

        dodaj(val1, val2);
        if(debug) std::cout << val1+1 << " " << val2+1 << std::endl;
    }
    sprawdz_spojnosc(debug);
    if(debug) std::cout << "Liczba krawedzi: " << this->m << std::endl;
    zapisz_instancje("instancja.txt");

}

Graf::Graf(std::string plik, bool debug /*=false*/) {
    std::ifstream odczyt;
    int val1, val2;
    odczyt.open(plik);
    odczyt >> n;

    //tworzenie struktury danych
    for(int i=0; i<n; i++ ) {
        listy_sasiedztwa.push_back({});
    }

    while (!odczyt.eof())
    {
        odczyt >> val1 >> val2;
        if(debug) std::cout << val1 << " " << val2 << std::endl;
        dodaj(val1-1, val2-1);
    }
    odczyt.close();
}

Graf::~Graf() {
    if(visited != NULL) delete [] visited;
}

void Graf::dodaj(int val1, int val2) {
    listy_sasiedztwa[val1].push_back(val2);
    listy_sasiedztwa[val2].push_back(val1);
}

bool Graf::istnieje(int val1, int val2) {
    if (std::find(listy_sasiedztwa[val1].begin(), listy_sasiedztwa[val1].end(),val2)
        !=listy_sasiedztwa[val1].end()) { return true; }
    else return false;
}

void Graf::DFS(int v) {
    visited[v] = true;
    for(std::vector<int>::size_type i = 0; i != listy_sasiedztwa[v].size(); i++) {
        if (!visited[listy_sasiedztwa[v][i]]) {
            DFS(listy_sasiedztwa[v][i]);
        }
    }
}

void Graf::sprawdz_spojnosc(bool debug /*=false*/) {
    // ustawiamy poczatkowy stan tablicy visited
    this->visited = new bool[n];
    for(int i=0; i<n; i++ ) {
        visited[i] = false;
    }

    DFS(0);
    for (int j = 0; j < this->n; j++) {
        if (!visited[j]) {
            if (j != 0) {
                dodaj(j - 1, j);
                if(debug) std::cout << "Dodano krawedz " << j << " " << j+1 << std::endl;
                //zwiekszmy ilosc krawedzi w naszym grafie
                this->m++;
            }
            else {
                dodaj(0, 1);
                if(debug) std::cout << "Dodano krawedz " << 0 << " " << 1 << std::endl;
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
    zapis.open("instancja.txt");
    // sortowanie 
    for(int i=0; i<n; i++) {
       std::sort(listy_sasiedztwa[i].begin(), listy_sasiedztwa[i].end());
    }
    // wpisywanie
    zapis << n << std::endl;
    for(int i=0; i<n; i++ ) {
        for(std::vector<int>::size_type j = 0; j != listy_sasiedztwa[i].size(); j++) {
            if (i < listy_sasiedztwa[i][j]) {
                zapis << i+1 << " " << listy_sasiedztwa[i][j]+1 << std::endl;
            }
        }
    }
    zapis.close();
}