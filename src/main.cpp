#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <cmath>
#include "../include/matrix.h"
#include "../include/file_utils.h"

using namespace std;

/**
 * @brief Wyswietla glowne menu programu.
 */
void wyswietlMenu() {
    cout << "\n=== GLOWNE MENU PROGRAMU ===" << endl;
    cout << "--- Sekcja 1: Zarzadzanie Pamiecia i Konstruktory ---" << endl;
    cout << "1.  Alokuj A i B (puste)" << endl;
    cout << "2.  Alokuj A z tablicy" << endl;
    cout << "3.  Test konstruktora kopiujacego" << endl;
    cout << "4.  Zwolnij pamiec / Reset" << endl;
    
    cout << "--- Sekcja 2: Wypelnianie i Edycja (Operacje na Macierzy A) ---" << endl;
    cout << "5.  Wstaw pojedyncza wartosc" << endl;
    cout << "6.  Losuj cala macierz" << endl;
    cout << "7.  Losuj X elementow" << endl;
    cout << "8.  Wczytaj z pliku" << endl;

    cout << "--- Sekcja 3: Wzorce i Struktura (Metody logiczne na A) ---" << endl;
    cout << "9.  Wypelnij przekatna (z tablicy)" << endl;
    cout << "10. Wypelnij przekatna przesunieta k" << endl;
    cout << "11. Wypelnij kolumne X (z tablicy)" << endl;
    cout << "12. Wypelnij wiersz Y (z tablicy)" << endl;
    cout << "13. Transpozycja" << endl;
    cout << "14. Wzorce Binarne (0/1)" << endl;

    cout << "--- Sekcja 4: Matematyka Macierzowa (A i B) ---" << endl;
    cout << "15. Dodawanie (A + B)" << endl;
    cout << "16. Mnozenie (A * B)" << endl;

    cout << "--- Sekcja 5: Operatory Skalarne i Modyfikujace ---" << endl;
    cout << "17. Dodawanie liczby (A+k oraz k+A)" << endl;
    cout << "18. Mnozenie przez liczbe (A*k oraz k*A)" << endl;
    cout << "19. Odejmowanie liczby (A-k oraz k-A)" << endl;
    cout << "20. Modyfikacja A (+=, -=, *=)" << endl;
    cout << "21. Inkrementacja/Dekrementacja (A++, A--)" << endl;
    cout << "22. Funktor A(double)" << endl;

    cout << "--- Sekcja 6: Porownania ---" << endl;
    cout << "23. Sprawdz relacje (==, >, <)" << endl;

    cout << "--- Sekcja 7: Finalne Testy i Wyjscie ---" << endl;
    cout << "24. Pokaz obie macierze" << endl;
    cout << "25. Zapisz A do pliku" << endl;
    cout << "26. TEST WYDAJNOSCI (n=30)" << endl;
    cout << "0.  Wyjscie" << endl;
    cout << "Wybor: ";
}

/**
 * @brief Pomocnicza funkcja generujaca wektor danych testowych.
 * @param n Rozmiar wektora.
 * @return std::vector<int> Wektor z kolejnymi liczbami.
 */
vector<int> generujDaneTestowe(int n) {
    vector<int> dane(n);
    for(int i=0; i<n; ++i) dane[i] = i + 1;
    return dane;
}

/**
 * @brief Test wydajnosci dla duzych macierzy.
 */
