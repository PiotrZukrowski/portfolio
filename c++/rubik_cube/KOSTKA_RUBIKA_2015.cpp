#include "KOSTKA_RUBIKA_2015.h"
#include <iostream>
#include<string>
#include<stdlib.h>     /* exit, EXIT_FAILURE */
#include<time.h>

//#define SAMA_SCIANKA 1    // 'cout<< endl;' po wypisaniu wiersza w (Scianka) X.Wypisz(int i);
#define KOSTKA 1            // 'cout<< " ";' po wypisaniu wiersza w (Scianka) X.Wypisz(int i)
//#define TEST2 1              // INFORMUJE o obrotach
//#define KONTROLA_PROGRAMU 1
#define KONTROLA_WCZYTANIA 1
#define ZABAWA_KAZDY_RUCH 1
#define STD 1
using namespace std;

/*class Scianka{
  private:
    char *Tab;                          // Wyglad chwilowy obiektu
    const char KolorSrodka;             // Identyfikacja posrednia obiektu
  public:
    Scianka(char kolor);                // Dynamiczna alokacja dla tablicy
    ~Scianka();

    void ObrotC();                      // Obrot zgodny ze wskazowek zegar
    void ObrotAC();                     // Obrot przeciwny do ruchu wskaz.

    void Wypisz();
    void Wypisz(int wiersz);

    void Set(int i,char k);
    char Get(int i);
    friend void Obrot(Scianka &A,int a1,int a2,int a3,Scianka &B,int b1,int b2,int b3,Scianka &C,int c1,int c2,int c3,Scianka &D,int d1,int d2,int d3);
    // A[ai]=>B[bi]=>C[ci]=>D[di]=>A[ai]
};
class Kostka{
  private:
    Scianka Up,Left,Front,Right,Back,Down;      // Glowne elementy obiektu
  public:
    Kostka();
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
    void Ruch(char c);      // FUNKCJA POMOCNICZA:
                                // skladaja sie na nia powyzsze metody;
                                // char c jest kodem metody
                                //np: X.Ruch(L); oznacza X.L();
};// */

Scianka::Scianka(char kolor)throw (char):KolorSrodka(kolor){
    if (kolor!='W' and kolor!='R' and kolor!='B' and
        kolor!='O' and kolor!='G' and kolor!='Y')
        throw(kolor);
    Tab= new char[8];
    //KolorSrodka= kolor;
    for (int i=0; i<8; i++)
    {
        Tab[i]= kolor;
    }
}
//*******************************************************************

Scianka::~Scianka(){
    delete []Tab;
}
//*******************************************************************

void Scianka::ObrotC()
{
    char kopia[8];
    for (int i=0; i<8; i++)
    {
        kopia[i]= Tab[i];
    }

    for (int i=0; i<8; i++)
    {
        Tab[i]= kopia[(i+6)%8];
    }
}
//********************************************************************

void Scianka::ObrotAC(){
    char kopia[8];
    for (int i=0; i<8; i++){
        kopia[i]= Tab[i];
    }

    for (int i=0; i<8; i++){
        Tab[i]= kopia[(i+2)%8];
    }
}
//********************************************************************

void Scianka::Wypisz()
{
    cout<< Tab[0]<< " "<< Tab[1]<< " "<< Tab[2]<< endl;
    cout<< Tab[7]<< " "<< KolorSrodka<< " "<< Tab[3]<< endl;
    cout<< Tab[6]<< " "<< Tab[5]<< " "<< Tab[4]<< endl;
}
//********************************************************************

void Scianka::Wypisz(int wiersz)
 throw(int){
    if (3<wiersz or wiersz<1)
        throw(wiersz);
    switch (wiersz){
    case 1:
        cout<< Tab[0]<< " "<< Tab[1]<< " "<< Tab[2];
        #ifdef SAMA_SCIANKA
        cout<< endl;
        #endif // SAMA_SCIANKA

        #ifdef KOSTKA
        cout<< " ";
        #endif // KOSTKA
        break;
    case 2:
        cout<< Tab[7]<< " "<< KolorSrodka<< " "<< Tab[3];
        #ifdef SAMA_SCIANKA
        cout<< endl;
        #endif // SAMA_SCIANKA

        #ifdef KOSTKA
        cout<< " ";
        #endif // KOSTKA
        break;
    case 3:
        cout<< Tab[6]<< " "<< Tab[5]<< " "<< Tab[4];
        #ifdef SAMA_SCIANKA
        cout<< endl;
        #endif // SAMA_SCIANKA

        #ifdef KOSTKA
        cout<< " ";
        #endif // KOSTKA
        break;
    }
}
//*********************************************************************

