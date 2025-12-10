#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 2: KOPIOWANIE I BEZPIECZENSTWO ===" << endl;

    // 1. Tworzymy macierz A
    cout << "-> Tworze A (2x2)..." << endl;
    matrix A(2);
    A.wstaw(0, 0, 10); // A[0][0] = 10
    cout << "A(0,0) = " << A.pokaz(0,0) << endl;

    // 2. Tworzymy B jako kopie A (Konstruktor kopiujacy)
    cout << "-> Tworze B = A..." << endl;
    matrix B = A; 

    // 3. Modyfikujemy TYLKO B
    cout << "-> Zmieniam B(0,0) na 999..." << endl;
    B.wstaw(0, 0, 999);

    // 4. Weryfikacja (Czy A pozostalo bez zmian?)
    cout << "Wartosc w B: " << B.pokaz(0,0) << endl;
    cout << "Wartosc w A: " << A.pokaz(0,0) << endl;

    if (A.pokaz(0,0) == 10) {
        cout << "[SUKCES] A pozostalo bez zmian. Gleboka kopia dziala." << endl;
    } else {
        cout << "[BLAD] A tez sie zmienilo! Mamy plytka kopie (wspoldzielona pamiec)." << endl;
    }

    // 5. Test operatora przypisania
    cout << "-> Test operatora przypisania (A = B)..." << endl;
    A = B; // Teraz A powinno przejac wartosci z B (czyli 999)
    cout << "A(0,0) po przypisaniu: " << A.pokaz(0,0) << endl;

    return 0;
}