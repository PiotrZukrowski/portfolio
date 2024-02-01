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

#include <iostream>// std:: cout
#include "GRAF_SKOJARZENIE.h"

//*******************************************************
#include <process.h>
#include <windows.h>

#include <math.h>// pow()

//#define STANDARD_SPECIAL //   <- obiekty rozszerzone o niepotrzebne dane
//#define SZESCIO_WATKOWOSC                                         // <- ! zwrace zle wartosci, to trzeba jeszcze poprawic
//#define WERSJA_STD //   <- nie wylosowane krawedzie= (0,0)/          <- ! zrezygnowano ze wsparcia tego pomyslu
#define WERSJA_ZERO //  <- faktycznie nieistniejace krawedzie
//#define JEDNO_WYWOLANIE //    <- mozliwosc wywolania dla pojedynczo ustalonego k,i[ustawiane recznie w F[Lista1112...]
//#define WERSJA_KONCZACE_WEKTOR // <- "Konczace_krawedzie" pamietane w "std:: vector<bool>"
#define WERSJA_KONCZACE_TABLICA //  <- "Konczace_krawedzie" pamietane w tablicy pod wskaznikiem "bool*"

//#define TEST_PROGRAMISTY


//*******************************************************
#ifdef SZESCIO_WATKOWOSC//      UWAGA:: 6 watkow!!!
HANDLE FastThreadNo2;
HANDLE FastThreadNo3;
HANDLE FastThreadNo4;// */
HANDLE FastThreadNo5;
HANDLE FastThreadNo6;// */
#endif // SZESCIO_WATKOWOSC

int potega_Shared_thread;// <- k
//int ilosc_wierzcholkowShared_thread;    // Watki wykonaja kopie

long liczba_sc_pow_Shared_thread;// zawsze wspolny

double prawd;// <- 2^(-i)
//  Koniec zmiennych globalnych*************************

#ifdef WERSJA_STD
SkojarzenieWierzcholekPrzesylowy_w0::
    SkojarzenieWierzcholekPrzesylowy_w0( int moc_sciagajacych ){

        /* Kiedy wPrzesylowy sie rodzi, ma na sobie wartosc 1*/
    value= true;
        /* Decydujemy, czy mamy krawedz z kazdym mozliwym synem,
        Wersja_Std: krawedz istnieje w wektorze, ale ma w= (0,0),
        Wersja_0:   krawedz jest dodawana tylko, jesli istnieje
        */
    for( int i=0; i < moc_sciagajacych; ++i )
/* przesylowy zawsze jest inicjowany z synem "0", bo to krawedz powrotu*/        //Son.push_back( std:: make_tuple( i,rand()>granica_prawd_rand ? true:false) )
        Son.push_back( std:: make_tuple( i,false ) )
    wstaczny= false;

        /* wierzcholek 0..0 otrzymuje index= "-1" */
    id_doplywu= -1;
}
#endif // WERSJA_STD
// SkWierzPrzesylowy_w0()*******************************

/*
#ifdef WERSJA_STD
SkojarzenieWierzcholekPrzesylowy_w0::
    ~SkojarzenieWierzcholekPrzesylowy_w0(){

}
// ~SkWierzPrzesylowy_w0()****************************** */

#ifdef WERSJA_STD
SkojarzenieWierzcholekSciagajacy_w0::
    SkojarzenieWierzcholekSciagajacy_w0( int moc_przesylowych ){

        /* Kiedy wSciagajacy sie rodzi, nie ma wartosci*/
    //value= false;   // - najprawdopodobniej bedziemy i tak najpierw nadawac

        /* Decydujemy, czy mamy krawedz z kazdym mozliwym ojcem,
        Wersja_Std: krawedz istnieje w wektorze, ale ma w= (0,0),
        Wersja_0:   krawedz jest dodawana tylko, jesli istnieje
        */
    for( int i=0; i < moc_przesylowych; ++i )
        Father.push_back( std:: make_tuple( i,
            rand()>granica_prawd_rand ? true:false) )

    wstaczny= false;    // byc moze posiada to pole, byc moze nie
        /* nie potrzebuje tego pola bo zawsze sciaga z dolu*/
    //id_doplywu= nieznane;
}
#endif // WERSJA_STD
// SkWierzSciagajacy_w0()*******************************

/*
SkojarzenieWierzcholekSciagajacy_w0::
    ~SkojarzenieWierzcholekSciagajacy_w0(){

}
// ~SkWierzSciagajacy_w0()******************************/

