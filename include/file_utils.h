#pragma once
#include <vector>
#include <string>

// Forward declaration (Zapowiedz klasy)
// Dzieki temu nie musimy robic #include "matrix.h" w tym pliku,
// co przyspiesza kompilacje i zapobiega cyklom zalaczen.
class matrix;

/**
 * @brief Wczytuje ciag liczb z pliku tekstowego do wektora.
 * * @param sciezka Sciezka do pliku (np. "data/dane.txt").
 * @return std::vector<int> Wektor zawierajacy wczytane liczby.
 */
std::vector<int> wczytajDaneZPliku(const std::string& sciezka);

/**
 * @brief Zapisuje sformatowana macierz do pliku tekstowego.
 * * @param sciezka Sciezka do pliku wynikowego.
 * @param m Referencja do macierzy, ktora ma zostac zapisana.
 */
void zapiszMacierzDoPliku(const std::string& sciezka, const matrix& m);