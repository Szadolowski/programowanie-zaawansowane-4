#include "../include/file_utils.h"
#include <fstream>
#include <iostream>
#include <stdexcept> // do std::runtime_error

std::vector<int> wczytajDaneZPliku(const std::string& sciezka) {
    std::ifstream plik(sciezka);
    
    if (!plik.is_open()) {
        throw std::runtime_error("Blad: Nie mozna otworzyc pliku: " + sciezka);
    }

    std::vector<int> dane;
    int liczba;
    
    // Czytamy liczby tak dlugo, jak sa dostepne w pliku
    while (plik >> liczba) {
        dane.push_back(liczba);
    }

    plik.close();
    
    if (dane.empty()) {
        std::cerr << "Ostrzezenie: Plik " << sciezka << " jest pusty lub nie zawiera liczb!" << std::endl;
    }

    return dane;
}

void zapiszWynikDoPliku(const std::string& sciezka, const std::string& tekst) {
    std::ofstream plik(sciezka, std::ios::app); // std::ios::app - dopisywanie do konca pliku
    
    if (!plik.is_open()) {
        std::cerr << "Blad: Nie mozna zapisac do pliku: " << sciezka << std::endl;
        return;
    }

    plik << tekst << std::endl;
    plik.close();
}