#include <iostream>
#include "KOSTKA_RUBIKA_2015.h"
#include "KOSTKA_RUBIKA_2015.cpp"

using namespace std;

int main()
{
    try {
    //Test1();  // Scianka
    //Test2();  // Kostka
    //Zabawa1();  // Zad4
    //Zad7_2();       // Zad 7 bez wczytania, test Wymieszaj() i Uluz();
    //TestUloz();
    //TestWczytaj();
    UlozZPliku();
    }
    catch(int b) {
        cout << "Liczba " << b << " z poza zakresu." << endl;
    }
    catch(char b) {
        cout << "Znak "<< b<< " z poza zakresu."<< endl;
    }
    catch(string b) {
        cout << b << endl;
    }
    catch(char* b) {
        cout << "Nazwa pliku: " << b << " jest nieprawidlowa" << endl;
    }
    return 0;
}
