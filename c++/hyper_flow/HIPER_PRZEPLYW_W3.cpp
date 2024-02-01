/* W trakcie pracy do 30.12.2015 */
#include "HIPER_PRZEPLYW_W3.h"

#include <iostream>
#include<vector>
#include<tuple>
#include<string>

#include <cstdlib>// rand(), RAND_MAX
#include <climits>// INT_MAX
#include <algorithm>// min()

#include <cfloat>// DBL_MAX
#include <limits>// DBL_MAX

#include <process.h>
#include <windows.h>

//#define STANDARD_SPECIAL //                                           <- obiekty rozszerzone o niepotrzebne dane

#define SZESCIO_WATKOWOSC               // Bedziemy dzialac na 6 watkach
//#define VALUE_REPREZENTACJA_DOUBLE
#define JEDNO_WYWOLANIE

//#define KONTROLA_BLEDU_230
    // przyczyna bledu: nie generowalismy ojcow i synow po wszystkich
    //  mozliwosciach. kiedy liczba osiagala zero, wychodzilismy
    //  z generowania, a przeciez na miejscu tych zer mozna wstawic
    //  jedynki. Zamieniono warunek z liczba>0 na licznik<dlugosc_ciagu

//#define TEST_PROGRAMISTY

#ifdef SZESCIO_WATKOWOSC//      UWAGA:: 6 watkow!!!
HANDLE FastThreadNo2;
HANDLE FastThreadNo3;
HANDLE FastThreadNo4;// */
HANDLE FastThreadNo5;
HANDLE FastThreadNo6;// */
#endif // SZESCIO_WATKOWOSC

int potega_Shared_thread;
int ilosc_wierzcholkowShared_thread;    // Watki wykonaja kopie
int last_index;
//int ostatni_indexShared_thread;

#ifndef VALUE_REPREZENTACJA_DOUBLE
long HiperPrzeplyw_ZbiorczyShared_thread;// zawsze wspolny
    // pamieta jak duzo udalo sie ostatecznie poscic w 1000 probach calosciowo
#endif // VALUE_REPREZENTACJA_DOUBLE
#ifdef VALUE_REPREZENTACJA_DOUBLE
double HiperPrzeplyw_ZbiorczyShared_thread;// zawsze wspolny
    // pamieta jak duzo udalo sie ostatecznie poscic w 1000 probach calosciowo
#endif // VALUE_REPREZENTACJA_DOUBLE
long liczba_sc_pow_Shared_thread;// zawsze wspolny
    // pamieta jak duzo bylo sciezek pow. w 1000 probach calosciowo
//int k;

double RandM= static_cast<double>(RAND_MAX - 1);

//*****************************************************************
//Koniec preambuly*************************************************