void testWydajnosci() {
    cout << "\n--- TEST WYDAJNOSCIOWY (n=30) ---" << endl;
    try {
        matrix DuzaA(30);
        matrix DuzaB(30);
        
        cout << "1. Losowanie danych..." << endl;
        DuzaA.losuj();
        DuzaB.losuj();

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

int main() {
    matrix A;
    matrix B;

    while (true) {
        wyswietlMenu();
        int wybor;
        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (wybor == 0) break;

        try {
            switch (wybor) {
                // --- Sekcja 1 ---
                case 1: {
                    int n;
                    cout << "Podaj rozmiar N: ";
                    cin >> n;
                    A.alokuj(n);
                    B.alokuj(n);
                    cout << "Zaalokowano macierze A i B o wymiarze " << n << "x" << n << endl;
                    break;
                }
                case 2: {
                    int n;
                    cout << "Podaj rozmiar N: ";
                    cin >> n;
                    vector<int> dane = generujDaneTestowe(n * n);
                    // Uzywamy konstruktora z tablica
                    matrix Temp(n, dane.data());
                    A = Temp; // Operator przypisania
                    cout << "Zaalokowano A z tablicy (kolejne liczby)." << endl;
                    break;
                }
                case 3: {
                    cout << "Tworzenie kopii A..." << endl;
                    matrix Kopia = A; // Konstruktor kopiujacy
                    cout << "Oryginal A:" << endl << A << endl;
                    cout << "Kopia A:" << endl << Kopia << endl;
                    cout << "Modyfikuje kopie (losuje)..." << endl;
                    Kopia.losuj();
                    cout << "Oryginal A (powinien byc bez zmian):" << endl << A << endl;
                    cout << "Kopia A (zmieniona):" << endl << Kopia << endl;
                    break;
                }
                case 4: {
                    A.alokuj(0);
                    B.alokuj(0);
                    cout << "Pamiec zwolniona." << endl;
                    break;
                }

                // --- Sekcja 2 ---
                case 5: {
                    int x, y, val;
                    cout << "Podaj x y wartosc: ";
                    cin >> x >> y >> val;
                    A.wstaw(x, y, val);
                    cout << "Wstawiono." << endl;
                    break;
                }
                case 6:
                    A.losuj();
                    cout << "Macierz A wylosowana." << endl;
                    break;
                case 7: {
                    int ile;
                    cout << "Ile elementow wylosowac: ";
                    cin >> ile;
                    A.losuj(ile);
                    cout << "Wylosowano " << ile << " elementow." << endl;
                    break;
                }
                case 8: {
                    string sciezka;
                    cout << "Podaj sciezke do pliku: ";
                    cin >> sciezka;
                    vector<int> dane = wczytajDaneZPliku(sciezka);
                    if (dane.empty()) {
                        cout << "Pusty plik lub blad odczytu." << endl;
                    } else {
                        // Probujemy ustalic wymiar (pierwiastek z ilosci elementow)
                        int rozmiar = static_cast<int>(sqrt(dane.size()));
                        if (rozmiar * rozmiar == static_cast<int>(dane.size())) {
                            matrix Temp(rozmiar, dane.data());
                            A = Temp;
                            cout << "Wczytano macierz " << rozmiar << "x" << rozmiar << endl;
                        } else {
                            cout << "Liczba danych w pliku (" << dane.size() << ") nie tworzy kwadratu!" << endl;
                        }
                    }
                    break;
                }

                // --- Sekcja 3 ---
                case 9: {
                    vector<int> dane = generujDaneTestowe(A.size());
                    A.diagonalna(dane.data());
                    cout << "Wypelniono przekatna." << endl;
                    break;
                }
                case 10: {
                    int k;
                    cout << "Podaj przesuniecie k: ";
                    cin >> k;
                    // Dla uproszczenia generujemy tyle danych ile rozmiar macierzy, 
                    // metoda wezmie tyle ile potrzebuje
                    vector<int> dane = generujDaneTestowe(A.size());
                    A.diagonalna_k(k, dane.data());
                    cout << "Wypelniono przekatna przesunieta o " << k << "." << endl;
                    break;
                }
                case 11: {
                    int x;
                    cout << "Podaj numer kolumny x: ";
                    cin >> x;
                    vector<int> dane = generujDaneTestowe(A.size());
                    A.kolumna(x, dane.data());
                    cout << "Wypelniono kolumne " << x << "." << endl;
                    break;
                }
                case 12: {
                    int y;
                    cout << "Podaj numer wiersza y: ";
                    cin >> y;
                    vector<int> dane = generujDaneTestowe(A.size());
                    A.wiersz(y, dane.data());
                    cout << "Wypelniono wiersz " << y << "." << endl;
                    break;
                }
                case 13:
                    A.dowroc();
                    cout << "Transpozycja wykonana." << endl;
                    break;
                case 14: {
                    cout << "1. Jedynki na przekatnej" << endl;
                    cout << "2. Jedynki pod przekatna" << endl;
                    cout << "3. Jedynki nad przekatna" << endl;
                    cout << "4. Szachownica" << endl;
                    int op;
                    cin >> op;
                    if (op == 1) A.przekatna();
                    else if (op == 2) A.pod_przekatna();
                    else if (op == 3) A.nad_przekatna();
                    else if (op == 4) A.szachownica();
                    cout << "Wzor zastosowany." << endl;
                    break;
                }

                // --- Sekcja 4 ---
                case 15: {
                    cout << "Wynik A + B:" << endl;
                    cout << (A + B) << endl;
                    break;
                }
                case 16: {
                    cout << "Wynik A * B:" << endl;
                    cout << (A * B) << endl;
                    break;
                }

                // --- Sekcja 5 ---
                case 17: {
                    int k;
                    cout << "Podaj k: ";
                    cin >> k;
                    cout << "A + " << k << " =" << endl << (A + k) << endl;
                    cout << k << " + A =" << endl << (k + A) << endl;
                    break;
                }
                case 18: {
                    int k;
                    cout << "Podaj k: ";
                    cin >> k;
                    cout << "A * " << k << " =" << endl << (A * k) << endl;
                    cout << k << " * A =" << endl << (k * A) << endl;
                    break;
                }
                case 19: {
                    int k;
                    cout << "Podaj k: ";
                    cin >> k;
                    cout << "A - " << k << " =" << endl << (A - k) << endl;
                    cout << k << " - A =" << endl << (k - A) << endl;
                    break;
                }
                case 20: {
                    int k;
                    cout << "Podaj k: ";
                    cin >> k;
                    cout << "1. A += k\n2. A -= k\n3. A *= k\nWybor: ";
                    int op;
                    cin >> op;
                    if (op == 1) A += k;
                    else if (op == 2) A -= k;
                    else if (op == 3) A *= k;
                    cout << "Po modyfikacji A:" << endl << A << endl;
                    break;
                }
                case 21: {
                    cout << "1. A++\n2. A--\nWybor: ";
                    int op;
                    cin >> op;
                    if (op == 1) A++;
                    else if (op == 2) A--;
                    cout << "Po modyfikacji A:" << endl << A << endl;
                    break;
                }
                case 22: {
                    double d;
                    cout << "Podaj double d: ";
                    cin >> d;
                    A(d);
                    cout << "Po zastosowaniu funktora A(" << d << "):" << endl << A << endl;
                    break;
                }

                // --- Sekcja 6 ---
                case 23: {
                    cout << "A == B: " << (A == B ? "TAK" : "NIE") << endl;
                    cout << "A > B:  " << (A > B ? "TAK" : "NIE") << endl;
                    cout << "A < B:  " << (A < B ? "TAK" : "NIE") << endl;
                    break;
                }

                // --- Sekcja 7 ---
                case 24:
                    cout << "--- MACIERZ A ---" << endl << A << endl;
                    cout << "--- MACIERZ B ---" << endl << B << endl;
                    break;
                case 25: {
                    string sciezka;
                    cout << "Podaj sciezke zapisu: ";
                    cin >> sciezka;
                    stringstream ss;
                    ss << A; // Konwersja macierzy do stringa
                    zapiszWynikDoPliku(sciezka, ss.str());
                    cout << "Zapisano." << endl;
                    break;
                }
                case 26:
                    testWydajnosci();
                    break;

                default:
                    cout << "Nieznana opcja." << endl;
            }
        } catch (const exception& e) {
            cerr << "\n!!! WYJATEK !!!: " << e.what() << endl;
        }
    }

    return 0;
}