void Obrot(Scianka &A,int a1,int a2,int a3,Scianka &B,int b1,int b2,int b3,Scianka &C,int c1,int c2,int c3,Scianka &D,int d1,int d2,int d3)
throw(string){
    if(7<a1 or a1<0 or 7<a2 or a2<0 or 7<a3 or a3<0 or
       7<b1 or b1<0 or 7<b2 or b2<0 or 7<b3 or b3<0 or
       7<c1 or c1<0 or 7<c2 or c2<0 or 7<c3 or c3<0)
        throw string("Argument pola liczby w Obrocie jest z poza zakresu.");
    k= D.Tab[d1];
    D.Tab[d1]= C.Tab[c1]; C.Tab[c1]= B.Tab[b1]; B.Tab[b1]= A.Tab[a1]; A.Tab[a1]= k;
    k= D.Tab[d2];
    D.Tab[d2]= C.Tab[c2]; C.Tab[c2]= B.Tab[b2]; B.Tab[b2]= A.Tab[a2]; A.Tab[a2]= k;
    k= D.Tab[d3];
    D.Tab[d3]= C.Tab[c3]; C.Tab[c3]= B.Tab[b3]; B.Tab[b3]= A.Tab[a3]; A.Tab[a3]= k;
}
//*********************************************************************

void Scianka::Set(int pole, char znak)
throw(int, char){
    #ifdef STD
    if (7<pole or pole<0)
        throw(pole);
    if (znak!='W' and znak!='R' and
        znak!='B' and
        znak!='O' and znak!='G' and znak!='Y')
        throw(znak);
    Tab[pole]= znak;
    #endif // STD
    #ifndef STD
    if (7<pole or pole<(-1))
        throw(pole);
    /*if (znak!='W' and znak!='R' and
        znak!='B' and
        znak!='O' and znak!='G' and znak!='Y')
        throw(znak); // */
    if (pole = (-1))
        KolorSrodka= znak;
    else
        Tab[pole]= znak;
    #endif // STD
}
//*********************************************************************

char Scianka::Get(int pole) // Need add #error
throw(int){
    if (pole!=(-1) and (7<pole or pole<0))
        throw(pole);
    if ((pole > (-1)) and (pole < 8)) return Tab[pole];
    else if (pole == (-1)) return KolorSrodka;  // throw to wyrzucil
    else{
        cout<< " !#!#!# Blad danych Funkcji Scianka::Get(...) !#!#!#"<< endl;
        return 'a';
    }
}
//*********************************************************************

