/* Ostatnia modyfikacja: 09.01.2016
Ostatnio poprawione bledy:
    - bad_alloc <- brak czyszczenia wierzcholkow kryjacych sie pod wskaznikami
    - kazdy wierzcholek W(Presylowy) mogl byc w max. jednym skojarzeniu,
       W(Sciagajacy) w nieskonczonej ilosci skojarzen <- Konczace_krawedzie,
*/
/*
Atrybuty:
    - brak wierzcholka konca/ zastapiono "bool ones"[znacznik czy znaleziono
       nowa "Sciezke Powiekszajaca"], "int id_start"[index W(Sciagajacego)
       z ktorego przyszedl sygnal do 'W(1...1)'],
    - wierzcholek 'W(0...0)' zostal oznaczony jako index "-1"
    - dwie wersje istnienia/ nieistnienia krawedzi: #WERSJA_STD I _ZERO,
      - zrezygnowano ze wsparcia dla _STD,

Puszczenie sygnalu wiaze sie z ustawieniem value= false na wszystkich
 wierz. ktore odwiedzimy, zarowno val. tymczasowe(aktualizowane jako
 doplyw od innych wierzcholkow) jak i bazowe(z ktorym rodza sie
 W(Przesylowe)).
 - Dziala to, poniewaz takie puszczenie sygnalu zawsze konczy sie zmiana
    value[bazowe]= false u tylko jednego W[Przesylowego].

|    - W[Sciagajace] zawsze sciagaja sygnal od W[Przesylowych],
|       czyli W[Przesylowe] beda wysylac sygnal zawsze do get<1>(Son).
|
|    - W[Sciagajace] zawsze wysylaja sygnal do W[Przesylowych],
|       czyli beda wysylac sygnal zawsze do get<1>(Father),
|       - procz id_start[W[Sciagajace]], ktory wirtualnie wysyla sygnal
           do 'W(1...1)'

|    - W(Przesylowe) zawsze wysylaja do get<1>(Son).
|    - W(Przesylowe) czasem beda sciagac sygnal od 'W(0...0)' o id= "-1",
|       wtedy po zmianie value= false konczymy puszczenie sygnalu.
|    - W(Przesylowe) czasem beda sciagac sygnal od W[Sciagajacych].
*/

#include <iostream>
#ifndef GRAF_SKOJARZENIE_H_INCLUDED
#define GRAF_SKOJARZENIE_H_INCLUDED

//*******************************************************
#include <vector>
#include <tuple>

#include <process.h>
#include <windows.h>

//#define STANDARD_SPECIAL //   <- obiekty rozszerzone o niepotrzebne dane
//#define SZESCIO_WATKOWOSC                                         // <- ! zwrace zle wartosci, to trzeba jeszcze poprawic
//#define WERSJA_STD //   <- nie wylosowane krawedzie= (0,0)/          <- ! zrezygnowano ze wsparcia tego pomyslu
#define WERSJA_ZERO //  <- faktycznie nieistniejace krawedzie
//#define WERSJA_KONCZACE_WEKTOR // <- "Konczace_krawedzie" pamietane w "std:: vector<bool>"
#define WERSJA_KONCZACE_TABLICA //  <- "Konczace_krawedzie" pamietane w tablicy pod wskaznikiem "bool*"

//#define TEST_PROGRAMISTY

//*******************************************************
#ifdef SZESCIO_WATKOWOSC//      UWAGA:: 6 watkow!!!
extern HANDLE FastThreadNo2;
extern HANDLE FastThreadNo3;
extern HANDLE FastThreadNo4;
extern HANDLE FastThreadNo5;
extern HANDLE FastThreadNo6;// */
#endif // SZESCIO_WATKOWOSC

//extern int potega_Shared_thread;// <- k
//extern int ilosc_wierzcholkowShared_thread;

//extern long liczba_sc_pow_Shared_thread;
//extern double RandM;
class SkojarzenieWierzcholekSciagajacy_w0;

//*******************************************************
class SkojarzenieWierzcholekPrzesylowy_w0{

/* - nie posiada numeru,
   - wie ile moze cofnac [wekt. Son],

*/
    private:
        bool value;
        std:: vector< std:: tuple<int,bool> > Son;
        bool wsteczny;  // jesli dostalismy od Sciagajacego, to ==1
        int id_doplywu; // czasami ="-1", w innych przypadkach z zalozenia odwoluje sie do W(Sciagajace).
    public:
        #ifdef WERSJA_STD
            /* Konstr. wie ile jest elementow w drugim zbiorze*/
            SkojarzenieWierzcholekPrzesylowy_w0( int moc_sciagajacych );
        #endif // WERSJA_STD
            #ifdef WERSJA_ZERO // - nie potrzebuje ilosci
        SkojarzenieWierzcholekPrzesylowy_w0()
            {value= true;wsteczny= false;id_doplywu= -1;}
        void push_edge_with( int id_sciagajacego )  /* Tworzymy mu krawedz sciagajaca z wierz. sposrod W(Sciagajacych), o id= id_sciagajacego. */
            {Son.push_back( std:: make_tuple( id_sciagajacego,false) );}
            #endif // WERSJA_ZERO
        ~SkojarzenieWierzcholekPrzesylowy_w0()
            {Son.clear();}
/* Metody */
        void FindNewPartner( std:: vector<  /* Musimy miec dostep do pol wierz. Sciagajacych */
             SkojarzenieWierzcholekSciagajacy_w0* >:: iterator Brothers);
        inline bool get_value() /* Inni musza miec mozliwosc zczytania tego pola */
            {return value;}
        std:: tuple<int, bool> Plyn( int id_poprzednika, bool wst_poprzednika);
            /* , zwraca id nastepcy[czasem -1] oraz wlasny wsteczny[jesli jest false, gdy wychodzimy od Przesylowych, to konczymy wysylac sygnal. */