HiperWierzcholek_w3::HiperWierzcholek_w3( int n, int d){
    // Konstruktor Wierzcholka n <- index, d <- dlugosc indexu
    // numer= n; //jest nizej
    dlugosc_numeru= d;

    // dostepny= 0;                         //<- zakladamy ze od razu wywolujemy metode Rebuild
    // wsteczny= false;                     //<- zakladamy ze od razu wywolujemy metode Rebuild

// Stworzymy sobie ojcow i synow do wektorow "Father" i "Son"
    int liczba= numer= n;
    int licznik= 0;

    #ifdef KONTROLA_BLEDU_230
    licznik_kontrolny_synow=0;
    #endif // KONTROLA_BLEDU_230
#ifdef TEST_PROGRAMISTY
        licznik_kontrolny_synow= 0;
        licznik_kontrolny_ojcow= 0;
#endif // TEST_PROGRAMISTY
    while( dlugosc_numeru > licznik ){
        if( (liczba % 2) != 0 ){// ma ojca
            //Father.push_back( std::make_tuple( n-(1<<(licznik++)), 0, n ));//                     <- NIESPRAWDZONA kolejnosc operacji !! 1<<zmienna++ !!
#ifdef STANDARD_SPECIAL
            Father.push_back( std::make_tuple( n^(1<< (licznik++) ), 0, n ));
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
            Father.push_back( std::make_tuple( n^(1<< (licznik++) ), 0 ));
#endif // STANDARD_SPECIAL

#ifdef TEST_PROGRAMISTY
        ++licznik_kontrolny_ojcow;
#endif // TEST_PROGRAMISTY
        }
        else// ma syna
            {
            //Son.push_back( std::make_tuple( n, 0, n+(1<<(licznik++) ) ));
#ifdef STANDARD_SPECIAL
            Son.push_back( std::make_tuple( n, 0, n^(1<<(licznik++) ) ));
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
            Son.push_back( std::make_tuple( n^(1<<(licznik++) ), 0 ));
#endif // STANDARD_SPECIAL

#ifdef TEST_PROGRAMISTY
            ++licznik_kontrolny_synow;
#endif // TEST_PROGRAMISTY
            //Son.push_back( std::make_tuple( n, 0, n^( (int) pow(2, licznik++) ) ));
            #ifdef KONTROLA_BLEDU_230
            ++licznik_kontrolny_synow;
            #endif // KONTROLA_BLEDU_230
            }
        liczba= (liczba>>1);
        //++licznik;
    }

/*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# Wierzcholek ["<< numer<< "] ma ("<< licznik_kontrolny_ojcow<<
            ") ojcow i ("<< licznik_kontrolny_synow<< ") synow.\n";
#endif // TEST_PROGRAMISTY
// Wyswietlamy numer kazdego wierzcholka, ile ma synow i ojcow */
}

HiperWierzcholek_w3:: ~HiperWierzcholek_w3(){
    // Dekonstruktor Wierzcholka
    Father.clear();
    Son.clear();
}
//****************************************************************

void HiperWierzcholek_w3:: Wierzcholek_Rebuild(){

        // Dla kazdej krawedzi z ojcami i synami, tj. dla wektorow
            // Father, Son, losujemy nowa srodkowa wartosc.
    // Skoro jest to dla calych wektorow potrzebujemy iterator

#ifdef STANDARD_SPECIAL
    std:: vector< std:: tuple< int, int, int> >::iterator vec_it;
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL

    #ifndef VALUE_REPREZENTACJA_DOUBLE
    std:: vector< std:: tuple< int, int> >::iterator vec_it;
    #endif // VALUE_REPREZENTACJA_DOUBLE
    #ifdef VALUE_REPREZENTACJA_DOUBLE
    std:: vector< std:: tuple< int, double> >::iterator vec_it;
    #endif // VALUE_REPREZENTACJA_DOUBLE
#endif // STANDARD_SPECIAL

    #ifndef VALUE_REPREZENTACJA_DOUBLE
    for( vec_it= Father.begin(); vec_it != Father.end(); ++vec_it )//{
        std::get <1>(*vec_it)= rand();
            // przeplywy maksymalne/ licznosc tego ile jeszcze moglibysmy
                // z tamtad dostac
    #endif // VALUE_REPREZENTACJA_DOUBLE
    #ifdef VALUE_REPREZENTACJA_DOUBLE
    for( vec_it= Father.begin(); vec_it != Father.end(); ++vec_it )//{
        std::get <1>(*vec_it)= (double)rand() / RandM;
            // przeplywy maksymalne/ licznosc tego ile jeszcze moglibysmy
                // z tamtad dostac
    #endif // VALUE_REPREZENTACJA_DOUBLE

// /*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# Wierzcholek ["<< numer<< "], krawedz z ojcem ["<<
            std:: get <0>(*vec_it)<< "], value= "<< std:: get <1>(*vec_it)<< std:: endl;}
#endif // TEST_PROGRAMISTY
// wyswietlanie wszystkich krawedzi, do kogo nalezy, z kim laczy, po jakiej wartosci */

    for( vec_it= Son.begin(); vec_it != Son.end(); ++vec_it )//{
        std::get <1>(*vec_it)= 0;//rand();
            // przeplywy _rezydualne/ licznosc tego co juz zostalo
                // puszczone

// /*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# Wierzcholek ["<< numer<< "], krawedz z synem ["<<
            std:: get <0>(*vec_it)<< "], value= "<< std:: get <1>(*vec_it)<< std:: endl;}