void Test1()
{
    cout<< "### Procedura Test1 rozpoczyna prace."<< endl;
    Scianka AA('A'), BB('B'), CC('C'), DD('D'), ZZ('Z');
    cout<< "### Stworzono piec obiektow:"<< endl;
    cout<< endl<< "Scianka AA:"<< endl;
    AA.Wypisz();

    cout<< endl<< "Scianka BB:"<< endl;
    BB.Wypisz();

    cout<< endl<< "Scianka CC:"<< endl;
    CC.Wypisz();

    cout<< endl<< "Scianka DD:"<< endl;
    DD.Wypisz();

    cout<< endl<< "Scianka ZZ:"<< endl;
    ZZ.Wypisz();
    //*****************************************************
    cout<< "### Funkcja ZZ.Set(...)"<< endl;
    ZZ.Set(0, 'E');
    ZZ.Set(1, 'F');
    ZZ.Set(2, 'G');
    ZZ.Set(3, 'H');
    ZZ.Set(4, 'I');
    ZZ.Set(5, 'J');
    ZZ.Set(6, 'K');
    ZZ.Set(7, 'L');
    cout<< "     ZAKONCZONA SUKCESEM"<< endl;
    ZZ.Wypisz();
    //*****************************************************
    cout<< "### USTAWIAM pozostale pola z wszystkich kostek ###"<< endl;
    AA.Set(6, 'U');   // Scianka Gorna
    AA.Set(5, 'W');
    AA.Set(4, 'X');
    BB.Set(0, 'A');   // Scianka Prawa
    BB.Set(7, 'B');
    BB.Set(6, 'C');
    CC.Set(0, 'M');   // Scianka Dolna
    CC.Set(1, 'N');
    CC.Set(2, 'O');
    DD.Set(2, 'Y');   // Scianka Lewa
    DD.Set(3, 'Q');
    DD.Set(4, 'V');

    cout<< "   Wyglad scianek po ustawieniu:"<< endl;
    cout<< endl<< "Scianka AA:   (Gorna)"<< endl;
    AA.Wypisz();

    cout<< endl<< "Scianka BB:   (Prawa)"<< endl;
    BB.Wypisz();

    cout<< endl<< "Scianka CC:   (Dolna)"<< endl;
    CC.Wypisz();

    cout<< endl<< "Scianka DD:   (Lewa)"<< endl;
    DD.Wypisz();

    cout<< endl<< "Scianka ZZ:   (Srodkowa)"<< endl;
    ZZ.Wypisz();
    //**************************************************************
    cout<< "### Sprawdzenie metody Obrot(...(w prawo)...)   ###"<< endl;
    Obrot(AA, 6, 5, 4,
          BB, 0, 7, 6,
          CC, 2, 1, 0,
          DD, 4, 3, 2);
    ZZ.ObrotC();
    cout<< "   Wyglad scianek po (obrocie):"<< endl;
    cout<< endl<< "Scianka AA:   (Gorna)"<< endl;
    AA.Wypisz();

    cout<< endl<< "Scianka BB:   (Prawa)"<< endl;
    BB.Wypisz();

    cout<< endl<< "Scianka CC:   (Dolna)"<< endl;
    CC.Wypisz();

    cout<< endl<< "Scianka DD:   (Lewa)"<< endl;
    DD.Wypisz();

    cout<< endl<< "Scianka ZZ:   (Srodkowa)"<< endl;
    ZZ.Wypisz();
}
//*******************************************************************
//*******************************************************************

//Kostka::Kostka():Up('W'):Left('R'):Front('B'):Right('O'):Back('G'):Down('Y')
Kostka::Kostka():Up('W'),Left('R'),Front('B'),Right('O'),Back('G'),Down('Y')
{
    /*Up('W')
    Left('R')
    Front('B')
    Right('O')
    Back('G')
    Down('Y') // */
    cout<< "Kostka stworzona !"<< endl;
}
//*********************************************************************

