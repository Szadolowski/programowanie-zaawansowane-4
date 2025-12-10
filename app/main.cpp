#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 6: ARYTMETYKA SKALARNA ===" << endl;

    // Macierz 2x2 z samymi jedynkami
    int t[] = {1, 1, 1, 1};
    matrix A(2, t);
    
    cout << "Macierz A (same 1):" << endl << A;

    // 1. Dodawanie skalarne (A + 5)
    cout << "1. A + 5 (oczekiwane 6):" << endl;
    cout << (A + 5);

    // 2. Mnozenie skalarne (A * 10)
    cout << "2. A * 10 (oczekiwane 10):" << endl;
    cout << (A * 10);

    // 3. Friend: Liczba + Macierz (5 + A)
    cout << "3. 5 + A (oczekiwane 6):" << endl;
    cout << (5 + A);

    // 4. Friend: Odejmowanie (10 - A)
    // 10 - 1 = 9
    cout << "4. 10 - A (oczekiwane 9):" << endl;
    cout << (10 - A);

    return 0;
}