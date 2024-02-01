/* W trakcie pracy do 30.12.2015 */

/* Aktualne prace:

    wyciagnac throw'y (if'y)
*/

#include <iostream>
#include "HIPER_PRZEPLYW_W3.h"

#include <cstdlib>
// #include <stdlib>
#include <ctime>
using namespace std;

int main()
{
    srand( time(NULL) );
    try{

/*
    HiperKostka_w3 T( 5 );
    T.Kostka_Primal_Update();
    T.Kostka_Rebuild();
    T.FindMaxFlow();
// */
    Lista910_HiperPrzeplyw_w3();
    }
    catch(string b){
        cout<< b<< endl;
    }
    return 0;
}
/* Modyfikacje:
    - wykonuje dla k od 3 do 16.
    - pojemnosc kazdej krawedzi: calkowita
      od 0 do RAND_MAX.

    - HKostka poprzez konstruktor dostaje
      dlugosc ciagu.
      - zapamietuje dlugosc ciagu
      - sama sobie liczy rozmiar i zapamietuje
      - tworzy wektor wierzcholkow w dobrej ilosci

    1'Tworzymy HKostke dla ustalonego k.
      - wierzcholki dostaja swoj numer i
        dlugosc ciagu

      HWierzcholek w momecie stworzenia
      - zapamietuje dlugosc ciagu                   <- mozna zmienic zeby kazdy obiekt z projektu wylacznie czytal ta wartosc (zal: operacja atomowa)
      - nie podstawia pola dostepny             <- zakladamy ze od razu wywolujemy metode Rebuild
      - nie podstawia pola wsteczny             <- zakladamy ze od razu wywolujemy metode Rebuild
                                                                        <- moglibysmy juz w momencie stworzenia nadac losowa wartosc krawedzi, bo przy
                                                                           tworzeniu wywolujemy .push_back
                                                                           - wtedy rebuild idzie na koniec?

    2'Metoda Rebuild
      - nada nowe losowe wartosci
        ojcom
      - wyzeruje synow
        //zrobi to Refresh - wyzeruje pola dostepny
        //zrobi ot Refresh - pole wsteczny na false
    - wszystkim procz pierwszego

    3'Kazemy HKostce znalezc sobie maxFlow
      - dla kazdego wierzcholka od 1st:

        - .Refresh

        - sprawdzamy kazdego ojca:
          - min( krawedzi z nim, jego dost.)
        - az mamy najlepszy dostepny i adres
          skad przyszedl
      - ponownie, k-2 razy kazdemu wierzholkowi
        liczbym MixFlow

    4'Jezeli uzyskalismy na 1...1 pole dost.>0
      - zapamietujemy kopie tej wartosci
      - zwiekszamy wspolny licznik SCIEZ. POW.
      - zwiekszamy maksymalny przeplyw

      - kazdemu wierzcholkowi SCIEZKI POW.
        aktualizujemy wartosci krawedzi

*/
/* Program ma na celu wyznaczyc maksymalny
    przeplyw z wierzcholka 0...0 do 1...1.
    Kazdy wierzcholek bedzie znal
    - wartosc najwiekszego _pojedynczego i
        tylko pojedynczego przeplywu,
    ktory moze do niego doplynac od poczatku,

    - index wierzcholka z ktorego on przyjdzie
    oraz czy przeplyw przyjdzie z wierzcholka
    wyzej czy nizej. Wierzcholki beda ponadto
    znaly indexy swoich synow i ojcow, swoje
    aktualne przeplywy z nimi /maksymalne/
    oraz rezydualne.

    Program szuka najlepszego pojedynczego
    przeplywu, modyfikuje wartosci na krawedziach,
    odswieza pola 'dostepny' tak dluga jak
    istnieje taka SCIAZKA POW.
*/