Kostka::Kostka(char* NazwaPliku)throw(string, char):Up('W'),Left('R'),Front('B'),Right('O'),Back('G'),Down('Y')
{
    fstream plik;
    plik.open(NazwaPliku,ios::in );
    //plik.open("Kostka3_3.txt",ios::in );
    if( plik.good()== false )
    {
        #ifdef KONTROLA_WCZYTANIA
        cout<< "Brak dostepu do pliku!" << endl;
        #endif // KONTROLA
        throw(NazwaPliku);
    } // */
    string napis;
    //plik>> napis;
    /*cout << "Zawartosc pliku:" << endl<< napis<< endl;
    while( !plik.eof() ){
        getline( plik, napis );
        #ifdef KONTROLA_WCZYTANIA
        cout << napis <<napis<< endl;
        //cout<< napis[3]<<endl;
        #endif // KONTROLA_WCZYTANIA
    } // */
    if ( !plik.eof() ){
        getline(plik, napis);
        //if
        Up.Set(0, napis[7]); /*Up.Set(1, 'O');*/ Up.Set(1, napis[9]); Up.Set(2, napis[11]);
    }
    if ( !plik.eof() ){
        getline(plik, napis);
        #ifdef STD
        if (napis[9] != 'W')
            throw(napis[9]);
        Up.Set(7, napis[7]); Up.Set(3, napis[11]);
        #endif // STD
        #ifndef STD
        Up.Set(7, napis[7]); Up.Set((-1), napis[9]); Up.Set(3, napsi[11]);
        #endif // STD
    }
    if ( !plik.eof() ){// LINIA 3 - Dziala
        getline(plik, napis);
        Up.Set(6, napis[7]); Up.Set(5, napis[9]); Up.Set(4, napis[11]);
    }
    /*if ( !plik.eof() ){// ENTER
        getline(plik, napis);
    } // */
    if ( !plik.eof() ){// ENTER - ### WYMAGANY ###
        getline(plik, napis);
    } // */
    if ( !plik.eof() ){// LINIA 4 - Dziala
        getline(plik, napis);
        Left.Set(0, napis[0]); Left.Set(1, napis[2]); Left.Set(2, napis[4]);
        Front.Set(0, napis[7]); Front.Set(1, napis[9]); Front.Set(2, napis[11]);
        Right.Set(0, napis[14]); Right.Set(1, napis[16]); Right.Set(2, napis[18]);
        Back.Set(0, napis[21]); Back.Set(1, napis[23]); Back.Set(2, napis[25]);
    }
    if ( !plik.eof() ){// LINIA 5 z warunkiem
        getline(plik, napis);
        #ifdef STD
        if (napis[2] != 'R' or napis[9] != 'B' or napis[16] != 'O' or
            napis[23] != 'G')
            throw("Wczytany plik poza standardem."); // */
        #endif // STD
        #ifndef STD
        Left.Set((-1), napis[2]); Front.Set((-1), napis[9]);
        Right.Set((-1), napis[16]); Back.Set((-1), napis[23]);
        #endif // STD
        Left.Set(7, napis[0]); Left.Set(3, napis[4]);
        Front.Set(7, napis[7]); Front.Set(3, napis[11]);
        Right.Set(7, napis[14]); Right.Set(3, napis[18]);
        Back.Set(7, napis[21]); Back.Set(3, napis[25]);
    }
    if ( !plik.eof() ){// LINIA 6 - Dziala, sprawdza standard prawidlowo
        getline(plik, napis);
        Left.Set(6, napis[0]); Left.Set(5, napis[2]); Left.Set(4, napis[4]);
        Front.Set(6, napis[7]); Front.Set(5, napis[9]); Front.Set(4, napis[11]);
        Right.Set(6, napis[14]); Right.Set(5, napis[16]); Right.Set(4, napis[18]);
        Back.Set(6, napis[21]); Back.Set(5, napis[23]); Back.Set(4, napis[25]);
    }
    if ( !plik.eof() ){// ENTER - ### WYMAGANY ###
        getline(plik, napis);
    } // */
    if ( !plik.eof() ){// LINIA 7
        getline(plik, napis);
        Down.Set(0, napis[7]); Down.Set(1, napis[9]); Down.Set(2, napis[11]);
    }
    if ( !plik.eof() ){// LINIA 8 - Dziala
        getline(plik, napis);
        #ifdef STD
        if (napis[9] != 'Y')
            throw(napis[9]);
        #endif // STD
        #ifndef STD
        Up.Set((-1), napis[9]);
        #endif // STD
        Down.Set(7, napis[7]); Down.Set(3, napis[11]);
    }
    if ( !plik.eof() ){// LINIA 9
        getline(plik, napis);
        Down.Set(6, napis[7]); Down.Set(5, napis[9]); Down.Set(4, napis[11]);
    }
    // */
    /*#ifdef KONTROLA_WCZYTANIA
    cout << "Na koncu w zmiennej napis jest:"<< endl <<napis << endl;
    #endif // KONTROLA_WCZYTANIA // */
    plik.close();
}
void Kostka::U()                // OBROT Gornej SCIANKI zgodnie z ruchem wskaz
{
    Up.ObrotC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Up.ObrotC(); czyli GORNA SCIANKA KOSTKI"
            " zostala obrocona zgodnie ze wskazowkami zegara"<< endl;
    #endif // TEST2
    Obrot(Back, 2, 1, 0,    // OK2/ Popr z 'Down na Beck'
          Right, 2, 1, 0,   // OK1/ O
          Front, 2, 1, 0,   // OK1/ O
          Left, 2, 1, 0);   // OK1/ O
}
void Kostka::u()                // OBROT Gornej SCIANKI przeciwnie do wskazow
{               // ### TO jest nasz przyklad modyfikacji 'WIELKIEJ litery'
    Up.ObrotAC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Up.ObrotAC(); czyli GORNA SCIANKA KOSTKI"
            " zostala obrocona przeciwnie do ruchu wskazowek zegara"<< endl;
    #endif // TEST2
    Obrot(Back, 2, 1, 0,    // #1   // OK2/
          Left, 2, 1, 0,   // #4    // brak kolejnych OK'jek oznacza brak
          Front, 2, 1, 0,   // #3   // dodatkowej ingerencji w linijke
          Right, 2, 1, 0);   // #2  // procz jej bezmyslnego skopiowania

}
void Kostka::L()                //np: X.L()
{
    Left.ObrotC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Left.ObrotC(); czyli LEWA SCIANKA KOSTKI"
            " zostala obrocona zgodnie ze wskazowkami zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 0, 7, 6,          // OK1/ O
          Front, 0, 7, 6,       // OK1/ O
          Down, 0, 7, 6,        // OK1/ O
          Back, 4, 3, 2);       // OK1/ O
}
void Kostka::l()
{
    Left.ObrotAC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Left.ObrotAC(); czyli LEWA SCIANKA KOSTKI"
            " zostala obrocona przeciwnie do ruchu wskazowek zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 0, 7, 6,          // OK2/
          Back, 4, 3, 2,       //
          Down, 0, 7, 6,        //
          Front, 0, 7, 6);       //
}
void Kostka::F()                    // (Kostka) X.F();
{               // ### TO jest nasz przyklad/ WZOR ###
    Front.ObrotC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Front.ObrotC(); czyli PRZEDNIA SCIANKA KOSTKI"
            " zostala obrocona zgodnie ze wskazowkami zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 6, 5, 4,
          Right, 0, 7, 6,
          Down, 2, 1, 0,
          Left, 4, 3, 2);
}
void Kostka::f()
{               // ### #2 <-> #4 ###
    Front.ObrotAC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Front.ObrotAC(); czyli PRZEDNIA SCIANKA KOSTKI"
            " zostala obrocona przeciwnie do ruchu wskazowek zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 6, 5, 4,      // OK2/
          Left, 4, 3, 2,    // #4 wiersz
          Down, 2, 1, 0,    // #3 wiersz
          Right, 0, 7, 6);  // #2 wiersz
}
void Kostka::R()
{
    Right.ObrotC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Right.ObrotC(); czyli GORNA SCIANKA KOSTKI"
            " zostala obrocona zgodnie ze wskazowkami zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 4, 3, 2,      // OK1/ O
          Back, 0, 7, 6,    // OK1/ O
          Down, 4, 3, 2,    // OK1/ O
          Front, 4, 3, 2);  // OK1/ O
}
void Kostka::r()
{
    Right.ObrotAC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Right.ObrotAC(); czyli GORNA SCIANKA KOSTKI"
            " zostala obrocona przeciwnie do ruchu wskazowek zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 4, 3, 2,      // OK2/
          Front, 4, 3, 2,  //
          Down, 4, 3, 2,    //
          Back, 0, 7, 6);    //
}
void Kostka::B()
{
    Back.ObrotC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Back.ObrotC(); czyli TYLNIA SCIANKA KOSTKI"
            " zostala obrocona zgodnie ze wskazowkami zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 2, 1, 0,      // OK1/ O
          Left, 0, 7, 6,    // OK1/ O
          Down, 6, 5, 4,    // OK1/ O
          Right, 4, 3, 2);  // OK1/ O
}
void Kostka::b()
{
    Back.ObrotAC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Back.ObrotAC(); czyli TYLNIA SCIANKA KOSTKI"
            " zostala obrocona przeciwnie do ruchu wskazowek zegara"<< endl;
    #endif // TEST2
    Obrot(Up, 2, 1, 0,      // OK2/
          Right, 4, 3, 2,  //
          Down, 6, 5, 4,    //
          Left, 0, 7, 6);    //
}
void Kostka::D()
{
    Down.ObrotC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Down.ObrotC(); czyli Dolna SCIANKA KOSTKI"
            " zostala obrocona zgodnie ze wskazowkami zegara"<< endl;
    #endif // TEST2
    Obrot(Front, 6, 5, 4,       // OK1/ O
          Right, 6, 5, 4,       // OK1/ O
          Back, 6, 5, 4,        // OK1/ O
          Left, 6, 5, 4);       // OK1/ O
}
void Kostka::d()
{
    Down.ObrotAC();
    #ifdef TEST2
    cout<< "Wykonano: Kostka::Down.ObrotAC(); czyli Dolna SCIANKA KOSTKI"
            " zostala obrocona przeciwnie do ruchu wskazowek zegara"<< endl;
    #endif // TEST2
    Obrot(Front, 6, 5, 4,       //
          Left, 6, 5, 4,       //
          Back, 6, 5, 4,        //
          Right, 6, 5, 4);       //
}
void Kostka::Wypisz()           // ... SIATKE KOSTKI
{
    #ifdef KONTROLA_PROGRAMU
    cout<< " ### KONTROLA PROGRAMU: Wypisuje kostke w postaci siatki."<< endl;
    #endif // KONTROLA_PROGRAMU
    cout<< "      "; Up.Wypisz(1); cout<< endl;
    cout<< "      "; Up.Wypisz(2); cout<< endl;
    cout<< "      "; Up.Wypisz(3); cout<< endl<< endl;

    Left.Wypisz(1); Front.Wypisz(1); Right.Wypisz(1); Back.Wypisz(1);cout<< endl;
    Left.Wypisz(2); Front.Wypisz(2); Right.Wypisz(2); Back.Wypisz(2);cout<< endl;
    Left.Wypisz(3); Front.Wypisz(3); Right.Wypisz(3); Back.Wypisz(3);cout<< endl<< endl;

    cout<< "      "; Down.Wypisz(1);cout<< endl;
    cout<< "      "; Down.Wypisz(2);cout<< endl;
    cout<< "      "; Down.Wypisz(3);cout<< endl;
}
bool Kostka::CzyUlozona()       // Wieszczka poprawnosci STANU obiektu
{                       // WERSJA dla dowolnej symboliki z dokladnoscia
                        // do zachowania przyzwoitych wlasnosci kostki
    //bool z= true;
    /*for (i=0; i<8; i++)
    {
        if (Up.Tab[i] != Up.KolorSrodka) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Left.Tab[i] != Left.KolorSrodka) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Front.Tab[i] != Front.KolorSrodka) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Right.Tab[i] != Right.KolorSrodka) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Back.Tab[i] != Back.KolorSrodka) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Down.Tab[i] != Down.KolorSrodka) return false;
    } // */
    #ifdef STD
    for (int i=0; i<8; i++){
        if (Up.Get(i) != 'W') return false;
    }
    for (int i=0; i<8; i++){
        if (Left.Get(i) != 'R') return false;
    }
    for (int i=0; i<8; i++){
        if (Front.Get(i) != 'B') return false;
    }
    for (int i=0; i<8; i++){
        if (Right.Get(i) != 'O') return false;
    }
    for (int i=0; i<8; i++){
        if (Back.Get(i) != 'G') return false;
    }
    for (int i=0; i<8; i++){
        if (Down.Get(i) != 'Y') return false;
    }
    #endif // STD
    #ifndef STD
    for (i=0; i<8; i++)
    {
        if (Up.Get(i) != Up.Get(-1)) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Left.Get(i) != Left.Get(-1)) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Front.Get(i) != Front.Get(-1)) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Right.Get(i) != Right.Get(-1)) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Back.Get(i) != Back.Get(-1)) return false;
    }
    for (i=0; i<8; i++)
    {
        if (Down.Get(i) != Down.Get(-1)) return false;
    }
    #endif // STD
    return true;
}
void Kostka::Ruch(char c)       // FUNKCJA POMOCNICZA:
                                // skladaja sie na nia powyzsze metody;
                                // char c jest kodem metody
                                //np: X.Ruch(L); oznacza X.L();