/*
#ifdef WERSJA_ZERO
void SkojarzenieWierzcholekPrzesylowy_w0:: push_edge_with( int id_sciagajacego ){

    Son.push_back( make_tuple( id_sciagajacego,0) );
}
// SkWierzPrzes .push_edge_with()***********************

void SkojarzenieWierzcholekSciagajacy_w0:: push_edge_with( int id_przesylowego ){

}
// SkWierzSciag .push_edge_with()***********************
#endif // WERSJA_ZERO */

void SkojarzenieWierzcholekSciagajacy_w0:: FindNewPartner( std::
    vector< SkojarzenieWierzcholekPrzesylowy_w0* >:: iterator Brothers){

    /* Aktualizujemy pole value, zakladamy ze jest= false */
    std:: vector< std:: tuple< int, bool> >::iterator vec_it;
    for( vec_it= Father.begin(); vec_it != Father.end(); ++vec_it ){
        /* Sprawdzamy, czy poprawia on nasza sytuacje.
           - rownowazne z tym, ze na krawedzi i u ojca jest true*/
        if( (std:: get<1>(*vec_it) == true)and((*(Brothers+std::get <0>
                (*vec_it)))->get_value() == true)){
            value= true;
            id_doplywu= std:: get <0>(*vec_it);

            break;                                              // <- !
                /* Jak polepszylismy sytuacje to wychodzimy */
        }
    }
}
// SkWierzSciagajacy .FindNewPartner********************

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SkojarzenieWierzcholekPrzesylowy_w0:: FindNewPartner( std::
    vector< SkojarzenieWierzcholekSciagajacy_w0* >:: iterator Brothers){

    /* Aktualizujemy pole value, zakladamy ze jest= false */
    std:: vector< std:: tuple< int, bool> >::iterator vec_it;
    for( vec_it= Son.begin(); vec_it != Son.end(); ++vec_it ){
        /* Sprawdzamy, czy poprawia on nasza sytuacje.
           - rownowazne z tym, ze na krawedzi i u syna jest true*/
        if( (std:: get<1>(*vec_it) == true)and((*(Brothers+std::get <0>
                (*vec_it)))->get_value() == true) ){
            value= true;
            id_doplywu= std:: get <0>(*vec_it);

            break;                                              // <- !
                /* Jak polepszylismy sytuacje to wychodzimy */
        }
    }
}
// SkWierzSciagajacy .FindNewPartner********************

std:: tuple<int, bool> SkojarzenieWierzcholekSciagajacy_w0:: Primal_Flow(){

    /* zwraca id_doplywu, ustawia swoje value= false,
        krawedz z nastepca na 0
    */
    value= false;                                                   // <- ! raczej niepotrzebne
    int licz= 0;

    // Teraz krawedz z ktorej my wzielismy doplyw
    while(true){//wst-0
        if( !(std:: get<0>(Father[licz])!= id_doplywu) ){
                // licz jest indexem w wektorze ojcow
            std:: get<1>(Father[licz])= false;
    // zwraca index nastepcy
            return std:: make_tuple(id_doplywu, false);
        }
        ++licz;
    }
}
// Primal_Flow******************************************                <- ! return

std:: tuple<int, bool> SkojarzenieWierzcholekPrzesylowy_w0:: Plyn
    ( int id_poprzednika, bool wst_poprzednika){
    /* zwraca id nastepcy oraz wlasny wsteczny */

    int licz=0;// index kolejnych krawedzi dla petli while

// Czesc wysylajaca                                                 <- ! zawsze po synach
            while(true){//p-0
                if( !(std:: get<0>(Son[licz])!= id_poprzednika) ){
                    // licz jest indexem w wektorze synow
                    std:: get<1>(Son[licz])= true;
                    break;
                }
                ++licz;
            }

    licz= 0;

// Czesc sciagajaca sygnal
    if( wsteczny ){//wst-1

        while(true){
            if( !(std:: get<0>(Son[licz])!= id_doplywu) ){
                // licz jest indexem w wektorze synow
                std:: get<1>(Son[licz])-= false;
    // zwraca index nastepcy i obecne wsteczny
                return std:: make_tuple( id_doplywu, wsteczny );
            }
            ++licz;
        }
    }
        else return std:: make_tuple( -1, false );
            /* jezeli z przesylowego dostalismy z dolu, to musi byc tak */

            /*
            while(true){//wst-0
                if( !(std:: get<0>(Father[licz])!= id_doplywu) ){
                // licz jest indexem w wektorze ojcow
                std:: get<1>(Father[licz])-= value;
    // zwraca index nastepcy i obecne wsteczny
                return std:: make_tuple( id_doplywu, wsteczny );
                }
                ++licz;
            }// */
}
std:: tuple<int, bool> SkojarzenieWierzcholekSciagajacy_w0:: Plyn
    ( int id_poprzednika, bool wst_poprzednika){
            /* zwraca id nastepcy oraz wlasny wsteczny */

    int licz=0;// index kolejnych krawedzi dla petli while

// Czesc wysylajaca                                                 <- zawsze po ojcach
    /*if( wsteczny_poprzednika ){*///p-1
        // to my pamietamy...
        while(true){//                                              <- szukamy odpowiedniej krawedzi
            if( !(std:: get<0>(Father[licz])!= id_poprzednika) ){
                // licz jest indexem w wektorze ojcow
                std:: get<1>(Father[licz])= true;
                break;
            }
            ++licz;
        }
    //}

    licz= 0;

// Czesc sciagajaca sygnal                                          <- zawsze po ojcach
    while(true){//wst-0
        if( !(std:: get<0>(Father[licz])!= id_doplywu) ){
            // licz jest indexem w wektorze ojcow
            std:: get<1>(Father[licz])= false;
    // zwraca index nastepcy i obecne wsteczny
                return std:: make_tuple( id_doplywu, false/*wsteczny*/ );
        }                                                       // <- !
        ++licz;
    }
}

