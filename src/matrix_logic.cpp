#include "../include/matrix.h"
#include <random>
#include <ctime>
#include <algorithm> // do std::swap

// --- Metody Losujące ---

matrix& matrix::losuj() {
    // Uzywamy nowoczesnego generatora liczb losowych z C++11
    static std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> dist(0, 9);

    for (int i = 0; i < n * n; ++i) {
        data[i] = dist(gen);
    }
    return *this;
}

matrix& matrix::losuj(int ilosc) {
    // Wypelnij zerami na start (opcjonalne, ale logiczne przy "wstawianiu w losowe miejsca")
    // std::fill(data.get(), data.get() + n * n, 0); 
    // ^ Odkomentuj powyzsze, jesli macierz ma byc czysta przed losowaniem.
    // Z tresci zadania nie wynika wprost, czy czyscic, wiec zostawiam nadpisywanie obecnych.

    static std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> distVal(0, 9);     // Wartosci 0-9
    std::uniform_int_distribution<> distPos(0, n - 1); // Pozycje 0..(n-1)

    for (int k = 0; k < ilosc; ++k) {
        int x = distPos(gen);
        int y = distPos(gen);
        // Wstaw wylosowana cyfre w losowe miejsce
        at(x, y) = distVal(gen);
    }
    return *this;
}

// --- Operacje na Strukturze ---

matrix& matrix::dowroc() {
    // Transpozycja macierzy (zamiana wierszy z kolumnami)
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
    // Przekatna przechodzaca przez srodek (k=0)
    return diagonalna_k(0, t);
}

matrix& matrix::diagonalna_k(int k, int* t) {
    // 1. Wyzeruj cala macierz (zgodnie z wymogiem: "pozostałe elementy są równe 0")
    std::fill(data.get(), data.get() + n * n, 0);

    if (t == nullptr) return *this;

    // 2. Logika przesuniecia
    // k = 0 -> glowna przekatna (x=y)
    // k > 0 -> przesuniecie w gore/prawo (x = y + k)
    // k < 0 -> przesuniecie w dol/lewo (y = x + abs(k))

    for (int i = 0; i < n; ++i) {
        // Obliczamy wspolrzedne na podstawie i (gdzie i to indeks wiersza lub kolumny bazowej)
        int y = i;
        int x = i + k; // Dla k ujemnego x bedzie mniejsze od y

        // Korekta dla k ujemnego:
        // Jesli k jest np. -1, to chcemy zaczac od y=1, x=0.
        // Powyzszy wzor x = y + k dziala uniwersalnie:
        // y=0 -> x=-1 (poza zakresem, pomijamy)
        // y=1 -> x=0 (ok)
        
        // Sprawdzamy czy punkt miesci sie w macierzy
        if (x >= 0 && x < n && y >= 0 && y < n) {
            // Pobieramy wartosc z tablicy t.
            // UWAGA: t musi miec odpowiednia dlugosc. Zakladamy ze ma.
            // Indeks w t rosnie z kazda iteracja glownej petli,
            // ale musimy uwazac, ktory element t bierzemy.
            // Przyjmijmy, ze t[0] to pierwszy element widocznej przekatnej.
            
            // Ponizsza logika zaklada, ze t ma tyle elementow ile dlugosc przekatnej
            // Dlugosc przekatnej to n - abs(k)
            int index_w_t = (k >= 0) ? i : (i + k); // Korekta indeksowania dla ujemnych k?
            // Uproszczenie: po prostu bierzemy kolejne elementy t dla kolejnych wypelnianych pol.
            // Musimy tylko liczyc ile pol juz wypelnilismy.
        }
    }

    // PODEJSCIE 2 (Bardziej czytelne):
    // Przejdzmy po prostu po dlugosci przekatnej.
    int dlugosc = n - std::abs(k);
    if (dlugosc <= 0) return *this; // k poza zakresem macierzy

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
            at(x, y) = (y > x) ? 1 : 0;
        }
    }
    return *this;
}

matrix& matrix::nad_przekatna() {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            at(x, y) = (x > y) ? 1 : 0; // x > y oznacza nad przekatna
        }
    }
    return *this;
}

matrix& matrix::szachownica() {
    // Wzor: 0101...
    // Zaleznosc: (x + y) % 2
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            // Jesli suma indeksow jest parzysta -> 0, nieparzysta -> 1
            // Daje to efekt szachownicy.
            at(x, y) = (x + y) % 2;
        }
    }
    return *this;
}