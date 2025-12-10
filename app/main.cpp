#include <iostream>
#include <fstream> // Potrzebne do utworzenia pliku testowego w locie
#include "../include/matrix.h"
#include "../include/file_utils.h"
#include <filesystem> // C++17 standard

using namespace std;

int main() {
    // --- DIAGNOSTYKA ŚCIEŻKI ---
    std::cout << "Katalog roboczy programu: " << std::filesystem::current_path() << std::endl;
    std::cout << "Czy folder 'data' istnieje tu?: " << (std::filesystem::exists("data") ? "TAK" : "NIE") << std::endl;
    // ---------------------------

    matrix A;
    matrix B;
    // ... reszta kodu ...
    cout << "=== TEST 9: OBSLUGA PLIKOW ===" << endl;

    // KROK 1: Przygotowanie danych (Symulacja pliku wejsciowego)
    // Tworzymy plik 'data/test_input.txt' z samymi liczbami
    string sciezkaWej = "../data/test_input.txt";
    string sciezkaWyj = "../data/test_output.txt";

    {
        ofstream plik(sciezkaWej);
        if (plik.is_open()) {
            plik << "10 20 30 40 50 60 70 80 90"; // Dane dla macierzy 3x3
            plik.close();
            cout << "[1] Stworzono plik testowy: " << sciezkaWej << endl;
        } else {
            cout << "[BLAD] Nie udalo sie stworzyc pliku testowego w folderze data/!" << endl;
            return 1;
        }
    }

    // KROK 2: Odczyt danych z pliku
    cout << "[2] Proba odczytu..." << endl;
    try {
        vector<int> dane = wczytajDaneZPliku(sciezkaWej);
        
        // Sprawdzamy czy mamy wystarczajaco danych na macierz 3x3
        if (dane.size() == 9) {
            matrix A(3, dane.data()); // Tworzymy macierz z wektora
            cout << "Wczytano poprawnie do macierzy A:\n" << A;

            // KROK 3: Zapis sformatowany
            cout << "[3] Zapisuje wynik do " << sciezkaWyj << "..." << endl;
            zapiszMacierzDoPliku(sciezkaWyj, A);
            cout << "Gotowe. Sprawdz folder data/!" << endl;

        } else {
            cout << "[BLAD] Wczytano " << dane.size() << " liczb, a oczekiwano 9." << endl;
        }

    } catch (const exception& e) {
        cout << "[WYJATEK] " << e.what() << endl;
    }

    cout << "\n=== TEST 10: FINAŁ (WYDAJNOSC n=30) ===" << endl;
    try {
        cout << "1. Alokacja dwoch macierzy 30x30..." << endl;
        matrix BigA(30);
        matrix BigB(30);

        cout << "2. Losowanie danych..." << endl;
        BigA.losuj();
        BigB.szachownica(); // Dla urozmaicenia

        cout << "3. Mnozenie (moze chwilke potrwac)..." << endl;
        matrix BigC = BigA * BigB;

        cout << "4. Wynik (fragment 5x5):" << endl;
        // Pokazujemy tylko fragment, zeby nie zasmiecic konsoli
        for(int y=0; y<5; ++y) {
            for(int x=0; x<5; ++x) {
                cout << BigC.pokaz(x, y) << "\t";
            }
            cout << "..." << endl;
        }
        cout << "[SUKCES] Operacje na duzych macierzach zakonczone." << endl;

    } catch (const exception& e) {
        cout << "[BLAD KRYTYCZNY] " << e.what() << endl;
    }

    cout << "\nProgram zakonczony. Nacisnij Enter, aby zamknac okno...";
    
    // Wyczyszczenie bufora (na wypadek gdyby cos tam zostalo po ostatnim cin)
    cin.clear();
    cin.ignore(1000, '\n'); 
    
    // Czekanie na znak
    cin.get(); 

    return 0;
}