/*
|   // Koniec czesci poswieconej Wierzcholkom***************
*/

//#ifdef WERSJA_STD
SkojarzenieGraf_w0:: SkojarzenieGraf_w0( int rozmiar ){

    /* W wersji _STD do wektorow wierzcholkow tworzymy kolejne wierzcholki i one juz posiadaja odpowiednie krawedzie. */
    wielkosc= rozmiar;
        #ifdef WERSJA_KONCZACE_TABLICA
    Konczace_krawedzie= new bool[rozmiar];
        #endif // WERSJA_KONCZACE_TABLICA
    for( int i=0; i< rozmiar; ++i){
        Przesylowe.push_back( new SkojarzenieWierzcholekPrzesylowy_w0() );
        Sciagajace.push_back( new SkojarzenieWierzcholekSciagajacy_w0() );
            #ifdef WERSJA_KONCZACE_TABLICA
        Konczace_krawedzie[i]= true;
            #endif // WERSJA_KONCZACE_TABLICA
            #ifdef WERSJA_KONCZACE_WEKTOR
        Konczace_krawedzie.push_back( true );
            #endif // WERSJA_KONCZACE_WEKTOR
    }

    /* W wersji _ZERO po kazdy-z-kazdym losujemy czy krawedz
        wystapi i wywolujemy dla obu rozwazanych wierzcholkow
        odpowiednie metody dodajace krawedz.
    */
#ifdef WERSJA_ZERO

    for( int i=0; i < rozmiar; ++i){
        for( int ii=0; ii < rozmiar; ++ii){

            if( rand()<prawd ? true:false ){
                Przesylowe[i]->push_edge_with( ii );
                Sciagajace[ii]->push_edge_with( i );
            }
        }
    }
#endif // WERSJA_ZERO
}
//#endif // WERSJA_STD

/*
#ifdef WERSJA_ZERO
SkojarzenieGraf_w0:: SkojarzenieGraf_w0( int rozmiar ){

     W wersji _ZERO po kazdy-z-kazdym losujemy czy krawedz
        wystapi i wywolujemy dla obu rozwazanych wierzcholkowdo
        odpowiednie metody dodajace krawedz.

    for( int i=0; i < rozmiar; ++i){
        for( int ii=0; ii < rozmiar; ++ii){

            if( rand()>granica_prawd_rand ? true:false ){

            }
        }
    }
}
#endif // WERSJA_ZERO
*/

SkojarzenieGraf_w0:: ~SkojarzenieGraf_w0(){

        #ifdef WERSJA_KONCZACE_WEKTOR
    Konczace_krawedzie.clear();// */
        #endif // WERSJA_KONCZACE_WEKTOR
        #ifdef WERSJA_KONCZACE_TABLICA
    delete[] Konczace_krawedzie;// */
        #endif // WERSJA_KONCZACE_TABLICA

/* Zanim wyczyscimy wektory z WSKAZNIKOW! mosimy usunac to,
    co jest po wskaznikami (a to one sa elementami wektorow)
*/
    for( int i=0; i < wielkosc; ++i){
        delete Przesylowe[i];
        delete Sciagajace[i];
    }
    Przesylowe.clear();
    Sciagajace.clear();
}