throw(char){
    if (c!='U' and c!='u' and c!='L' and c!='l' and c!='F' and
        c!='f' and c!='R' and c!='r' and c!='B' and c!='b' and
        c!='D' and c!='d' and c!='q' and c!='Q' and c!='k' and c!='K')
        throw(c);
    switch (c){
    case 'U':
        U();
        break;
    case 'u':
        u();
        break;
    case 'L':
        L();
        break;
    case 'l':
        l();
        break;
    case 'F':
        F();
        break;
    case 'f':
        f();
        break;
    case 'R':
        R();
        break;
    case 'r':
        r();
        break;
    case 'B':
        B();
        break;
    case 'b':
        b();
        break;
    case 'D':
        D();
        break;
    case 'd':
        d();
        break;
    case 'q':
        exit (EXIT_SUCCESS);
        break;
    case 'Q':
        exit (EXIT_SUCCESS);
        break;
    case 'k':
        exit (EXIT_SUCCESS);
        break;
    case 'K':
        exit (EXIT_SUCCESS);
        break;
    default:
        cout<< "Cos chyba poszlo nie tak. Nieprawidlowy znak dla funkcji"
                " (Kostka) X.Ruch(char c)."<< endl;

    }
}
//*********************************************************************

void Kostka::Wymieszaj(int n){
    srand(time(NULL)); // inicjalizacja generatora - tylko raz w programie
    //char TabRuch[12]= { 'U','u','L','l','F','f','R','r','B','b','D','d'};
    for (int j=0; j<n; j++){
        int chwil= rand()%12;
        Ruch(TabRuch[chwil]);
        cout<< TabRuch[chwil]<< endl;
    }
}
//*********************************************************************

