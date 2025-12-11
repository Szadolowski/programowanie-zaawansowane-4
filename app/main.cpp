#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <fstream> 
#include "../include/matrix.h"
#include "../include/file_utils.h"

using namespace std;

// --- FUNKCJE POMOCNICZE ---

void naglowek(string tytul) {
    cout << "\n==========================================" << endl;
    cout << "   TEST: " << tytul << endl;
    cout << "==========================================" << endl;
}

void sukces(string msg) {
    cout << "[ OK ] " << msg << endl;
}

// --- SCENARIUSZE TESTOWE (REALIZACJA WYMAGAN) ---

// Służy do pokazania: konstruktorów, alokacji, unique_ptr i deep copy
void Test1_Pamiec_Konstruktory() {
    naglowek("1. Zarzadzanie Pamiecia i Konstruktory");

    // Wymaganie: matrix(void) i alokuj(n)
    matrix A;
    A.alokuj(3);
    cout << "1. Zaalokowano A (3x3)." << endl;

    // Wymaganie: matrix(int n, int* t)
    int dane[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix B(3, dane);
    cout << "2. Utworzono B z tablicy:\n" << B;

    // Wymaganie: matrix(matrix& m) - Konstruktor kopiujacy
    matrix C = B;
    cout << "3. Utworzono C jako kopie B (Test Deep Copy)." << endl;
    
    // Sprawdzamy czy kopia jest głęboka (zmiana C nie psuje B)
    C.wstaw(0, 0, 999);
    if(B.pokaz(0,0) == 1 && C.pokaz(0,0) == 999) 
        sukces("Gleboka kopia dziala poprawnie.");
    else 
        cout << "[ BLAD ] Plytka kopia! Zmiana w C zepsula B!" << endl;
}

// Służy do pokazania: losuj, dowroc, wzorców (diagonalna, szachownica itp.)
void Test2_Logika_Ksztalty() {
    naglowek("2. Logika, Wzorce, Transpozycja");
    
    matrix M(4);

    // Wymaganie: losuj()
    M.losuj();
    cout << "1. Losuj calosc:\n" << M;

    // Wymaganie: dowroc()
    cout << "2. Transpozycja (dowroc):" << endl;
    int dane[] = {1, 2, 3, 4}; // 2x2
    matrix T(2, dane);
    cout << "   Przed:\n" << T;
    T.dowroc();
    cout << "   Po:\n" << T;

    // Wymagania: wzorce binarne
    M.alokuj(4); M.szachownica();   cout << "3. Szachownica:\n" << M;
    M.przekatna();     cout << "4. Przekatna:\n" << M;
    M.nad_przekatna(); cout << "5. Nad przekatna:\n" << M;

    // Wymagania: wzorce z tablicy
    int t[] = {9, 9, 9, 9}; 
    M.diagonalna(t);        cout << "6. Diagonalna (z tablicy):\n" << M;
    M.kolumna(0, t);        cout << "7. Kolumna 0 (z tablicy):\n" << M;
}

// Służy do pokazania: operatorów +, -, * (macierzowych i skalarnych)
void Test3_Operatory_Arytmetyczne() {
    naglowek("3. Operatory (+, -, *)");

    int tA[] = {2, 2, 2, 2};
    int tB[] = {1, 1, 1, 1};
    matrix A(2, tA);
    matrix B(2, tB);

    cout << "A (same 2), B (same 1)." << endl;

    // Wymaganie: A+B, A-B, A*B
    cout << "1. A + B (oczekiwane 3):\n" << (A + B);
    cout << "2. A - B (oczekiwane 1):\n" << (A - B);
    cout << "3. A * B (oczekiwane 4):\n" << (A * B);

    // Wymaganie: Operacje z liczbą (skalar) i friend
    cout << "4. A + 10 (skalar):\n" << (A + 10);
    cout << "5. 5 * A  (friend):\n" << (5 * A);
    cout << "6. 10 - A (friend):\n" << (10 - A);
}

// Służy do pokazania: ++, +=, (), ==, >
void Test4_Modyfikacje_Porownania() {
    naglowek("4. Modyfikacje (+=, ++, ()) i Porownania");

    matrix A(2); // Zera
    
    // Wymaganie: ++
    A++; 
    cout << "1. A++ (wszystko +1):\n" << A;
    
    // Wymaganie: +=, *=
    A += 10; cout << "2. A += 10:\n" << A;
    A *= 2;  cout << "3. A *= 2:\n"  << A;
    
    // Wymaganie: Funktor ()
    A.alokuj(2); 
    A(3.99);     
    cout << "4. Funktor A(3.99) -> dodaj 3:\n" << A;

    // Wymaganie: Porównania ==, >
    matrix B = A;
    cout << "5. Porownania:" << endl;
    cout << "   A == B? " << (A == B ? "TAK" : "NIE") << endl;
    
    B.wstaw(0,0, 0); // Zmniejszamy B
    cout << "   Zmniejszylem B(0,0). A > B? " << (A > B ? "TAK" : "NIE") << endl;
}

// Służy do pokazania: wczytywania z pliku i testu n=30
void Test5_Pliki_Wydajnosc() {
    naglowek("5. Obsluga Plikow i Test n=30");

    // Wymaganie: Wczytanie z pliku
    try {
        string inPath = "../data/test_input.txt"; // Wychodzimy z app do data
        string outPath = "../data/test_output.txt";
        
        // Generujemy plik, zeby test zawsze dzialal
        ofstream plik(inPath);
        if(plik.is_open()) {
            plik << "10 20 30 40"; 
            plik.close();
            
            vector<int> dane = wczytajDaneZPliku(inPath);
            if(!dane.empty()) {
                matrix M(2, dane.data());
                cout << "1. Wczytano z pliku " << inPath << ":\n" << M;
                
                zapiszMacierzDoPliku(outPath, M);
                cout << "2. Zapisano macierz do " << outPath << endl;
            }
        } else {
            cout << "[UWAGA] Nie udalo sie utworzyc pliku w ../data/. Sprawdz folder." << endl;
        }
    } catch (exception& e) {
        cout << "Blad plikow: " << e.what() << endl;
    }

    // Wymaganie: Test n=30
    cout << "\n--- TEST WYDAJNOSCIOWY (n=30) ---" << endl;
    try {
        matrix BigA(30);
        matrix BigB(30);
        
        cout << "Generowanie danych..." << endl;
        BigA.losuj();
        BigB.szachownica();

        cout << "Mnozenie macierzy 30x30..." << endl;
        matrix Wynik = BigA * BigB;

        cout << "Wynik (fragment 5x5):" << endl;
        for(int y=0; y<5; ++y) {
            for(int x=0; x<5; ++x) cout << Wynik.pokaz(x, y) << "\t";
            cout << "..." << endl;
        }
        sukces("Test wydajnosci zakonczony.");
        zapiszMacierzDoPliku("../data/test_output.txt", Wynik);
    } catch (exception& e) {
        cout << "BLAD: " << e.what() << endl;
    }
}

// Test scalania macierzy o różnych rozmiarach
void Test6_Scalanie_Rozne_Rozmiary() {
    naglowek("6. Scalanie Macierzy o Różnych Rozmiarach");
    
    cout << "Tworzenie macierzy A (2x2) i B (3x3)..." << endl;
    
    // Macierz A o rozmiarze 2x2
    int dane_A[] = {1, 2, 3, 4};
    matrix A(2, dane_A);
    cout << "Macierz A (2x2):\n" << A;
    
    // Macierz B o rozmiarze 3x3
    int dane_B[] = {5, 6, 7, 8, 9, 10, 11, 12, 13};
    matrix B(3, dane_B);
    cout << "Macierz B (3x3):\n" << B;
    
    // Próba scalania macierzy o różnych rozmiarach
    cout << "\nPróba dodawania A + B (różne rozmiary)..." << endl;
    try {
        matrix Wynik = A + B;
        cout << "Wynik:\n" << Wynik;
    } catch (const exception& e) {
        cout << "[ BLAD PRZEWIDZIANY ] Złapano wyjątek: " << e.what() << endl;
    }
    
    cout << "\nPróba odejmowania A - B (różne rozmiary)..." << endl;
    try {
        matrix Wynik = A - B;
        cout << "Wynik:\n" << Wynik;
    } catch (const exception& e) {
        cout << "[ BLAD PRZEWIDZIANY ] Złapano wyjątek: " << e.what() << endl;
    }
    
    cout << "\nPróba mnożenia A * B (różne rozmiary)..." << endl;
    try {
        matrix Wynik = A * B;
        cout << "Wynik:\n" << Wynik;
    } catch (const exception& e) {
        cout << "[ BLAD PRZEWIDZIANY ] Złapano wyjątek: " << e.what() << endl;
    }
    
    sukces("Test scalania macierzy o różnych rozmiarach zakonczony.");
}

int main() {

    // Menu Główne - Sterowanie Testami
    while (true) {
        cout << "\n=== SYSTEM MACIERZY (PROJEKT P4) ===" << endl;
        cout << "1. Test Pamieci (Konstruktory, Alokacja)" << endl;
        cout << "2. Test Logiki (Wzorce, Losowanie, Transpozycja)" << endl;
        cout << "3. Test Matematyki (Operatory +, -, *)" << endl;
        cout << "4. Test Modyfikacji (++, +=, Porownania)" << endl;
        cout << "5. Test Plikow i Wydajnosci (n=30)" << endl;
        cout << "6. Test Scalania Macierzy o Różnych Rozmiarach" << endl;
        cout << "9. URUCHOM WSZYSTKIE TESTY (Pelna prezentacja)" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "Wybor: ";

        int opcja;
        if (!(cin >> opcja)) {
            cin.clear(); cin.ignore(1000, '\n'); continue;
        }

        if (opcja == 0) break;

        try {
            switch (opcja) {
                case 1: Test1_Pamiec_Konstruktory(); break;
                case 2: Test2_Logika_Ksztalty(); break;
                case 3: Test3_Operatory_Arytmetyczne(); break;
                case 4: Test4_Modyfikacje_Porownania(); break;
                case 5: Test5_Pliki_Wydajnosc(); break;
                case 6: Test6_Scalanie_Rozne_Rozmiary(); break;
                case 9:
                    Test1_Pamiec_Konstruktory();
                    Test2_Logika_Ksztalty();
                    Test3_Operatory_Arytmetyczne();
                    Test4_Modyfikacje_Porownania();
                    Test5_Pliki_Wydajnosc();
                    Test6_Scalanie_Rozne_Rozmiary();
                    break;
                default: cout << "Nieznana opcja." << endl;
            }
        } catch (const exception& e) {
            cout << "\n!!! WYLAPANO BLAD KRYTYCZNY: " << e.what() << endl;
        }
        
        cout << "\n(Nacisnij Enter...)";
        cin.ignore(); cin.get();
    }
    
    // Pauza na koniec (dla Windows)
    cout << "\nKoniec programu.";
    cin.ignore(); cin.get();



    return 0;
}