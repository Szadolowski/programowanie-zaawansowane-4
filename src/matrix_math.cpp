#include "../include/matrix.h"
#include <stdexcept>

// --- Operatory Arytmetyczne (Macierz <-> Macierz) ---

// Dodawanie: A + B
matrix matrix::operator+(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna dodawac macierzy roznych rozmiarow!");
    }

    matrix wynik(n); // Nowa macierz na wynik (zera)
    
    // Dodawanie element po elemencie
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] + m.data[i];
    }
    return wynik;
}

// Odejmowanie: A - B
matrix matrix::operator-(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna odejmowac macierzy roznych rozmiarow!");
    }

    matrix wynik(n);
    
    // Odejmowanie element po elemencie
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] - m.data[i];
    }
    return wynik;
}

// Mnozenie: A * B
// UWAGA: To jest mnozenie wiersz * kolumna (O(n^3)), a nie element * element!
matrix matrix::operator*(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna mnozyc macierzy roznych rozmiarow!");
    }

    matrix wynik(n); // Wynikowa macierz
    
    // y - wiersz w macierzy wynikowej
    for (int y = 0; y < n; ++y) {
        // x - kolumna w macierzy wynikowej
        for (int x = 0; x < n; ++x) {
            int suma = 0;
            // k - indeks do 'przesuwania sie' (wiersz w A, kolumna w B)
            for (int k = 0; k < n; ++k) {
                // A(k, y) * B(x, k)
                // this->at(k, y) to element z wiersza y kolumny k obecnej macierzy
                // m.at(x, k) to element z wiersza k kolumny x drugiej macierzy
                suma += this->at(k, y) * m.at(x, k);
            }
            wynik.wstaw(x, y, suma);
        }
    }
    return wynik;
}

// --- Operatory Skalarne (Macierz operacja Liczba) ---

matrix matrix::operator+(int a) const {
    matrix wynik(n);
    // Dodajemy liczbe 'a' do kazdego elementu
    for (int i = 0; i < n * n; ++i) {
        wynik.wstaw(i % n, i / n, data[i] + a);
    }
    return wynik;
}

matrix matrix::operator-(int a) const {
    matrix wynik(n);
    for (int i = 0; i < n * n; ++i) {
        wynik.wstaw(i % n, i / n, data[i] - a);
    }
    return wynik;
}

matrix matrix::operator*(int a) const {
    matrix wynik(n);
    for (int i = 0; i < n * n; ++i) {
        wynik.wstaw(i % n, i / n, data[i] * a);
    }
    return wynik;
}

// --- Funkcje Zaprzyjaznione (Liczba operacja Macierz) ---

// Dodawanie jest przemienne: 5 + A to to samo co A + 5
matrix operator+(int a, const matrix& m) {
    return m + a; 
}

// Mnozenie jest przemienne: 2 * A to to samo co A * 2
matrix operator*(int a, const matrix& m) {
    return m * a;
}

// Odejmowanie NIE jest przemienne: 10 - A to co innego niz A - 10
// Musimy stworzyc nowa macierz gdzie kazdy element to (a - element_macierzy)
matrix operator-(int a, const matrix& m) {
    matrix wynik(m.n); // m.n jest dostepne bo to friend
    for (int i = 0; i < m.n * m.n; ++i) {
        // Dostep bezposredni do m.data[] tez jest mozliwy (friend)
        // Ale dla bezpieczenstwa uzyjmy metod publicznych lub at() jesli sa
        // Tutaj mamy dostep do prywatnych bo friend
        wynik.wstaw(i % m.n, i / m.n, a - m.data[i]);
    }
    return wynik;
}