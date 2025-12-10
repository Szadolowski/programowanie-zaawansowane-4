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
    // --- Konstruktory i Destruktor ---

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
    explicit matrix(int n);

    /**
     * @brief Konstruktor inicjalizujacy macierz danymi z tablicy.
     * @param n Wielkosc macierzy.
     * @param t Wskaznik do tablicy z danymi.
     */
    matrix(int n, int* t);

    /**
     * @brief Konstruktor kopiujacy (Deep Copy).
     * Tworzy nowy obiekt i kopiuje do niego zawartosc innej macierzy.
     * @param m Macierz zrodlowa.
     */
    matrix(const matrix& m);

    /**
     * @brief Destruktor.
     * Pamiec zwalniana jest automatycznie przez unique_ptr.
     */
    ~matrix();

    // --- Zarzadzanie Pamiecia i Dostep ---

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

    // --- Operatory Przypisania ---

    /**
     * @brief Operator przypisania kopiujacego (Deep Copy).
     * Obsluguje operacje: A = B.
     * @param m Macierz zrodlowa.
     * @return matrix& Referencja do this.
     */
    matrix& operator=(const matrix& m);

    // --- Metody Logiczne i Wzorce ---

    matrix& losuj();
    matrix& losuj(int ilosc);
    matrix& dowroc(); // Transpozycja
    
    // Wzorce 0/1
    matrix& przekatna();
    matrix& pod_przekatna();
    matrix& nad_przekatna();
    matrix& szachownica();
    
    // Wzorce z tablicy zewnetrznej
    matrix& diagonalna(int* t);
    matrix& diagonalna_k(int k, int* t);
    matrix& kolumna(int x, int* t);
    matrix& wiersz(int y, int* t);

    // --- Operatory Arytmetyczne (Macierz <-> Macierz) ---
    // Zwracamy nowy obiekt przez wartosc

    matrix operator+(const matrix& m) const;
    matrix operator-(const matrix& m) const;
    matrix operator*(const matrix& m) const;

    // --- Operatory Arytmetyczne (Macierz <-> Skalar) ---

    matrix operator+(int a) const;
    matrix operator-(int a) const;
    matrix operator*(int a) const;

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
    friend matrix operator-(int a, const matrix& m);
    friend matrix operator*(int a, const matrix& m);

    /**
     * @brief Operator strumieniowy do wypisywania macierzy.
     */
    friend std::ostream& operator<<(std::ostream& o, const matrix& m);
};