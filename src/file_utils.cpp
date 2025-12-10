#include "../include/file_utils.h"
#include "../include/matrix.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

// Funkcja wczytujaca surowe liczby z pliku do wektora
std::vector<int> wczytajDaneZPliku(const std::string& sciezka) {
    std::ifstream plik(sciezka);
    
    if (!plik.is_open()) {
        throw std::runtime_error("Blad: Nie mozna otworzyc pliku do odczytu: " + sciezka);
    }

    std::vector<int> dane;
    int liczba;
    
    // Czytamy liczby tak dlugo, jak sa w strumieniu
    while (plik >> liczba) {
        dane.push_back(liczba);
    }

    plik.close();
    
    if (dane.empty()) {
        std::cerr << "Ostrzezenie: Plik " << sciezka << " jest pusty lub nie zawiera liczb!" << std::endl;
    }

    return dane;
}

// Funkcja zapisujaca sformatowana macierz do pliku
void zapiszMacierzDoPliku(const std::string& sciezka, const matrix& m) {
    std::ofstream plik(sciezka); // Domyslnie tryb truncate (nadpisuje plik)
    
    if (!plik.is_open()) {
        throw std::runtime_error("Blad: Nie mozna otworzyc pliku do zapisu: " + sciezka);
    }

    // Wykorzystujemy nasz friend operator<< zdefiniowany w matrix_core.cpp
    // Dzieki temu w pliku bedzie ladna tabelka z ramkami | |
    plik << m;

    plik.close();
    std::cout << "Sukces: Zapisano macierz do pliku " << sciezka << std::endl;
}