void Wymieszaj(Kostka A, int n){
    srand(time(NULL)); // inicjalizacja generatora - tylko raz w programie
    //char TabRuch[12]= { 'U','u','L','l','F','f','R','r','B','b','D','d'};
    for (int j=0; j<n; j++)
        A.Ruch(TabRuch[rand()%12]);
}
//*********************************************************************

void Kostka::Uloz(int n){
    #ifdef KONTROLA_PROGRAMU
    cout<< "### KONTROLA PROGRAMU: Uloz("<< n<< ").   ###"<<endl;
    #endif // KONTROLA_PROGRAMU
    //static int licznik= n;
    //static char pamiec[n];
    if (CzyUlozona()){
        cout<< "Metoda Uloz("<< n<< ") zakonczona sukcesem."<< endl;
        /*for (j=0; j<(licznik-n+1); j++){
            cout<< pamiec[j]<< ", ";} // */
        cout<< endl; return;
    }
    if ( n>0 ){
        #ifdef KONTROLA_PROGRAMU
        cout<< "### KONTROLA PROGRAMU: n>0.   ###"<< endl;
        #endif // KONTROLA_PROGRAMU
        for (int l=0; l<12 and CzyUlozona()==false; l++){
            #ifdef KONTROLA_PROGRAMU
            cout<< "### KONTROLA PROGRAMU: petla("<< l<< ")."<<endl;
            #endif // KONTROLA_PROGRAMU
            Ruch(TabRuch[l]);
            //pamiec[iter]= TabRuch[iter];
            Uloz(n-1);
            if (CzyUlozona()){
                cout<< TabRuch[l]<< ", ";
                return;
            }
            Ruch(TabRuch[(l+6)%12]);
        }
    }
}
//*********************************************************************

