#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 3: WIZUALIZACJA I LOSOWOSC ===" << endl;

    matrix A(5); // Macierz 5x5
    cout << "1. Pusta macierz A (5x5):" << endl;
    cout << A << endl; // Test operatora <<

    cout << "2. Losowanie calej macierzy:" << endl;
    A.losuj();
    cout << A << endl;

    cout << "3. Losowanie 3 elementow (nadpisanie):" << endl;
    // Tworzymy nowa czysta macierz dla czytelnosci
    matrix B(4);
    B.losuj(3);
    cout << "Macierz B (4x4) z 3 losowymi cyframi:" << endl;
    cout << B << endl;

    return 0;
}