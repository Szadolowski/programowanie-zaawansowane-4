#pragma once
#include <memory>
#include <iostream>

/**
 * @brief Klasa reprezentujaca macierz kwadratowa.
 * * Klasa zarzadza pamiecia dynamiczna przy uzyciu inteligentnego wskaznika
 * std::unique_ptr. Przechowuje dane w tablicy jednowymiarowej.
 */
class matrix {
private:
    int n;                        ///< Wymiar macierzy (ilosc wierszy i kolumn)
    std::unique_ptr<int[]> data;  ///< Wskaznik do tablicy przechowujacej dane

    /**
     * @brief Metoda pomocnicza do bezpiecznego dostepu do elementow.
     * * Sprawdza, czy indeksy mieszcza sie w zakresie macierzy.
     * Rzuca wyjatek std::out_of_range w przypadku bledu.
     * * @param x Numer kolumny (0..n-1)
     * @param y Numer wiersza (0..n-1)
     * @return int& Referencja do elementu macierzy
     */
    int& at(int x, int y);

    /**
     * @brief Wersja const metody at() dla obiektow tylko do odczytu.
     * * @param x Numer kolumny
     * @param y Numer wiersza
     * @return int Wartosc elementu
     */
    int at(int x, int y) const;

public:
    /**
     * @brief Konstruktor domyslny.
     * Tworzy pusta macierz o rozmiarze 0.
     */
    matrix();

    /**
     * @brief Konstruktor alokujacy pamiec.
     * Tworzy macierz o wymiarach n x n wypelniona zerami.
     * * @param n Zadana wielkosc macierzy.
     */
    matrix(int n);

    /**
     * @brief Destruktor.
     * Pamiec zwalniana jest automatycznie przez unique_ptr.
     */
    ~matrix();

    /**
     * @brief Alokuje pamiec dla macierzy.
     * * Jesli macierz nie ma pamieci -> alokuje.
     * Jesli ma inna wielkosc -> realokuje.
     * Jesli ma te sama wielkosc -> nie robi nic (optymalizacja).
     * * @param n Nowy wymiar macierzy.
     * @return matrix& Referencja do biezacego obiektu.
     */
    matrix& alokuj(int n);

    /**
     * @brief Wstawia wartosc do macierzy.
     * * @param x Numer kolumny.
     * @param y Numer wiersza.
     * @param wartosc Liczba do wstawienia.
     * @return matrix& Referencja do biezacego obiektu (umozliwia lancuchowanie).
     */
    matrix& wstaw(int x, int y, int wartosc);

    /**
     * @brief Pobiera wartosc z macierzy.
     * * @param x Numer kolumny.
     * @param y Numer wiersza.
     * @return int Wartosc komorki.
     */
    int pokaz(int x, int y) const;

    /**
     * @brief Zwraca aktualny rozmiar macierzy.
     * @return int Wymiar n.
     */
    int size() const;

    
};