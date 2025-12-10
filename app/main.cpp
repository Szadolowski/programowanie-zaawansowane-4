#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 1: ALOKACJA ===" << endl;

    // 1. Test konstruktora domyslnego
    cout << "-> Tworze macierz A (domyslna)..." << endl;
    matrix A;
    
    // 2. Test alokacji
    cout << "-> Alokuje pamiec dla A (5x5)..." << endl;
    A.alokuj(5);
    cout << "Rozmiar A: " << A.size() << endl;

    // 3. Test konstruktora z parametrem
    cout << "-> Tworze macierz B (10x10) konstruktorem..." << endl;
    matrix B(10);
    cout << "Rozmiar B: " << B.size() << endl;

    cout << "\nKoniec programu (teraz powinny uruchomic sie destruktory)." << endl;
    return 0;
}