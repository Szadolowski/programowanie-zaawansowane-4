#include "../include/matrix.h"
#include <iomanip>

// --- Operatory Arytmetyczne (Macierz <-> Macierz) ---

matrix matrix::operator+(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna dodawac macierzy roznych rozmiarow!");
    }

    matrix wynik(n); // Nowa macierz na wynik
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] + m.data[i];
    }
    return wynik;
}

matrix matrix::operator-(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna odejmowac macierzy roznych rozmiarow!");
    }

    matrix wynik(n);
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] - m.data[i];
    }
    return wynik;
}

matrix matrix::operator*(const matrix& m) const {
    if (n != m.n) {
        throw std::invalid_argument("Blad: Nie mozna mnozyc macierzy roznych rozmiarow!");
    }

    matrix wynik(n); // Domyslnie wypelniona zerami
    
    // Klasyczny algorytm mnozenia macierzy (Wiersz * Kolumna)
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            int suma = 0;
            for (int k = 0; k < n; ++k) {
                suma += this->at(k, y) * m.at(x, k);
            }
            wynik.at(x, y) = suma;
        }
    }
    return wynik;
}

// --- Operatory Arytmetyczne (Macierz <-> Skalar) ---

matrix matrix::operator+(int a) const {
    matrix wynik(n);
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] + a;
    }
    return wynik;
}

matrix matrix::operator*(int a) const {
    matrix wynik(n);
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] * a;
    }
    return wynik;
}

matrix matrix::operator-(int a) const {
    matrix wynik(n);
    for (int i = 0; i < n * n; ++i) {
        wynik.data[i] = this->data[i] - a;
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

matrix& matrix::operator++(int) {
    // Wersja postfiksowa A++ powinna zwrocic kopie przed zmiana,
    // ale w zadaniu typ zwracany to matrix&, co sugeruje dzialanie na oryginale
    // lub blad w specyfikacji. Zaimplementujemy zwiekszenie wszystkich elementow.
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

matrix& matrix::operator()(double a) {
    int czesc_calkowita = static_cast<int>(a);
    // "wszystkie cyfry sa powiekszone o czesc calkowita"
    return (*this += czesc_calkowita); // Wykorzystujemy operator+=
}

// --- Operatory Porownania ---

bool matrix::operator==(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (data[i] != m.data[i]) return false;
    }
    return true;
}

bool matrix::operator>(const matrix& m) const {
    if (n != m.n) return false; // Nie mozna porownac, wiec falsz
    // "sprawdza, czy kazdy element macierzy spelnia nierownosc M(i, j) > N(i, j)"
    for (int i = 0; i < n * n; ++i) {
        if (data[i] <= m.data[i]) return false; // Jesli choc jeden nie jest wiekszy -> falsz
    }
    return true;
}

bool matrix::operator<(const matrix& m) const {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; ++i) {
        if (data[i] >= m.data[i]) return false;
    }
    return true;
}

// --- Funkcje Zaprzyjaznione (Friends) ---

matrix operator+(int a, const matrix& m) {
    return m + a; // Przemiennosc dodawania
}

matrix operator*(int a, const matrix& m) {
    return m * a; // Przemiennosc mnozenia
}

matrix operator-(int a, const matrix& m) {
    // a - M (odejmowanie nie jest przemienne!)
    matrix wynik(m.n);
    for (int i = 0; i < m.n * m.n; ++i) {
        wynik.data[i] = a - m.data[i];
    }
    return wynik;
}

std::ostream& operator<<(std::ostream& o, const matrix& m) {
    for (int y = 0; y < m.n; ++y) {
        o << "| ";
        for (int x = 0; x < m.n; ++x) {
            o << std::setw(4) << m.at(x, y) << " ";
        }
        o << "|" << std::endl;
    }
    return o;
}