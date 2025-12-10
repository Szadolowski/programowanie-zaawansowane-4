#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 4: KSZTALTY I STRUKTURA ===" << endl;

    int rozmiar = 4;
    matrix M(rozmiar);

    // 1. Szachownica
    cout << "1. Szachownica (4x4):" << endl;
    M.szachownica();
    cout << M << endl;

    // 2. Przekatna (Jednostkowa)
    cout << "2. Przekatna glowna:" << endl;
    M.przekatna();
    cout << M << endl;

    // 3. Nad przekatna
    cout << "3. Trojkat gorny (nad przekatna):" << endl;
    M.nad_przekatna();
    cout << M << endl;

    // 4. Diagonalna przesunieta (z tablicy)
    cout << "4. Diagonalna z tablicy przesunieta o k=1:" << endl;
    int dane[] = {9, 9, 9, 9}; // Dane do wpisania
    M.diagonalna_k(1, dane);
    cout << M << endl;

    // 5. Transpozycja
    cout << "5. Test Transpozycji:" << endl;
    // Najpierw stworzmy niesymetryczna macierz
    M.alokuj(3); // Zmieniamy na 3x3 dla czytelnosci
    M.wstaw(0, 1, 5); // Wstawiamy 5 w dolnym lewym rogu (kolumna 0, wiersz 1)
    cout << "Przed obrotem (5 jest na dole po lewej):" << endl;
    cout << M;
    
    M.dowroc();
    cout << "Po obrocie (5 powinno byc na gorze po prawej):" << endl;
    cout << M << endl;

    return 0;
}