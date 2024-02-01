#ifndef KOSTKA_RUBIKA_2015_H_INCLUDED
#define KOSTKA_RUBIKA_2015_H_INCLUDED
#include <iostream>
#include <fstream>
#include <conio.h>
#include<string>


int i, j;
char k;
char TabRuch[12] = {'U','L','F','R','B','D','u','l','f','r','b','d'};

class Scianka{
  private:
    char *Tab;                          // Wyglad chwilowy obiektu
    const char KolorSrodka;             // Identyfikacja posrednia obiektu
  public:
    Scianka(char kolor) throw(char);                // Dynamiczna alokacja dla tablicy
    ~Scianka();

    void ObrotC();                      // Obrot zgodny ze wskazowek zegar
    void ObrotAC();                     // Obrot przeciwny do ruchu wskaz.

    void Wypisz();
    void Wypisz(int wiersz) throw(int);

    void Set(int i,char k) throw(int, char);             // Ingerencja w scianke 'z boku'
    char Get(int i) throw(int);
    friend void Obrot(Scianka &A,int a1,int a2,int a3,Scianka &B,int b1,int b2,int b3,Scianka &C,int c1,int c2,int c3,Scianka &D,int d1,int d2,int d3) throw(std::string);
    // A[ai]=>B[bi]=>C[ci]=>D[di]=>A[ai]
};
//*****************************************************************

class Kostka{
  private:
    Scianka Up,Left,Front,Right,Back,Down;      // Glowne elementy obiektu
  public:
    Kostka();
    Kostka(char* NazwaPliku) throw(std::string, char);
    void U();               // OBROT Gornej SCIANKI zgodnie z ruchem wskaz
    void u();               // OBROT Gornej SCIANKI przeciwnie do wskazow
    void L();               //np: X.L()
    void l();
    void F();
    void f();
    void R();
    void r();
    void B();
    void b();
    void D();
    void d();
    void Wypisz();          // ... SIATKE KOSTKI
    bool CzyUlozona();      // Wieszczka poprawnosci STANU obiektu
    void Ruch(char c) throw(char);      // FUNKCJA POMOCNICZA:
                                // skladaja sie na nia powyzsze metody;
                                // char c jest kodem metody
                                //np: X.Ruch(L); oznacza X.L();
    void Wymieszaj(int n);
    void Uloz(int n);
};
//*****************************************************************

void Wymieszaj(Kostka A, int n);

void Test1();
void Test2();
void Zabawa1();
void Zad7_2();
void TestUloz();
void TestWczytaj();
void UlozZPliku();

#endif // KOSTKA_RUBIKA_2015_H_INCLUDED
