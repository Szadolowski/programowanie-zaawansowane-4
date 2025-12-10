#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 7: MODYFIKACJE I INKREMENTACJA ===" << endl;

    // Startujemy z macierza wypelniona zerami
    matrix A(2); 
    cout << "Start A (zera):" << endl << A;

    // 1. Inkrementacja (A++)
    A++;
    cout << "1. Po A++ (oczekiwane 1):" << endl << A;

    // 2. Modyfikacja +=
    A += 10;
    cout << "2. Po A += 10 (oczekiwane 11):" << endl << A;

    // 3. Modyfikacja *=
    A *= 2;
    cout << "3. Po A *= 2 (oczekiwane 22):" << endl << A;

    // 4. Dekrementacja (A--)
    A--;
    cout << "4. Po A-- (oczekiwane 21):" << endl << A;

    // 5. Funktor A(double)
    // Dodajemy czesc calkowita z 5.99 (czyli 5)
    A(5.99);
    cout << "5. Po A(5.99) (oczekiwane 26):" << endl << A;

    return 0;
}