void Test2()
{
    #ifdef KONTROLA_PROGRAMU
    cout<< " ### TEST2: Tworzenie kostki ###"<< endl;
    #endif // KONTROLA_PROGRAMU
    Kostka X;
    cout<< " Wyglad kostki z konstruktora:"<< endl;
    X.Wypisz(); cout<< endl<< endl;

    cout<< " ### FUNKCJA CzyUlozona(): ###"<< endl;
    cout<< X.CzyUlozona()<< endl<< endl;

    cout<< " ### Obroty: (Kostka) X.f(); ###"<< endl;
    X.f();
    cout<< " Wyglad kostki po obrocie 'f'"<< endl;
    X.Wypisz(); cout<< endl<< endl;

    cout<< " ### FUNKCJA CzyUlozona(): ###"<< endl;
    cout<< X.CzyUlozona()<< endl<< endl;
    //************************************************************
    //************************************************************

    cout<< " ### Obrot-FUNKCJA (Kostka) X.Ruch('r'); ###"<< endl;
    X.Ruch('r');
    cout<< " Wyglad kostki po obrocie funkcyjnym Ruch('r')"<< endl;
    X.Wypisz(); cout<< endl<< endl;

    cout<< " ### FUNKCJA CzyUlozona(): ###"<< endl;
    cout<< X.CzyUlozona()<< endl<< endl;
}
//****************************************************************

