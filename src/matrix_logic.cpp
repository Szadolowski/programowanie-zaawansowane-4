#include "../include/matrix.h"
#include <random> // Do generatora liczb losowych
#include <ctime>  // Do time(nullptr)

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