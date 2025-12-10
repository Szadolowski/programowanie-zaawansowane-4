#include <iostream>
#include "../include/matrix.h"

using namespace std;

int main() {
    cout << "=== TEST 8: POROWNANIA (==, >, <) ===" << endl;

    // Przypadek 1: Identyczne
    cout << "--- Przypadek 1: Identyczne ---" << endl;
    matrix A(2); A.wstaw(0,0, 5); A.wstaw(1,1, 5); // 5,0 / 0,5
    matrix B = A;
    
    cout << "A:\n" << A << "B:\n" << B;
    cout << "A == B: " << (A == B ? "TAK" : "NIE") << " (Oczekiwane: TAK)" << endl;

    // Przypadek 2: A wieksze od B
    cout << "\n--- Przypadek 2: A wieksze od B ---" << endl;
    // Zwiekszamy kazdy element A o 1, wiec A bedzie silnie wieksze
    A = A + 1; 
    cout << "A (+1):\n" << A << "B:\n" << B;
    
    cout << "A == B: " << (A == B ? "TAK" : "NIE") << " (Oczekiwane: NIE)" << endl;
    cout << "A > B:  " << (A > B ? "TAK" : "NIE") << " (Oczekiwane: TAK)" << endl;
    cout << "A < B:  " << (A < B ? "TAK" : "NIE") << " (Oczekiwane: NIE)" << endl;

    // Przypadek 3: Mieszane (Relacja nieokreslona)
    cout << "\n--- Przypadek 3: Relacja nieokreslona ---" << endl;
    // Zmieniamy B tak, zeby mialo jeden element wiekszy od A
    B.wstaw(0, 0, 100); 
    // A ma (6, 1 / 1, 6), B ma (100, 0 / 0, 5)
    // A[0][0] < B[0][0] (6 < 100) ALE A[1][1] > B[1][1] (6 > 5)
    // Wiec ani A>B, ani A<B, ani A==B.
    
    cout << "A:\n" << A << "B:\n" << B;
    cout << "A == B: " << (A == B ? "TAK" : "NIE") << " (Oczekiwane: NIE)" << endl;
    cout << "A > B:  " << (A > B ? "TAK" : "NIE") << " (Oczekiwane: NIE)" << endl;
    cout << "A < B:  " << (A < B ? "TAK" : "NIE") << " (Oczekiwane: NIE)" << endl;

    return 0;
}