#endif // TEST_PROGRAMISTY
// */

    // Ustalamy poziom referencyjny.
    //dostepny= 0;//                                                                    <- .Refresh
    //wsteczny= false;
/* jest to wywolywane dla wszystkich wierzcholkow, takze dla pierwszego                 <- chociaz wierzcholek pierwszy nie potrzebuje zerowac synow
// */
}
//  *************************************************************

void HiperWierzcholek_w3:: Primal_Update(){

    // Ustawiamy na wierzcholku 0...0/ ale to jest juz konkretny
        // wierzcholek, wiec musimy wybrac wierzcholek z poziomu kostki
#ifndef VALUE_REPREZENTACJA_DOUBLE
    dostepny= INT_MAX;
#endif // VALUE_REPREZENTACJA_DOUBLE
#ifdef VALUE_REPREZENTACJA_DOUBLE
    dostepny= DBL_MAX;
#endif // VALUE_REPREZENTACJA_DOUBLE
    // wsteczny= false;

/*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# Wierzcholek ["<< numer<< "] ma w polu dostepny= "<<
            dostepny<< std:: endl;
#endif // TEST_PROGRAMISTY
// wywolanie .Kostka_Primal_Update prawidlowo dziala tylko na 1st. */
}
//  HWierzcholek. Primal_Update**********************************

