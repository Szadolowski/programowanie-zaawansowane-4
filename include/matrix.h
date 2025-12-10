#pragma once

#include <iostream>
#include <memory>    // Tutaj znajduje sie unique_ptr
#include <stdexcept> // Do obslugi bledow (wyjatki)

/**
 * @brief Klasa reprezentujaca kwadratowa macierz liczb calkowitych.
 * Zarzadzanie pamiecia oparte jest na std::unique_ptr.
 */
class matrix {
private:
    int n;                        ///< Wymiar macierzy (n x n)
    std::unique_ptr<int[]> data;  ///< Inteligentny wskaznik do tablicy danych

    /**
     * @brief Prywatna metoda pomocnicza do bezpiecznego dostepu do danych.
     * Przelicza wspolrzedne 2D (x, y) na indeks 1D w tablicy.
     * @param x Kolumna
     * @param y Wiersz
     * @return Referencja do elementu tablicy.
     */
    int& at(int x, int y);

    /**
     * @brief Wersja const metody at() dla obiektow tylko do odczytu.
     */
    int at(int x, int y) const;

public:
    // --- Konstruktory i Destruktor ---

    /**
     * @brief Konstruktor domyslny. Nie alokuje pamieci (n=0).
     */
    matrix();

    /**
     * @brief Konstruktor alokujacy macierz o wymiarze n x n.
     * @param n Wielkosc macierzy.
     */
    explicit matrix(int n);

    /**
     * @brief Konstruktor inicjalizujacy macierz danymi z tablicy.
     * @param n Wielkosc macierzy.
     * @param t Wskaznik do tablicy z danymi.
     */
    matrix(int n, int* t);

    /**
     * @brief Konstruktor kopiujacy.
     * Wykonuje GLEBOKA KOPIE (Deep Copy) danych, poniewaz unique_ptr nie jest kopiowalny.
     * @param m Macierz wzorcowa.
     */
    matrix(const matrix& m);

    /**
     * @brief Destruktor.
     * Pamiec zwalniana jest automatycznie przez unique_ptr.
     */
    ~matrix();

    // --- Metody Logiczne i Modyfikujace ---

    /**
     * @brief Alokuje pamiec dla macierzy.
     * Jesli rozmiar jest inny niz obecny, zwalnia stara pamiec i alokuje nowa.
     */
    matrix& alokuj(int n);

    /**
     * @brief Wstawia wartosc w podane miejsce.
     */
    matrix& wstaw(int x, int y, int wartosc);

    /**
     * @brief Zwraca wartosc elementu na pozycji (x, y).
     */
    int pokaz(int x, int y) const;

    /**
     * @brief Transponuje macierz (zamienia wiersze z kolumnami).
     */
    matrix& dowroc();

    /**
     * @brief Wypelnia macierz losowymi liczbami 0-9.
     */
    matrix& losuj();

    /**
     * @brief Wstawia x losowych cyfr w losowe miejsca macierzy.
     */
    matrix& losuj(int x);

    /**
     * @brief Wstawia dane z tablicy na przekatna (reszta 0).
     */
    matrix& diagonalna(int* t);

    /**
     * @brief Wstawia dane na przekatna przesunieta o k.
     */
    matrix& diagonalna_k(int k, int* t);

    /**
     * @brief Przepisuje dane z tabeli do kolumny x.
     */
    matrix& kolumna(int x, int* t);

    /**
     * @brief Przepisuje dane z tabeli do wiersza y.
     */
    matrix& wiersz(int y, int* t);

    /**
     * @brief Macierz jednostkowa (1 na przekatnej, reszta 0).
     */
    matrix& przekatna();

    /**
     * @brief Trojkatna dolna (1 pod przekatna).
     */
    matrix& pod_przekatna();

    /**
     * @brief Trojkatna gorna (1 nad przekatna).
     */
    matrix& nad_przekatna();

    /**
     * @brief Wypelnia macierz wzorem szachownicy (0101...).
     */
    matrix& szachownica();

    // --- Operatory Arytmetyczne ---
    // Zwracamy nowy obiekt (przez wartosc), nie referencje, aby uniknac bledow pamieci.

    matrix operator+(const matrix& m) const;
    matrix operator-(const matrix& m) const; // Dodalem odejmowanie dla kompletu
    matrix operator*(const matrix& m) const;
    
    matrix operator+(int a) const;
    matrix operator*(int a) const;
    matrix operator-(int a) const;

    // --- Operatory Modyfikujace (zwracaja *this) ---

    matrix& operator++(int);   // Postfiks A++
    matrix& operator--(int);   // Postfiks A--
    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);
    
    /**
     * @brief Funktor: Powieksza wszystkie elementy o czesc calkowita z double.
     */
    matrix& operator()(double a);

    // --- Operatory Porownania ---

    bool operator==(const matrix& m) const;
    bool operator>(const matrix& m) const;
    bool operator<(const matrix& m) const;

    // --- Funkcje Zaprzyjaznione (Friends) ---
    // Pozwalaja na operacje typu: 5 + A (gdzie int jest po lewej stronie)

    friend matrix operator+(int a, const matrix& m);
    friend matrix operator*(int a, const matrix& m);
    friend matrix operator-(int a, const matrix& m);

    /**
     * @brief Operator strumieniowy do wypisywania macierzy.
     */
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);

    // Getter pomocniczy
    int size() const { return n; }
};