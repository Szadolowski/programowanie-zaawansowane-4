#include "../include/matrix.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>

// --- Metody Prywatne ---

int& matrix::at(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        throw std::out_of_range("Blad: Indeks macierzy poza zakresem!");
    }
    // Mapowanie wspolrzednych 2D na indeks tablicy 1D
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
    // Inicjalizacja pustego obiektu
}

matrix::matrix(int n) : n(0), data(nullptr) {
    // Delegowanie zadania alokacji do metody alokuj()
    alokuj(n);
}

matrix::~matrix() {
    // std::unique_ptr automatycznie zwolni pamiec po wyjsciu z zakresu.
    // Nie trzeba recznie wolac delete[].
}

// --- Zarzadzanie Pamiecia ---

matrix& matrix::alokuj(int nowe_n) {
    // Zabezpieczenie przed ujemnym rozmiarem
    if (nowe_n < 0) return *this;

    // Przypadek 1: Macierz pusta - alokujemy nowa pamiec
    if (data == nullptr) {
        n = nowe_n;
        // make_unique alokuje tablice i zeruje ja
        data = std::make_unique<int[]>(n * n);
    } 
    // Przypadek 2: Zmiana rozmiaru - realokacja
    else if (n != nowe_n) {
        n = nowe_n;
        // Stary wskaznik zostanie automatycznie usuniety przy przypisaniu nowego
        data = std::make_unique<int[]>(n * n);
    }
    // Przypadek 3: Rozmiar ten sam - brak akcji (zgodnie z trescia zadania)
    
    return *this;
}

// --- Metody Dostepowe ---

matrix& matrix::wstaw(int x, int y, int wartosc) {
    // Uzywamy metody at() dla bezpieczenstwa (sprawdza zakresy)
    at(x, y) = wartosc;
    return *this;
}

int matrix::pokaz(int x, int y) const {
    return at(x, y);
}

int matrix::size() const {
    return n;
}

// Konstruktor z gotowej tablicy (np. int t[])
matrix::matrix(int n, int* t) : n(0), data(nullptr) {
    alokuj(n);
    if (t != nullptr) {
        // Kopiujemy dane z tablicy t do naszej pamieci
        std::copy(t, t + (n * n), data.get());
    }
}

// Konstruktor kopiujacy (tworzy nowy obiekt na podstawie istniejacego)
matrix::matrix(const matrix& m) : n(0), data(nullptr) {
    // 1. Alokujemy wlasna pamiec o takim samym rozmiarze
    alokuj(m.n);
    
    // 2. Kopiujemy dane (jesli zrodlo nie jest puste)
    if (m.data) {
        std::copy(m.data.get(), m.data.get() + (n * n), data.get());
    }
    std::cout << "Konstruktor kopiujacy: Skopiowano macierz " << n << "x" << n << std::endl;
}

// Operator przypisania (obsluguje A = B dla istniejacych obiektow)
matrix& matrix::operator=(const matrix& m) {
    // 1. Ochrona przed autozapisem (A = A)
    if (this == &m) {
        return *this;
    }

    // 2. Dopasowanie rozmiaru (realokacja jesli konieczna)
    alokuj(m.n);

    // 3. Kopiowanie danych
    if (m.data) {
        std::copy(m.data.get(), m.data.get() + (n * n), data.get());
    }
    
    return *this;
}

// --- Operator Wyswietlania (Friend) ---

std::ostream& operator<<(std::ostream& o, const matrix& m) {
    // Iterujemy po wierszach (y) i kolumnach (x)
    for (int y = 0; y < m.n; ++y) {
        o << "| ";
        for (int x = 0; x < m.n; ++x) {
            // setw(4) ustawia stala szerokosc pola, zeby kolumny byly rowne
            o << std::setw(4) << m.at(x, y) << " ";
        }
        o << "|" << std::endl;
    }
    return o;
}