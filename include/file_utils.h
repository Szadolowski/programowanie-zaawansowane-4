#pragma once
#include <string>
#include <vector>

/**
 * @brief Funkcja wczytujaca liczby z pliku tekstowego do wektora.
 * Wektor (std::vector) posluzy nam jako tymczasowy bufor przed
 * utworzeniem wlasciwej macierzy.
 * * @param sciezka Sciezka do pliku (np. "data/dane.txt").
 * @return std::vector<int> Zawartosc pliku jako ciag liczb.
 */
std::vector<int> wczytajDaneZPliku(const std::string& sciezka);

/**
 * @brief Funkcja zapisujaca macierz do pliku (opcjonalnie).
 */
void zapiszWynikDoPliku(const std::string& sciezka, const std::string& tekst);