            /* - ustawia swoje value= false[ ! MUSI ! ]                     <- !
               - zwraca id nastepcy (patrz UP ^ ),
               - wlasny wsteczny= X (patrz UP ^ ),
               - wysyla: get<1>(Son)= true,
               - sciaga: get<1>(Son)= false
            */
        inline void Refresh()
            {if( id_doplywu!= -1) value= false;}
};

class SkojarzenieWierzcholekSciagajacy_w0{

/* - nie posiada numeru,
   - nie posiada pola "wsteczny"
   - zawsze sciaga od Przesylowych

|   - potrafimy wyzerowac jego value;

*/
    private:
        bool value;
        std:: vector< std:: tuple<int,bool> > Father;
        int id_doplywu;
    public:
        #ifdef WERSJA_STD
            /* Konstr. wie ile jest elementow w drugim zbiorze*/
            SkojarzenieWierzcholekSciagajacy_w0( int moc_przesylowych );
        #endif // WERSJA_STD
            #ifdef WERSJA_ZERO // - nie potrzebuje ilosci
            /* Ta wersja i tak nic nie tworzy w tym miejscu*/
        SkojarzenieWierzcholekSciagajacy_w0()
            {value= false;}// */
        void push_edge_with( int id_przesylowego )  /* Tworzymy mu krawedz sciagajaca z wierz. sposrod W(Przesylowych), o id= id_przesylowego. */
            {Father.push_back( std:: make_tuple( id_przesylowego,true) );}
            #endif // WERSJA_0
/* Metody */
        inline void Refresh()
            {value= false;}
        void FindNewPartner( std:: vector</* Musimy miec dostep do pol wierz. Sciagajacych */
             SkojarzenieWierzcholekPrzesylowy_w0* >:: iterator Brothers);
        ~SkojarzenieWierzcholekSciagajacy_w0()
            {Father.clear();}

        inline bool get_value() /* Inni musza miec mozliwosc zczytania tego pola */
            {return value;}
        std:: tuple<int, bool> Primal_Flow();
            /* zwraca id_doplywu= X, (ustawia swoje value= false)[Sciagajace nie musza], krawedz z nastepca na 0[bo od niego sciagnal]*/
        std:: tuple<int, bool> Plyn( int id_poprzednika, bool wst_poprzednika);
            /* - zwraca id nastepcy \in {przesylowe}
               - wlasny wsteczny= false[zawsze],
               - wysyla: get<1>(Father)= true,
               - sciaga: get<1>(Father)= false
            */
};

class SkojarzenieGraf_w0{

/* - wierzcholek 0..0 otrzymuje index= "-1"
   - "ones" oznacza nam, czy mamy jeszcze jakas "Sc. Pow.", wspolpracuje z "id_start"
   - wierzcholki realnie dzieli na dwa zbiory[reprezentacja wektorami]
*/
    private:
        int wielkosc;

        bool ones;// pamieta czy cos doplynelo do 1...1
        int id_start;// pamieta skad to cos doplynelo
            #ifdef WERSJA_KONCZACE_TABLICA
        bool *Konczace_krawedzie;
            #endif // WERSJA_KONCZACE_TABLICA
            #ifdef WERSJA_KONCZACE_WEKTOR
        std:: vector< bool > Konczace_krawedzie;/* Inicjowane =true */
            #endif // WERSJA_KONCZACE_WEKTOR

        std:: vector< SkojarzenieWierzcholekPrzesylowy_w0* > Przesylowe;
        std:: vector< SkojarzenieWierzcholekSciagajacy_w0* > Sciagajace;
    public:
            /*
            Wersja_Std: Tworzy wszystkie wierzcholki, ktore od razu maja wektory,
            Wersja_0:   Towrzy puste wierzcholki, sami losujemy dla
                            kazdy-z-kazdym czy istnieje krawedz, jesli
                            tak, to do obu wierzcholkow wywolujemy
                            odpowiednia metode dodajaca odpowiednio
                            skierowana krawedz,
            */

            /* Konstr. wie ile jest elementow w zbiorach*/
        SkojarzenieGraf_w0( int rozmiar );  /* */
        ~ SkojarzenieGraf_w0();
/*
            {
                #ifdef WERSJA_KONCZACE_WEKTOR
            Konczace_krawedzie.clear();
                #endif // WERSJA_KONCZACE_WEKTOR
                #ifdef WERSJA_KONCZACE_TABLICA
            delete[] Konczace_krawedzie;
                #endif // WERSJA_KONCZACE_TABLICA
            Przesylowe.clear();Sciagajace.clear();}
*/

/* Metody */
        void FindMaxAssociation();
};

//*************************************************************
void __cdecl Skojarzenie_partialSymulate( void *dummy );
void Lista1112_Skojarzenie_w0();

#endif // GRAF_SKOJARZENIE_H_INCLUDED
