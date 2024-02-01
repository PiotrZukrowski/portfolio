#ifndef HIPER_PRZEPLYW_W3_H_INCLUDED
#define HIPER_PRZEPLYW_W3_H_INCLUDED

#include <vector>
#include <tuple>
#include<string>
//*******************************************************
#include <process.h>
#include <windows.h>

//#define STANDARD_SPECIAL //                                           <- obiekty rozszerzone o niepotrzebne dane
#define SZESCIO_WATKOWOSC
//#define VALUE_REPREZENTACJA_DOUBLE

//#define KONTROLA_BLEDU_230
//#define TEST_PROGRAMISTY

#ifdef SZESCIO_WATKOWOSC//      UWAGA:: 6 watkow!!!
extern HANDLE FastThreadNo2;
extern HANDLE FastThreadNo3;
extern HANDLE FastThreadNo4;
extern HANDLE FastThreadNo5;
extern HANDLE FastThreadNo6;// */
#endif // SZESCIO_WATKOWOSC

extern int potega_Shared_thread;
extern int ilosc_wierzcholkowShared_thread;

    #ifndef VALUE_REPREZENTACJA_DOUBLE
extern long HiperPrzeplyw_ZbiorczyShared_thread;
    #endif // VALUE_REPREZENTACJA_DOUBLE
    #ifdef VALUE_REPREZENTACJA_DOUBLE
extern double HiperPrzeplyw_ZbiorczyShared_thread;
    #endif // VALUE_REPREZENTACJA_DOUBLE
extern long liczba_sc_pow_Shared_thread;
extern double RandM;

class HiperWierzcholek_w3{
    private:

// Wierzcholek posiada:
//1' numer.
//2' dlugosc ciagu
//3' indeksy wierzcholkow od ktorych moze otrzymac doplyw,
//   jaka jest aktualna pojemnosc takiej krawedzi;

//   dwa oddzielne obiekty(wectory)
        int numer;
            // uzywam kiedy chce przekazac wstecznie kolejnemu
                // dokad ma wyslac doplyw.
        int dlugosc_numeru;     // Dlugosc ciagu reprezentacji numeru
            // jest niezbedna do wygenerowania wszystkich synow

#ifdef STANDARD_SPECIAL
        std:: vector< std:: tuple< int, int, int> >Father;//            <- krawedzie inicjujace
        std:: vector< std:: tuple< int, int, int> >Son;//               <- cofanie przeplywu
                                // pocz., v., kon.
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
    #ifndef VALUE_REPREZENTACJA_DOUBLE
        std:: vector< std:: tuple< int, int> >Father;//            <- krawedzie inicjujace
        std:: vector< std:: tuple< int, int> >Son;//               <- cofanie przeplywu
    #endif // VALUE_REPREZENTACJA_DOUBLE
    #ifdef VALUE_REPREZENTACJA_DOUBLE
        std:: vector< std:: tuple< int, double> >Father;//            <- krawedzie inicjujace
        std:: vector< std:: tuple< int, double> >Son;//               <- cofanie przeplywu
    #endif // VALUE_REPREZENTACJA_DOUBLE
#endif // STANDARD_SPECIAL

        #ifdef KONTROLA_BLEDU_230
        int licznik_kontrolny_synow;
        #endif // KONTROLA_BLEDU_230
#ifdef TEST_PROGRAMISTY
        int licznik_kontrolny_synow;
        int licznik_kontrolny_ojcow;
#endif // TEST_PROGRAMISTY

#ifndef VALUE_REPREZENTACJA_DOUBLE
        int dostepny;           // Wartosc dostepnego przeplywu
#endif // VALUE_REPREZENTACJA_DOUBLE
#ifdef VALUE_REPREZENTACJA_DOUBLE
        double dostepny;           // Wartosc dostepnego przeplywu
#endif // VALUE_REPREZENTACJA_DOUBLE
        int id_doplywu;
        bool wsteczny;          // Czy dostepny pochodzi od syna
    public:
        HiperWierzcholek_w3( int n, int d);
        ~HiperWierzcholek_w3();

        void Wierzcholek_Rebuild();    // f. pomocnicza, nadaje nowe,
            // losowe wartosci na ojcach i zeruje synow
        void Primal_Update();   // f. pomocnicza, ustawia maksymalny
            // doplyw do wierzcholka 0...0; (dostepny= INT_MAX).
            // ODRZUCONY:: zamieniamy na ustaw _dowolny na max.

        void Wierzcholek_Refresh(/* dostepny */)
            {dostepny= 0;wsteczny= false;}

        void Wierzcholek_MaxBottomFlow(
                std:: vector< // */
                HiperWierzcholek_w3*//*// */
                >:: iterator
                //*
                Brothers);// */
                // wskaznik(adres) na pierwszy wskaznik

        void Wierzcholek_MaxMixFlow(
                std:: vector< // */
                HiperWierzcholek_w3*//*// */
                >:: iterator
                //*
                Brothers);// */
#ifndef VALUE_REPREZENTACJA_DOUBLE
        inline int get_dostepny()
            {return dostepny;}
#endif // VALUE_REPREZENTACJA_DOUBLE
#ifdef VALUE_REPREZENTACJA_DOUBLE
        inline double get_dostepny()
            {return dostepny;}
#endif // VALUE_REPREZENTACJA_DOUBLE
        inline bool get_wsteczny()
            {return wsteczny;}
        std:: tuple<int, bool> Plyn( int id_poprzednika,
            bool wsteczny_poprzednika,
                    #ifndef VALUE_REPREZENTACJA_DOUBLE
            int value
                #endif // VALUE_REPREZENTACJA_DOUBLE
                #ifdef VALUE_REPREZENTACJA_DOUBLE
            double value
                #endif // VALUE_REPREZENTACJA_DOUBLE
            ) throw(std::string);
            // zwraca index nastepcy i obecne wsteczny

        int Plyn_Primal();
};

class HiperKostka_w3{
    private:
        int wielkosc;
        int Kostka_DlugoscCiagu;
        std:: vector< HiperWierzcholek_w3* > wsk_wierzcholki;
    public:
        HiperKostka_w3( int k );// dlugosc ciagow
        ~HiperKostka_w3();

        void Kostka_Rebuild();         // f. pomocnicza
            // daje nowa kostke w miejscu starej

        inline void Kostka_Primal_Update()
            {wsk_wierzcholki[0]->Primal_Update();}
        void FindMaxFlow() throw(std::string);     // funkcja COMBO
};

//*************************************************************
void __cdecl HiperPrzeplyw_partialSymulate( void *dummy );
void Lista910_HiperPrzeplyw_w3();

#endif // HIPER_PRZEPLYW_W3_H_INCLUDED
