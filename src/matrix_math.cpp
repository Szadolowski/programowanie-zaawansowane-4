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
// Zoptymalizowana wersja z jedną pętlą zewnętrzną i bezpośrednim dostępem do danych
matrix matrix::operator*(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna mnozyc macierzy roznych rozmiarow!");
    }

    matrix wynik(n); // Wynikowa macierz
    int* w_data = wynik.data.get(); // Bezpośredni dostęp do danych wyniku
    const int* a_data = this->data.get(); // Dane macierzy A
    const int* b_data = m.data.get(); // Dane macierzy B
    
    // Pojedyncza pętla po wszystkich elementach wyniku
    for (int idx = 0; idx < n * n; ++idx) {
        int y = idx / n;  // Wiersz
        int x = idx % n;  // Kolumna
        int suma = 0;
        
        // Iloczyn skalarny wiersza A z kolumną B
        for (int k = 0; k < n; ++k) {
            suma += a_data[y * n + k] * b_data[k * n + x];
        }
        w_data[idx] = suma;
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

// --- Operatory Modyfikujace (Compound Assignment) ---

matrix& matrix::operator+=(int a) {
    for (int i = 0; i < n * n; ++i) {
        data[i] += a;
    }
    return *this;
}

matrix& matrix::operator-=(int a) {
    for (int i = 0; i < n * n; ++i) {
        data[i] -= a;
    }
    return *this;
}

matrix& matrix::operator*=(int a) {
    for (int i = 0; i < n * n; ++i) {
        data[i] *= a;
    }
    return *this;
}

// --- Operatory Inkrementacji/Dekrementacji (Postfiks) ---

// Zgodnie z zadaniem: "wszystkie liczby powiekszone o 1"
// Zwracamy referencje (matrix&), wiec dzialamy na oryginalnym obiekcie.
matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; ++i) {
        data[i]++;
    }
    return *this;
}

matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; ++i) {
        data[i]--;
    }
    return *this;
}

// --- Funktor (Operator wywolania) ---

// Zadanie: "wszystkie cyfry sa powiekszone o czesc calkowita z wpisanej cyfry"
matrix& matrix::operator()(double a) {
    int czesc_calkowita = static_cast<int>(a);
    // Wykorzystujemy istniejacy operator += zeby nie powielac kodu
    return (*this += czesc_calkowita);
}

// --- Operatory Porownania ---

bool matrix::operator==(const matrix& m) const {
    // 1. Sprawdzenie wymiarow
    if (n != m.n) {
        return false; // Rozne wymiary = nie sa rowne
    }

    // 2. Sprawdzenie kazdego elementu
    for (int i = 0; i < n * n; ++i) {
        if (data[i] != m.data[i]) {
            return false; // Znaleziono roznice
        }
    }
    return true; // Przeszlismy cala tablice, wszystko sie zgadza
}

bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false; // Nie mozna porownac wymiarow

    // Definicja: Kazdy element A musi byc wiekszy od elementu B
    for (int i = 0; i < n * n; ++i) {
        if (data[i] <= m.data[i]) {
            return false; // Znaleziono element, ktory nie jest wiekszy
        }
    }
    return true;
}

bool matrix::operator<(const matrix& m) const {
    if (n != m.n) return false;

    // Definicja: Kazdy element A musi byc mniejszy od elementu B
    for (int i = 0; i < n * n; ++i) {
        if (data[i] >= m.data[i]) {
            return false; // Znaleziono element, ktory nie jest mniejszy
        }
    }
    return true;
}