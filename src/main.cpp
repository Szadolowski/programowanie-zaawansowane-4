#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "../include/matrix.h"
#include "../include/file_utils.h"

using namespace std;

// --- Funkcje Pomocnicze UI ---

void wyswietlMenu() {
    cout << "\n=== SYSTEM MACIERZY ===" << endl;
    cout << "1.  Alokuj macierze A i B (podaj wymiar)" << endl;
    cout << "2.  Wypelnij Macierz A (Losowo / Plik / Wzor)" << endl;
    cout << "3.  Wypelnij Macierz B (Losowo / Plik / Wzor)" << endl;
    cout << "4.  Wyswietl Macierze A i B" << endl;
    cout << "--- OPERACJE ---" << endl;
    cout << "5.  Dodawanie (A + B)" << endl;
    cout << "6.  Mnozenie (A * B)" << endl;
    cout << "7.  Transpozycja (A = A^T)" << endl;
    cout << "8.  Operacje z liczba (A + n, A * n, A(double)...)" << endl;
    cout << "9.  Porownanie (A == B, A > B)" << endl;
    cout << "--- TESTY SPECJALNE ---" << endl;
    cout << "10. Test wydajnosci (n=30) i mnozenie" << endl;
    cout << "0.  Wyjscie" << endl;
    cout << "Wybor: ";
}

// Funkcja do szybkiego wypelniania macierzy
void edytujMacierz(matrix& m, string nazwa) {
    cout << "\n--- Edycja Macierzy " << nazwa << " ---" << endl;
    cout << "1. Losuj (0-9)" << endl;
    cout << "2. Losuj X elementow" << endl;
    cout << "3. Macierz jednostkowa" << endl;
    cout << "4. Szachownica" << endl;
    cout << "5. Wczytaj z pliku (data/dane.txt)" << endl;
    cout << "Wybor: ";
    
    int opcja;
    cin >> opcja;

    try {
        switch (opcja) {
            case 1: m.losuj(); break;
            case 2: {
                int ilosc;
                cout << "Ile cyfr wstawic: ";
                cin >> ilosc;
                m.losuj(ilosc);
                break;
            }
            case 3: m.przekatna(); break;
            case 4: m.szachownica(); break;
            case 5: {
                string sciezka;
                cout << "Podaj sciezke (np. data/dane.txt): ";
                cin >> sciezka;
                vector<int> dane = wczytajDaneZPliku(sciezka);
                if (dane.size() >= m.size() * m.size()) {
                    // Tworzymy tymczasowa macierz z danych i kopiujemy
                    // To troche na okolo, ale pokazuje uzycie konstruktora z tablica
                    matrix temp(m.size(), dane.data());
                    m = temp; // Operator przypisania (move lub copy)
                    cout << "Dane wczytane!" << endl;
                } else {
                    cout << "Blad: Za malo danych w pliku dla macierzy " << m.size() << "x" << m.size() << endl;
                }
                break;
            }
            default: cout << "Nieznana opcja." << endl;
        }
    } catch (const exception& e) {
        cout << "Blad podczas edycji: " << e.what() << endl;
    }
}

void testDuzejMacierzy() {
    cout << "\n--- TEST WYDAJNOSCIOWY (n=30) ---" << endl;
    try {
        matrix DuzaA(30);
        matrix DuzaB(30);
        
        cout << "1. Losowanie danych..." << endl;
        DuzaA.losuj();
        DuzaB.losuj(); // albo np. szachownica

        cout << "2. Mnozenie macierzy 30x30..." << endl;
        matrix Wynik = DuzaA * DuzaB;

        cout << "3. Wynik mnozenia (fragment lewy gorny 5x5):" << endl;
        for(int y=0; y<5; ++y) {
            for(int x=0; x<5; ++x) {
                cout << Wynik.pokaz(x, y) << "\t";
            }
            cout << "..." << endl;
        }
        cout << "..." << endl;
        
        cout << "Test zakonczony sukcesem!" << endl;

    } catch (const exception& e) {
        cout << "TEST NIEUDANY: " << e.what() << endl;
    }
}

// --- MAIN ---

int main() {
    matrix A;
    matrix B;

    while (true) {
        wyswietlMenu();
        int wybor;
        if (!(cin >> wybor)) { // Zabezpieczenie przed wpisaniem liter
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (wybor == 0) break;

        try {
            switch (wybor) {
                case 1: {
                    int n;
                    cout << "Podaj rozmiar N: ";
                    cin >> n;
                    A.alokuj(n);
                    B.alokuj(n);
                    cout << "Zaalokowano macierze " << n << "x" << n << endl;
                    break;
                }
                case 2: edytujMacierz(A, "A"); break;
                case 3: edytujMacierz(B, "B"); break;
                case 4:
                    cout << "--- MACIERZ A ---" << endl << A << endl;
                    cout << "--- MACIERZ B ---" << endl << B << endl;
                    break;
                case 5: {
                    cout << "Wynik A + B:" << endl;
                    matrix C = A + B;
                    cout << C << endl;
                    break;
                }
                case 6: {
                    cout << "Wynik A * B:" << endl;
                    matrix C = A * B;
                    cout << C << endl;
                    break;
                }
                case 7: {
                    cout << "Transpozycja A:" << endl;
                    A.dowroc();
                    cout << A << endl;
                    break;
                }
                case 8: {
                    int k;
                    cout << "Podaj liczbe k: ";
                    cin >> k;
                    cout << "A + k = " << endl << (A + k) << endl;
                    cout << "A * k = " << endl << (A * k) << endl;
                    cout << "k * A = " << endl << (k * A) << endl; // Test friend
                    
                    cout << "Test funktora A(2.5) -> dodanie 2:" << endl;
                    matrix kopiaA = A;
                    kopiaA(2.5);
                    cout << kopiaA << endl;
                    break;
                }
                case 9: {
                    if (A == B) cout << "Macierze sa ROWNE" << endl;
                    else cout << "Macierze sa ROZNE" << endl;

                    if (A > B) cout << "Macierz A jest WIEKSZA od B" << endl;
                    else cout << "Nie mozna stwierdzic, ze A jest wieksza od B" << endl;
                    break;
                }
                case 10:
                    testDuzejMacierzy();
                    break;
                default:
                    cout << "Nieznana opcja" << endl;
            }
        } 
        catch (const std::exception& e) {
            // Tutaj lapiemy wszystkie bledy (zle wymiary, brak pamieci, indeksy)
            cerr << "\n!!! WYJATEK !!!: " << e.what() << endl;
            cerr << "Operacja anulowana.\n" << endl;
        }
    }

    return 0;
}