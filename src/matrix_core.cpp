#include "../include/matrix.h"
#include <iostream>
#include <algorithm> // std::copy

// --- Metody Pomocnicze (Private) ---

int& matrix::at(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        throw std::out_of_range("Blad: Indeks macierzy poza zakresem!");
    }
    // Mapowanie 2D -> 1D
    return data[y * n + x];
}

int matrix::at(int x, int y) const {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        throw std::out_of_range("Blad: Indeks macierzy poza zakresem!");
    }
    return data[y * n + x];
}

// --- Konstruktory i Destruktor ---

matrix::matrix() : n(0), data(nullptr) {
    // Pusta macierz
}

matrix::matrix(int n) : n(0), data(nullptr) {
    // Wywolujemy alokuj, ktora ustawi n i przydzieli pamiec
    alokuj(n);
}

matrix::matrix(int n, int* t) : n(0), data(nullptr) {
    alokuj(n);
    // Przepisujemy dane z tablicy t do naszej pamieci
    // UWAGA: Zakladamy, ze t ma rozmiar co najmniej n*n
    if (t != nullptr) {
        for (int i = 0; i < n * n; ++i) {
            data[i] = t[i];
        }
    }
}

// Konstruktor kopiujacy - BARDZO WAZNY
// unique_ptr nie mozna skopiowac (jest unikalny), wiec musimy
// utworzyc nowa pamiec i skopiowac wartosci recznie (Gleboka Kopia).
matrix::matrix(const matrix& m) : n(0), data(nullptr) {
    alokuj(m.n);
    if (m.data) {
        std::copy(m.data.get(), m.data.get() + (n * n), data.get());
    }
}

matrix::~matrix() {
    // unique_ptr sam zwolni pamiec, ale warto o tym wiedziec.
    // Mozna tu dodac logowanie dla celow edukacyjnych, np.:
    // std::cout << "Destruktor macierzy rozmiaru " << n << std::endl;
}

// --- Zarzadzanie Pamiecia ---

matrix& matrix::alokuj(int nowe_n) {
    if (nowe_n < 0) {
        throw std::invalid_argument("Rozmiar macierzy nie moze byc ujemny");
    }

    // Obliczamy calkowita ilosc elementow
    int stary_rozmiar = n * n;
    int nowy_rozmiar = nowe_n * nowe_n;

    // Logika zgodna z trescia zadania:
    if (data == nullptr) {
        // 1. Nie ma pamieci -> alokujemy
        n = nowe_n;
        data = std::make_unique<int[]>(nowy_rozmiar);
    } 
    else {
        // 2. Pamiec juz jest. Sprawdzamy rozmiar.
        if (nowy_rozmiar == stary_rozmiar) {
            // Rozmiar ten sam -> nic nie robimy (ewentualnie mozna wyzerowac)
        } 
        else if (stary_rozmiar < nowy_rozmiar) {
            // 3. Pamieci jest mniej niz potrzeba -> realokacja
            // unique_ptr automatycznie usunie stary wskaznik przy przypisaniu nowego
            n = nowe_n;
            data = std::make_unique<int[]>(nowy_rozmiar);
        } 
        else {
            // 4. Pamieci jest wiecej niz potrzeba -> pozostawic bez zmian (wg zadania)
            // Zmieniamy tylko wymiar n, ale fizycznie w pamieci wciaz jest wiecej miejsca.
            // Jest to optymalizacja, zeby nie alokowac w kolko mniejszych buforow.
            n = nowe_n;
        }
    }

    // Inicjalizacja zerami dla bezpieczenstwa (opcjonalne, ale zalecane)
    // make_unique<int[]> domyslnie inicjalizuje zerami, wiec jest ok.
    
    return *this;
}

// --- Dostep do Danych ---

matrix& matrix::wstaw(int x, int y, int wartosc) {
    // Metoda at() zalatwia sprawdzanie zakresow
    at(x, y) = wartosc;
    return *this;
}

int matrix::pokaz(int x, int y) const {
    return at(x, y);
}

// Operator przypisania (A = B)
matrix& matrix::operator=(const matrix& m) {
    // 1. Sprawdzenie autozapisu (A = A) - zebysmy nie usuneli sami siebie
    if (this == &m) {
        return *this;
    }

    // 2. Alokacja nowej pamieci (lub wykorzystanie istniejacej)
    // Metoda alokuj() sama sprawdzi, czy rozmiar sie zmienil
    alokuj(m.n);

    // 3. Gleboka kopia danych (Deep Copy)
    if (m.data) {
        std::copy(m.data.get(), m.data.get() + (n * n), data.get());
    }

    return *this;
}