void Zabawa1()
{
    #ifdef KONTROLA_PROGRAMU
    cout<< "Rozpoczynamy zabawe!"<< endl;
    #endif // KONTROLA_PROGRAMU
    //try{
    Kostka X;
    cout<< "Twoja kostka wyglada nastepujaco:"<< endl;
    X.Wypisz();
    int IloscRuchow, IterZabaw= 0;
    int koniec= 1;
    while (true)
    {
        cout<< "Ile ruchow podasz? ";
        cin>> IloscRuchow;
        char TabRuch[IloscRuchow];

        cout<< "Podaj ciag liter twojego ruchu, dlugosci podanej przez ciebie wczesniej: ";
        for (IterZabaw=0; IterZabaw<IloscRuchow; IterZabaw++)
        {
            cin>> TabRuch[IterZabaw];
        }
        #ifdef KONTROLA_PROGRAMU
        cout<< "Podales kod ruchu (ciag): ";
        for (IterZabaw= 0; IterZabaw<IloscRuchow; IterZabaw++)
        {
            cout<< TabRuch[IterZabaw];
        }
        cout<< endl<< endl;
        #endif // KONTROLA_PROGRAMU

        for (IterZabaw= 0; IterZabaw<IloscRuchow; IterZabaw++)
        {
            X.Ruch(TabRuch[IterZabaw]);
            #ifdef ZABAWA_KAZDY_RUCH
            cout<< "Po ruchu '"<< TabRuch[IterZabaw]<< "' kostka wyglada"
                    " nastepujaco:"<< endl;
            X.Wypisz();
            #endif // ZABAWA_KAZDY_RUCH
        }
        #ifdef ZABAWA_KAZDY_RUCH
        cout<< " ### Koniec ostatniej komendy ###";
        #endif // ZABAWA_KAZDY_RUCH
        cout<< endl<< endl<< endl;
        if (X.CzyUlozona() == 1)
        {
            cout<< "Brawo, wygrales."<< endl;
            break;
        }
        cout<< "Czy chcesz kontynuowac zabawe? (0 na nie): ";
        cin>> koniec;
        if (koniec == 0) break;
    }//}
    /*catch(int b){
        cout<< "Liczba "<<b << " z poza zakresu."<< endl;
    }
    catch(char b){
        cout<< "Znak "<< b<< " z poza zakrsu."<< endl;
    }
    catch(string b)
    {
        cout<< b<< endl;
    }// */

}
//**********************************************************************

void Zad7_2(){
    Kostka DoWymieszania;           // Losowe zachowanie
    DoWymieszania.Wypisz();
    cout<< endl<< "Po wymieszaniu:"<< endl;
    DoWymieszania.Wymieszaj(1);
    DoWymieszania.Wypisz();

    DoWymieszania.Uloz(1);
    cout<<endl;
    DoWymieszania.Wypisz();
}
//***********************************************************************

void TestUloz()
{
    Kostka V;
    V.Wypisz();
    char r[2];
    cout<< "Podaj litere twojego ruchu: ";
    cin>> r[0];
    cin>> r[1];
    V.Ruch(r[0]);
    V.Ruch(r[1]);
    V.Wypisz();
    V.Uloz(2);
    V.Wypisz();
}
//***********************************************************************

void TestWczytaj(){
    char* NazwaWskaznik;
    NazwaWskaznik= new char[14];
    char NazwaTab[14]= {'K','o','s','t','k','a','3','_','3','.','t','x',
                        't',0};
    for (int q=0; q<14; q++)
        NazwaWskaznik[q]= NazwaTab[q];
    cout<< NazwaWskaznik[7];
    string NAZWA= "Kostka3_3.txt";
    Kostka V(NazwaWskaznik);
    V.Wypisz();
}
//***********************************************************************

void UlozZPliku()
{
    char* NazwaWskaznik;
    NazwaWskaznik= new char[14];
    cout<< "podaj 13-znakowa nazwe pliku (z '.txt'): ";
    for (int q=0; q<13; q++)
        cin>> NazwaWskaznik[q];
    NazwaWskaznik[13]= 0;
    Kostka V(NazwaWskaznik);
    V.Wypisz();
    cout<< endl<<endl<<endl;
    V.Uloz((int)NazwaWskaznik[6] - 48);
    cout<< endl<< endl<< endl;
    V.Wypisz();
}