void SkojarzenieGraf_w0:: FindMaxAssociation(){

/* Strategia:

    #szukanie nowej sciazki:
    - zerujemy Sciagajace
    - szukamy najlepszego doplywu
    - szukamy oddzielnie dl 1...1
*/
    int licznik;
    std:: vector< SkojarzenieWierzcholekSciagajacy_w0* >:: iterator vec_it_sciag;
    std:: vector< SkojarzenieWierzcholekPrzesylowy_w0* >:: iterator vec_it_przes;
    while(true){

        ones= false; /* Szukamy nowej "Sciazki Powiekszajacej" */
        for( vec_it_przes= Przesylowe.begin(); vec_it_przes != Przesylowe.end(); ++vec_it_przes )
            (*vec_it_przes)->Refresh();
        for( vec_it_sciag= Sciagajace.begin(); vec_it_sciag != Sciagajace.end(); ++vec_it_sciag )
            {(*vec_it_sciag)->Refresh();
            (*vec_it_sciag)->FindNewPartner( Przesylowe.begin() );}
/* Mamy szanse na Sc. Pow. */
        /*for( vec_it= Sciagajace.begin(); vec_it != Sciagajace.end(); ++vec_it ){
            if( (*vec_it)->get_value() == false )
                (*vec_it)->FindNewPartner( Przesylowe.begin() );
        }// */
//std:: cout<< "jestem\n";
        licznik= 0;
        for( vec_it_sciag= Sciagajace.begin(); vec_it_sciag != Sciagajace.end(); ++vec_it_sciag, ++licznik )
            //if( ((*vec_it_sciag)->get_value() == true) and Konczace_krawedzie[licznik] ){
            if( (*vec_it_sciag)->get_value() and Konczace_krawedzie[licznik] ){
                ones= true;
                id_start= licznik;
                break;                                     // <- !
            }
//std:: cout<< "jestem\n";
/* Jezeli nadal ones= false*/
        if( !ones ){// ones == true
            bool zmiana= true;
            for( int i=0; i < wielkosc; ++i ){/* krotnosc*/
                if(zmiana){
                    for( vec_it_przes= Przesylowe.begin(); vec_it_przes !=
                        Przesylowe.end(); ++vec_it_przes )            // <- ! usunieto klamre
                            //if( (*vec_it_przes)->get_value() == false )
                            if( !((*vec_it_przes)->get_value()) )
(*vec_it_przes)->FindNewPartner( Sciagajace.begin() );
                    //zmiana= false;
                    zmiana= false;}
                else{
                    for( vec_it_sciag= Sciagajace.begin(); vec_it_sciag !=
                        Sciagajace.end(); ++vec_it_sciag )
                            //if( (*vec_it_sciag)->get_value() == false )
                            if( !((*vec_it_sciag)->get_value()) )
(*vec_it_sciag)->FindNewPartner( Przesylowe.begin() );
                            //zmiana= true;
                        //}
/* sprawdzamy czy udalo sie znalezc doplyw do 1...1 */
        licznik= 0;
        for( vec_it_sciag= Sciagajace.begin(); vec_it_sciag != Sciagajace.end(); ++vec_it_sciag, ++licznik )
            //if( ((*vec_it_sciag)->get_value() == true)and Konczace_krawedzie[licznik] ){
            if( (*vec_it_sciag)->get_value() and Konczace_krawedzie[licznik] ){
                ones= true;
                id_start= licznik;
                break;                                     // <- !
            }
                    zmiana= true;
                    }
//std:: cout<< "Jestem\n";
    /* O ile udalo nam sie znalezc doplyw do 1...1 */
            if( ones == true ) break;
            }
        }// if( ones==false) mixuj
/* Jezeli mozemy powiekszyc przeplyw: */
if( ones== true){
//std:: cout<< "eo\n";
    ++liczba_sc_pow_Shared_thread;  // znaleziono SCIEZKE POW.

    int tmp;
    /* Specjalne wywolanie */
    std:: tuple<int, bool> obecny= Sciagajace[id_start]->Primal_Flow();
//std:: cout<< id_start<< std:: endl;
    Konczace_krawedzie[id_start]= false;
    int poprzednik= id_start;
    bool zmiana= false;
    while( true/*std:: get<0>(obecny) != -1*/ ){
        tmp= std:: get<0>(obecny);
        if(zmiana){
        obecny= Sciagajace[tmp]->Plyn(
                poprzednik, std:: get<1>(obecny) );
        }else{
        obecny= Przesylowe[tmp]->Plyn(
                poprzednik, std:: get<1>(obecny) );
            if( !(std:: get<0>(obecny) != -1) ) break;      // <- !
        }
        poprzednik= tmp;//int
    }
        }// koniec powiekszania o pojedynczy przeplyw
    else break;
    }
}
// SkGraf_w0 .FindMaxAssociation()************************

