#include "../include/matrix.h"
#include <random> // Do generatora liczb losowych
#include <ctime>  // Do time(nullptr)
#include <cmath> // do std::abs
#include <algorithm> // do std::swap

// --- Metody Losujace ---

matrix& matrix::losuj() {
    // Inicjalizacja generatora (tylko raz, statycznie)
    static std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    // Zakres losowania cyfr od 0 do 9
    std::uniform_int_distribution<> dist(0, 9);

    // Wypelniamy cala tablice
    for (int i = 0; i < n * n; ++i) {
        data[i] = dist(gen);
    }
    return *this;
}

matrix& matrix::losuj(int ilosc) {
    static std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> distVal(0, 9);     // Wartosc 0-9
    std::uniform_int_distribution<> distPos(0, n - 1); // Pozycja 0..(n-1)

    // Najpierw mozna wyzerowac macierz (opcjonalnie), tutaj tylko wstawiamy
    // Wstawiamy 'ilosc' losowych cyfr w losowe miejsca
    for (int k = 0; k < ilosc; ++k) {
        int x = distPos(gen);
        int y = distPos(gen);
        wstaw(x, y, distVal(gen));
    }
    return *this;
}

// --- Operacje na Strukturze ---

matrix& matrix::dowroc() {
    // Transpozycja: zamieniamy element (x, y) z (y, x)
    // Iterujemy tylko po trojkacie gornym, zeby nie zamieniac dwa razy
    for (int y = 0; y < n; ++y) {
        for (int x = y + 1; x < n; ++x) {
            std::swap(at(x, y), at(y, x));
        }
    }
    return *this;
}

// --- Wzorce i Przekatne ---

matrix& matrix::diagonalna(int* t) {
    // Przekatna glowna to przypadek diagonalna_k dla k=0
    return diagonalna_k(0, t);
}

matrix& matrix::diagonalna_k(int k, int* t) {
    // 1. Zerujemy cala macierz (wymog zadania)
    // Mozemy uzyc wstaw() w petli lub memset, ale petla jest bezpieczna dla unique_ptr
    for(int i=0; i<n*n; ++i) data[i] = 0;

    if (t == nullptr) return *this;

    // 2. Logika przesuniecia
    // k = 0 -> glowna (x=y)
    // k > 0 -> nad glowna (x = y + k)
    // k < 0 -> pod glowna (y = x + |k|)
    
    // Obliczamy dlugosc przekatnej
    int dlugosc = n - std::abs(k);
    if (dlugosc <= 0) return *this; // k poza zakresem

    // Ustalamy punkt startowy
    int start_x = (k > 0) ? k : 0;
    int start_y = (k > 0) ? 0 : -k;

    for (int i = 0; i < dlugosc; ++i) {
        at(start_x + i, start_y + i) = t[i];
    }

    return *this;
}

matrix& matrix::kolumna(int x, int* t) {
    if (x < 0 || x >= n || t == nullptr) return *this;

    for (int y = 0; y < n; ++y) {
        at(x, y) = t[y];
    }
    return *this;
}

matrix& matrix::wiersz(int y, int* t) {
    if (y < 0 || y >= n || t == nullptr) return *this;

    for (int x = 0; x < n; ++x) {
        at(x, y) = t[x];
    }
    return *this;
}

// --- Wzorce Binarne (0/1) ---

matrix& matrix::przekatna() {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            at(x, y) = (x == y) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::pod_przekatna() {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            at(x, y) = (y > x) ? 1 : 0; // y > x to obszar pod przekatna
        }
    }
    return *this;
}

matrix& matrix::nad_przekatna() {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            at(x, y) = (x > y) ? 1 : 0; // x > y to obszar nad przekatna
        }
    }
    return *this;
}

matrix& matrix::szachownica() {
    // Wzor szachownicy: suma indeksow parzysta/nieparzysta
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            at(x, y) = (x + y) % 2;
        }
    }
    return *this;
}