void HiperWierzcholek_w3:: Wierzcholek_MaxBottomFlow(
        std:: vector< // */
        HiperWierzcholek_w3*//*// */
         >::iterator
         //* // */
        Brothers){

// Aktualizujemy pole dostepny, nie dotykamy co bedzie sie zmienialo
// Dla kazdego ojca:


#ifdef STANDARD_SPECIAL
    std:: vector< std:: tuple< int, int, int> >::iterator vec_it;
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL

    #ifndef VALUE_REPREZENTACJA_DOUBLE
    std:: vector< std:: tuple< int, int> >::iterator vec_it;
    #endif // VALUE_REPREZENTACJA_DOUBLE
    #ifdef VALUE_REPREZENTACJA_DOUBLE
    std:: vector< std:: tuple< int, double> >::iterator vec_it;
    #endif // VALUE_REPREZENTACJA_DOUBLE
#endif // STANDARD_SPECIAL
    for( vec_it= Father.begin(); vec_it != Father.end(); ++vec_it ){

        // Sprawdzamy, czy moze on dac nam wiecej niz mamy:
        if( std:: min( (*(Brothers+std::get <0>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it)) //> dostepny
           /* mniejsza wartosc z krawedzi i dostepu ojca*/
           > dostepny){
            dostepny= std:: min( (*(Brothers+std::get <0>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it));
            // zmniejszamy nasza dostepnosc przez ta krawedz
                // Odrzucono:: dostepnosc to tylko propozycja.
                // wagi na krawedziach bedziemy modyfikowac dopiero
                // jak bedziemy pewni przeplywu
            //std:: get <1>(*vec_it)-= min( , get <1>(*vec_it));

            //
            id_doplywu= std:: get <0>(*vec_it);
            //wsteczny= false;
                // niepotrzebne o ile ustawiamy to przy rebuildzie
           }
    }

/*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# Wierzcholek ["<< numer<< "] id_doplywu= "<< id_doplywu<<
                "\t dostepny= "<< dostepny<< std:: endl;
#endif // TEST_PROGRAMISTY
// wyswietla jaki wierzcholek, od jakiego przejal i ile */
}
//  .Wierzcholek_MaxBottomFlow***********************************

void HiperWierzcholek_w3:: Wierzcholek_MaxMixFlow(
        std:: vector< // */
        HiperWierzcholek_w3*//*// */
         >::iterator
         //* // */
        Brothers){

// Aktualizujemy pole dostepny, nie dotykamy co bedzie sie zmienialo

        // Dla kazdego ojca


#ifdef STANDARD_SPECIAL
    std:: vector< std:: tuple< int, int, int> >::iterator vec_it;
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
    #ifndef VALUE_REPREZENTACJA_DOUBLE
    std:: vector< std:: tuple< int, int> >::iterator vec_it;
    #endif // VALUE_REPREZENTACJA_DOUBLE
    #ifdef VALUE_REPREZENTACJA_DOUBLE
    std:: vector< std:: tuple< int, double> >::iterator vec_it;
    #endif // VALUE_REPREZENTACJA_DOUBLE
#endif // STANDARD_SPECIAL
    for( vec_it= Father.begin(); vec_it != Father.end(); ++vec_it ){

        // Sprawdzamy, czy moze on dac nam wiecej niz mamy:
        if( std:: min( (*(Brothers+std::get <0>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it)) //> dostepny
           /* mniejsza wartosc z krawedzi i dostepu ojca*/
           > dostepny){
            dostepny= std:: min( (*(Brothers+std::get <0>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it));
            // zmniejszamy nasza dostepnosc przez ta krawedz
                // Odrzucono:: dostepnosc to tylko propozycja.
                // wagi na krawedziach bedziemy modyfikowac dopiero
                // jak bedziemy pewni przeplywu
            //std:: get <1>(*vec_it)-= min( , get <1>(*vec_it));

            //
            id_doplywu= std:: get <0>(*vec_it);
            wsteczny= false;
                // tutaj juz trzeba, bo to nie jest piewsza metoda
                    // dzialajaca na kraw...
           }
    }
        // Dla kazdego syna
    for( vec_it= Son.begin(); vec_it != Son.end(); ++vec_it ){

        // Sprawdzamy, czy moze on dac nam wiecej niz mamy:

#ifdef STANDARD_SPECIAL
        if( std:: min( (*(Brothers+std::get <2>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it)) //> dostepny
           /* mniejsza wartosc z krawedzi i dostepu syna*/
           > dostepny){
            dostepny= std:: min( (*(Brothers+std::get <2>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it));
            // zmniejszamy nasza dostepnosc przez ta krawedz
                // Odrzucono:: dostepnosc to tylko propozycja.
                // wagi na krawedziach bedziemy modyfikowac dopiero
                // jak bedziemy pewni przeplywu
            //std:: get <1>(*vec_it)-= min( , get <1>(*vec_it));

            //
            id_doplywu= std:: get <2>(*vec_it);
            wsteczny= true;
                // tutaj juz trzeba, ^ UP
           }
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
if( !(std::get <0>(*vec_it)!= last_index)  ) continue;
        if( std:: min( (*(Brothers+std::get <0>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it)) //> dostepny
           /* mniejsza wartosc z krawedzi i dostepu syna*/
           > dostepny){
            dostepny= std:: min( (*(Brothers+std::get <0>(*vec_it)))->get_dostepny() ,
                std:: get <1>(*vec_it));
            id_doplywu= std:: get <0>(*vec_it);
            wsteczny= true;
                // tutaj juz trzeba, ^ UP
           }
#endif // STANDARD_SPECIAL

    }


#ifdef TEST_PROGRAMISTY
std:: cout<< "# Wierzcholek ["<< numer<< "] id_doplywu= "<< id_doplywu<<
                "["<<wsteczny<< "]\tdostepny= "<< dostepny<< std:: endl;
#endif // TEST_PROGRAMISTY
// wyswietla jaki wierzcholek, od jakiego przejal i ile */
}
//  .Wierzcholek_MaxMixFlow**************************************

int HiperWierzcholek_w3:: Plyn_Primal(){

    int licz= 0;

    // Teraz krawedz z ktorej my wzielismy doplyw
    while(true){//wst-0
        if( !(std:: get<0>(Father[licz])!= id_doplywu) ){
                // licz jest indexem w wektorze ojcow
            std:: get<1>(Father[licz])-= dostepny;
    // zwraca index nastepcy
            return id_doplywu;
        }
        ++licz;
    }
}
//  .Plyn_Primal*************************************************

std:: tuple<int, bool> HiperWierzcholek_w3:: Plyn( int id_poprzednika,
        bool wsteczny_poprzednika,
        #ifndef VALUE_REPREZENTACJA_DOUBLE
        int value
        #endif // VALUE_REPREZENTACJA_DOUBLE
        #ifdef VALUE_REPREZENTACJA_DOUBLE
        double value
        #endif // VALUE_REPREZENTACJA_DOUBLE
        ) throw(std::string){

// otzymuje index poprzednika i zwraca index nastepcy oraz bool
//  swojego pola "wsteczny"
    int licz=0;// index kolejnych krawedzi dla petli while

// Czesc wysylajaca
    if( wsteczny_poprzednika ){//p-1
        // to my pamietamy...
        while(true){//                                              <- szukamy odpowiedniej krawedzi
            if( !(std:: get<0>(Father[licz])!= id_poprzednika) ){
                // licz jest indexem w wektorze ojcow
                std:: get<1>(Father[licz])+= value;
                break;
            }
            ++licz;
        }
    }
        else
            while(true){//p-0
#ifdef KONTROLA_BLEDU_230
                if( !(licz < licznik_kontrolny_synow) )
                    throw (std:: string) "Licznik po Synach wyszedl poza zakres" ;

std:: cout<< std:: get<2>(Son[licz])<< std::endl;
#endif // KONTROLA_BLEDU_230

#ifdef STANDARD_SPECIAL
                if( !(std:: get<2>(Son[licz])!= id_poprzednika) ){
                    // licz jest indexem w wektorze synow
                    std:: get<1>(Son[licz])+= value;
                    break;
                }
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
                if( !(std:: get<0>(Son[licz])!= id_poprzednika) ){
                    // licz jest indexem w wektorze synow
                    std:: get<1>(Son[licz])+= value;
                    break;
                }
#endif // STANDARD_SPECIAL
                ++licz;
            }

    licz= 0;

// Czesc sciagajaca sygnal
    if( wsteczny ){//wst-1

        while(true){
            if( !(std:: get<
#ifdef STANDARD_SPECIAL
                            2
#endif // STANDARD_SPECIAL
#ifndef STANDARD_SPECIAL
                            0
#endif // STANDARD_SPECIAL
                                >(Son[licz])!= id_doplywu) ){
                // licz jest indexem w wektorze synow
                std:: get<1>(Son[licz])-= value;
    // zwraca index nastepcy i obecne wsteczny
                return std:: make_tuple( id_doplywu, wsteczny );
            }
            ++licz;
        }
    }
        else
            while(true){//wst-0
                if( !(std:: get<0>(Father[licz])!= id_doplywu) ){
                // licz jest indexem w wektorze ojcow
                std:: get<1>(Father[licz])-= value;
    // zwraca index nastepcy i obecne wsteczny
                return std:: make_tuple( id_doplywu, wsteczny );
                }
                ++licz;
            }
}
//  HWierzcholek .Plyn*******************************************
//Koniec metod dla Wierzcholka***********************************

HiperKostka_w3:: HiperKostka_w3( int k ){
    wielkosc= (1<<k);
    Kostka_DlugoscCiagu= k;
    for( int w=0; w < wielkosc; ++w )
        wsk_wierzcholki.push_back( new HiperWierzcholek_w3( w, k ));
}

HiperKostka_w3:: ~HiperKostka_w3(){
    for( int w=0; w < wielkosc; ++w )
        delete wsk_wierzcholki[w];
    wsk_wierzcholki.clear();
}
//****************************************************************

void HiperKostka_w3:: Kostka_Rebuild(){

        // Dla kazdego wierzcholka wywolujemy metode .Wierzcholek_Refresh
    // Skoro wierzcholki sa pamietane przez wskazniki wewnatrz wektoru,
        // to potrzebujemy iterator
    std:: vector< HiperWierzcholek_w3* >::iterator vec_it;
    for( vec_it= wsk_wierzcholki.begin()+1; vec_it != wsk_wierzcholki.end(); ++vec_it )//       <- zakladamy ze 0...0 nie potrzebuje zerowac synow
        (*vec_it)->Wierzcholek_Rebuild();
        //std::get <1>(*vec_it)= rand();
}
//  Koniec .Kostka_Refresh****************************************

void HiperKostka_w3:: FindMaxFlow() throw(std::string){

// Strategia:
    // Szukamy SCIEZKI POWIEKSZAJACEJ poki sie da:

        // 0.1' zerujemy dostepnosc, ustawiamy wsteczny na false.

        //1' Szukamy na kazdym wierzcholku doplywu tylko z dolu.
            // Dla wierzcholka 0...0 ustawiamy nieograniczony doplyw.
    //wsk_wierzcholki[0]->Primal_Update();//                                                <- nie potrzebujemy za kazdym razem przy tego odswiezac,
                                                                                            // na jednym 0...0 bedziemy dzialac max 170*16 razy

    std:: vector< HiperWierzcholek_w3*>:: iterator vec_it;
while( true ){//                                                <- dopoki istnieje SCIEZKA POW.

        //5' odswiezamy pola dostepny i byc moze dostepny dla
            // wierzcholka 0...0 na INT_MAX.
    for( vec_it= wsk_wierzcholki.begin()+1; vec_it != wsk_wierzcholki.end(); ++vec_it )
        (*vec_it)->Wierzcholek_Refresh();

            // Dla pozostalych wierzcholkow sposrod ojcow wybieramy
                // najlepszy doplyw(warunki!) i zapamietujemy wartosc,
                // indeks tatusia oraz ze przyszedl z dolu= false
    //  std:: vector< HiperWierzcholek_w3*>:: iterator vec_it;
    for( vec_it= wsk_wierzcholki.begin()+1; vec_it != wsk_wierzcholki.end(); ++vec_it )
        (*vec_it)->Wierzcholek_MaxBottomFlow( wsk_wierzcholki.begin() );

        //2' [raz lub (k-2) razy] wykonujemy podobna aktualizacje pola dostepny,
            // tym razem z uwzglednieniem pol od synow (z wektora Son)
            // dla wierzcholkow o indeksach od 1 do przedost. wlacznie

    /*
    for( vec_it= wsk_wierzcholki.begin()+1; vec_it !=
                wsk_wierzcholki.end(); ++vec_it )
            (*vec_it)->Wierzcholek_MaxMixFlow(
                wsk_wierzcholki.begin() );
    // Wersja stara */

if( !((*(--vec_it))->get_dostepny() !=0 ) ){
    // int kKoniec2= Kostka_DlugoscCiagu-2;// w1
    bool zmiana=true;
    for( int ii= 0; ii < Kostka_DlugoscCiagu;/*kKoniec2*/ ++ii  ){//                                                   <-
        if(zmiana){
        for( vec_it= wsk_wierzcholki.end()-2; vec_it !=
                wsk_wierzcholki.begin(); --vec_it ){
            (*vec_it)->Wierzcholek_MaxMixFlow(
                wsk_wierzcholki.begin() );
            //zmiana= false;
        }zmiana= false;}
        else{
        for( vec_it= wsk_wierzcholki.begin()+1; vec_it !=
                wsk_wierzcholki.end(); ++vec_it ){
            (*vec_it)->Wierzcholek_MaxMixFlow(
                wsk_wierzcholki.begin() );
            //zmiana= true;
        }zmiana= true;}

        if( (*(wsk_wierzcholki.end()-1))->get_dostepny() != 0 ) break;
    }
        //3' Mamy naszego kandydata na przeplyw, wiec:
}
    vec_it= wsk_wierzcholki.end() -1;/*[Wersja poprawiona
            (patrz UP ^)]*/


// UWAGA:: WARUNEK:
    // Jesli pole dostepny z Wierzcholka 1...1 == 0, to konczymy
        // prace. Jesli nie, to puszczamy sciezka powiekszajaca:

    //if( (*(--vec_it))->get_dostepny() !=0 ){
    if( (*(vec_it))->get_dostepny() !=0 ){

#ifndef VALUE_REPREZENTACJA_DOUBLE
        int kopia= (*(vec_it))->get_dostepny();
#endif // VALUE_REPREZENTACJA_DOUBLE
#ifdef VALUE_REPREZENTACJA_DOUBLE
        double kopia= (*(vec_it))->get_dostepny();
#endif // VALUE_REPREZENTACJA_DOUBLE
        ++liczba_sc_pow_Shared_thread;  // znaleziono SCIEZKE POW.
        HiperPrzeplyw_ZbiorczyShared_thread+= kopia;

// Zmienne do puszczenia tego konkretnego doplywu
        std:: tuple<int, bool> obecny= std:: make_tuple(
            (*vec_it)->Plyn_Primal(),0); // index wierzcholka nad
            // ktorym pracujemy. Inicjalizowany doplywem do 1...1,
            // i ze 1...1 dostal go od ojca
        int poprzednik= wielkosc-1;
        //bool poprzednik; druga pozycja obecny
        int tmp;

/*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# Index przedostatniego wierzcholka= "<<
            std:: get<0>(obecny)<< std:: endl;
#endif // TEST_PROGRAMISTY
// wyswietlamy index wierzcholka przedostatniego przy inicjalizacji */
//break;}}}/*                                                               <- DOTAD DOBRZE, znalazlo 1000 SC POW dla zwyklego, ale nie dla watkow
// oznaczalo by to, ze sa kostki, w ktorych nie ma zadnej sciezki

        while( std:: get<0>(obecny) != 0 ){

//  Przechodzimy po wszystkich wierzcholkach tego konkretnego dopywu
//      az dojdzeimy do 0...0. Mamy to zagwarantowane, bo kazdy w.
//      przez ktory przejdziemy mowi nam jak isc dalej
            tmp= std:: get<0>(obecny);
//break;}break;}}}/*                                                               <- DOTAD DOBRZE

#ifdef TEST_PROGRAMISTY
if ( (tmp<0) or (tmp>= wielkosc) )
    throw (std:: string)"#ERROR: obecny poza zakresem";
#endif // TEST_PROGRAMISTY
            obecny= wsk_wierzcholki[tmp]->Plyn(
                poprzednik, std:: get<1>(obecny), kopia );
            poprzednik= tmp;//int

/*
#ifdef TEST_PROGRAMISTY
std:: cout<< "# obecny= "<< std:: get<0>(obecny)<< std:: endl;
#endif // TEST_PROGRAMISTY
// wyswietla przed'przedostatni index */

//}break;}}}/*
        }
// BLAD:*********************************************************************************************************************************
//wsk_wierzcholki[0]->Plyn(poprzednik, 1, kopia );//                                    <- OSTATNI BLAD,
//                                              tak samo jak dla 1...1, jesli chcemy kazac my plynac, to nalezy zrobic oddzielna funckje.
//                                              potrafimy obsluzyc poprzednika, czyli aktualizowac krawedz z synem, potrafimy zwrocic
//                                              losowy adres nastepcy, bo i tak nie bedzie uzywany, ale druga cz. aktualizacji jest
//                                              obsluga nastepcy, a tego nie ma... i to tu wlasnie najprawd. sie wywalal
// BLAD ^********************************************************************************************************************************
        //  dla 0 petla konczy prace, wiec oddzielnie wywolujemy

        //4' odswiezamy pola dostepny i byc moze dostepny dla
            // wierzcholka 0...0 na INT_MAX.
    }
        else
            break;

    }
}// */
//  .FindMaxFlow**************************************************
//Koniec metod dla kostki*****************************************

void __cdecl HiperPrzeplyw_partialSymulate( void *dummy ){
    HiperKostka_w3 G_thread( potega_Shared_thread );

    G_thread.Kostka_Primal_Update();//                                                 <- tylko raz nadajemy 0...0 nieograniczony dostep

        // Wykonujemy kolejne symulacje w ilosci, ktora nam przypadla w udziale
    for ( int t_thread=0; t_thread <
    #ifndef SZESCIO_WATKOWOSC
    250
    #endif // SZESCIO_WATKOWOSC
    #ifdef SZESCIO_WATKOWOSC
    166
    #endif // SZESCIO_WATKOWOSC
    ; ++t_thread){

// Nadajemy nowe wagi na krawedziach poczatkowych oraz
    //zerujemy te na rezydualnych
        G_thread.Kostka_Rebuild();
        //G.Kostka_Primal_Update();//
        G_thread.FindMaxFlow();
    }// Symulacje w ilosci ktora nam przypadla
}
//  Funkcja pomocnicza obslugujaca watki dla Lista910...**********

void Lista910_HiperPrzeplyw_w3(){

        #ifndef JEDNO_WYWOLANIE
    for ( potega_Shared_thread=3; potega_Shared_thread < 17; ++potega_Shared_thread ){// k<17
        #endif // JEDNO_WYWOLANIE
        #ifdef JEDNO_WYWOLANIE
        potega_Shared_thread= 10;
        last_index= (1<<potega_Shared_thread)-1;
        #endif // JEDNO_WYWOLANIE

        HiperPrzeplyw_ZbiorczyShared_thread= 0;
            // dla tego k mamy wyzerowany calosciowy przeplyw
        liczba_sc_pow_Shared_thread= 0;
        #ifdef SZESCIO_WATKOWOSC
        FastThreadNo2= (HANDLE) _beginthread( HiperPrzeplyw_partialSymulate, 0, NULL);
        FastThreadNo3= (HANDLE) _beginthread( HiperPrzeplyw_partialSymulate, 0, NULL);
        FastThreadNo4= (HANDLE) _beginthread( HiperPrzeplyw_partialSymulate, 0, NULL);
        FastThreadNo5= (HANDLE) _beginthread( HiperPrzeplyw_partialSymulate, 0, NULL);
        FastThreadNo6= (HANDLE) _beginthread( HiperPrzeplyw_partialSymulate, 0, NULL);
        #endif // SZESCIO_WATKOWOSC

            // Strategia szybkiej symulacji:: dla ustalonego k tworzymy
                // tylko jedna kostke i ja nadpisujemy
        HiperKostka_w3 G( potega_Shared_thread );

        G.Kostka_Primal_Update();//                                                 <- tylko raz nadajemy 0...0 nieograniczony dostep

            // Wykonujemy kolejne symulacje w ilosci, ktora nam przypadla w udziale
        for ( int t=0; t <
        #ifndef SZESCIO_WATKOWOSC
        1000
        #endif // SZESCIO_WATKOWOSC
        #ifdef SZESCIO_WATKOWOSC
        170
        #endif // SZESCIO_WATKOWOSC
        ; ++t){
            // Nadajemy nowe wagi na krawedziach poczatkowych oraz
                //zerujemy te na rezydualnych
        G.Kostka_Rebuild();

            //G.Kostka_Primal_Update();//
G.FindMaxFlow();

        }// Symulacje w ilosci ktora nam przypadla
//                                                               <- DOTAD DOBRZE
        #ifdef SZESCIO_WATKOWOSC
        WaitForSingleObject( FastThreadNo2, INFINITE );
        WaitForSingleObject( FastThreadNo3, INFINITE );
        WaitForSingleObject( FastThreadNo4, INFINITE );
        WaitForSingleObject( FastThreadNo5, INFINITE );
        WaitForSingleObject( FastThreadNo6, INFINITE );
        #endif // SZESCIO_WATKOWOSC

#ifndef VALUE_REPREZENTACJA_DOUBLE
        std::cout<< "\tPrzeplyw sr: "<< static_cast<double>(HiperPrzeplyw_ZbiorczyShared_thread)
            /RandM / 1000<< "\tSr. liczba sc.pow: "<< (double)liczba_sc_pow_Shared_thread / 1000<< "\tG( 2^ "
            << potega_Shared_thread<< " )\n";
#endif // VALUE_REPREZENTACJA_DOUBLE
#ifdef VALUE_REPREZENTACJA_DOUBLE
        std::cout<< "\tPrzeplyw sr: "<< HiperPrzeplyw_ZbiorczyShared_thread/ 1000<< "\tSr. liczba sc.pow: "<<
            (double)liczba_sc_pow_Shared_thread / 1000<< "\tG( 2^ "
            << potega_Shared_thread<< " )\n";
#endif // VALUE_REPREZENTACJA_DOUBLE

        #ifndef JEDNO_WYWOLANIE
    }// dla kazdego 'k'
        #endif // JEDNO_WYWOLANIE

}// Funkcja Lista910...

// */