/*
|   // Koniec czesci poswieconej Grafowi**********************
*/

void __cdecl Skojarzenie_partialSymulate( void *dummy ){

    // Wykonujemy kolejne symulacje w ilosci, ktora nam przypadla w udziale
    for ( int t_thread=0; t_thread <
    #ifndef SZESCIO_WATKOWOSC
    250
    #endif // SZESCIO_WATKOWOSC
    #ifdef SZESCIO_WATKOWOSC
    166
    #endif // SZESCIO_WATKOWOSC
    ; ++t_thread){

        SkojarzenieGraf_w0 G_thread( 1<<potega_Shared_thread );
        G_thread.FindMaxAssociation();
    }// Symulacje w ilosci ktora nam przypadla
}
// Skojarzenie_partialSymulate()**************************

void Lista1112_Skojarzenie_w0(){

/* - "potega_Shared_thread" dostepna globalnie,
   - "prawd" dostepne globalnie
*/
 try{
        #ifndef JEDNO_WYWOLANIE
    for ( potega_Shared_thread=3; potega_Shared_thread < 11; ++potega_Shared_thread ){// k<11
     for( int i=0; i< potega_Shared_thread + 1; ++i){
        #endif // JEDNO_WYWOLANIE
        #ifdef JEDNO_WYWOLANIE
        potega_Shared_thread= 3;
        int i=0;
        //last_index= (1<<potega_Shared_thread)-1;
        #endif // JEDNO_WYWOLANIE

        liczba_sc_pow_Shared_thread= 0;
        prawd= pow( 2, (-i) ) * RAND_MAX;
        #ifdef SZESCIO_WATKOWOSC
        FastThreadNo2= (HANDLE) _beginthread( Skojarzenie_partialSymulate, 0, NULL);
        FastThreadNo3= (HANDLE) _beginthread( Skojarzenie_partialSymulate, 0, NULL);
        FastThreadNo4= (HANDLE) _beginthread( Skojarzenie_partialSymulate, 0, NULL);
        FastThreadNo5= (HANDLE) _beginthread( Skojarzenie_partialSymulate, 0, NULL);
        FastThreadNo6= (HANDLE) _beginthread( Skojarzenie_partialSymulate, 0, NULL);
        #endif // SZESCIO_WATKOWOSC

            // Strategia szybkiej symulacji:: dla ustalonego k tworzymy tylko jeden graf i go nadpisujemy, |-> tylko dla wersji _STD, dla _ZERO istnieja inne krawed, a struktura grafu jest tozsama z rozwiazaniem
        #ifdef WERSJA_STD
        SkojarzenieGraf_w0 G( 1<<potega_Shared_thread );
        #endif // WERSJA_STD

        for ( int t=0; t <
        #ifndef SZESCIO_WATKOWOSC
        1000
        #endif // SZESCIO_WATKOWOSC
        #ifdef SZESCIO_WATKOWOSC
        170
        #endif // SZESCIO_WATKOWOSC
        ; ++t){
//std:: cout<< "New\n";
            #ifdef WERSJA_ZERO
            SkojarzenieGraf_w0 G( 1<<potega_Shared_thread );
            #endif // WERSJA_ZERO
            G.FindMaxAssociation();

//std:: cout<< t<< std:: endl;
        }
//std:: cout<< "Jestem\n";
        #ifdef SZESCIO_WATKOWOSC
        WaitForSingleObject( FastThreadNo2, INFINITE );
        WaitForSingleObject( FastThreadNo3, INFINITE );
        WaitForSingleObject( FastThreadNo4, INFINITE );
        WaitForSingleObject( FastThreadNo5, INFINITE );
        WaitForSingleObject( FastThreadNo6, INFINITE );
        #endif // SZESCIO_WATKOWOSC

        std:: cout<< "\tSr. Skojarzenie: "<< (double)liczba_sc_pow_Shared_thread
            / 1000<< "\tG( 2^"<< potega_Shared_thread<< ", 2^(-"<<
             i<< ") )\n";

        #ifndef JEDNO_WYWOLANIE
     }
    std:: cout<< std:: endl<< std:: endl;
    }// dla kazdego 'k'
        #endif // JEDNO_WYWOLANIE

 }
 catch(std:: bad_alloc){
    std:: cout<< "Przechwycona nieudana rezerwacja pamieci !!!"<< std:: endl;
 }
}
// Lista1112_Skojarzenie_w0()*****************************
