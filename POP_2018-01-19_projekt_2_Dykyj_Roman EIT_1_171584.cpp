//
//  main.cpp
//  encyklopedia
//  G++, Xcode
//  Created by Roman Dykyj on 07.01.2018.
//  Copyright © 2018 Roman Dykyj. All rights reserved.
//  POP_2018-01-19_projekt_2_Dykyj_Roman EIT_1_171584

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

void szukanie_ciagu()
{
    //podanie ilosci wyrazow, ZMIENNE: ILOSC_WYRAZOW, WPROWADZANE DANE
    int ilosc_wyrazow;
    string wprowadzane_dane;
    do {
        cout << endl << "Podaj ilosc wyrazow ciagu (min:3; max:20), ktory chcesz dodac: ";
        cin >> wprowadzane_dane;
        ilosc_wyrazow = atoi(wprowadzane_dane.c_str());
        wprowadzane_dane.clear();
        if (ilosc_wyrazow>20 or ilosc_wyrazow<3) {
            cout << endl << "Podales niepoprawne dane!" << endl;
        }
    } while (ilosc_wyrazow>20 or ilosc_wyrazow<3);
    
    //podanie wartosci wyrazow ciagu, ZMIENNE: ilosc_wyrazow, wprowadzane dane, wartosc_wyrazow[]
    int *wartosc_wyrazow = new int[ilosc_wyrazow];
        for (int i=0; i<ilosc_wyrazow; i++) {
            do {
                cout << "Podaj " << i+1 << " wyraz ciagu: ";
                cin >> wprowadzane_dane;
                wartosc_wyrazow[i] = atoi(wprowadzane_dane.c_str());
                
                if (wartosc_wyrazow[i]<=0) {
                    cout << endl << "Podales niepoprawne dane!" << endl << endl;
                }
            } while (wartosc_wyrazow[i]<=0);
        }
    
    //sprawdzanie, czy podany ciag nie jest zwyklym ciagiem aryt albo geom. odeslanie do szukania w bazie ZMIENNE: wartosc_wyrazow[], SZUKANIE_BAZIE
    bool szukanie_bazie=false;
    if(2*wartosc_wyrazow[1]==wartosc_wyrazow[2]+wartosc_wyrazow[0] and wartosc_wyrazow[1]*wartosc_wyrazow[1]==wartosc_wyrazow[2]*wartosc_wyrazow[0])
        cout << endl << "Dany ciag jest zarowno arytmetyczny jak i geometryczny!" << endl << endl;
    else if(2*wartosc_wyrazow[1]==wartosc_wyrazow[2]+wartosc_wyrazow[0])
        cout << endl << "Dany ciag jest arytmentyczny!" << endl << endl;
    else if(wartosc_wyrazow[1]*wartosc_wyrazow[1]==wartosc_wyrazow[2]*wartosc_wyrazow[0])
        cout << endl << "Dany ciag jest geomatryczny!" << endl << endl;
    else {
        cout << endl << "Dany ciag nie jest ani arytmetyczny, ani geometryczny." << endl << "Sprawdze czy nie ma go w bazie specyficznych ciagow!" << endl << endl;
        szukanie_bazie = true;
    }
    
    //sprawdzenie czy dany ciag jest w bazie
    if (szukanie_bazie==true) {
        //pobranie trzech pierwszych wartosci ciagu wpisanych przez uzytkownika i zapisanie ich w postaci: x, y, z do zmiennej porownanie indeksu, ZMIENNE: PLIK, POROWNANIE_INDEKSU1, wartosc_wyrazow, PLIK POMOCNICZY.TXT
        fstream plik;
        string porownanie_indeksu1;
        plik.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/pomocniczy.txt", ios::out);
        plik << wartosc_wyrazow[0] << ", " << wartosc_wyrazow[1] << ", " << wartosc_wyrazow[2];
        plik.close();
        plik.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/pomocniczy.txt", ios::in);
        wprowadzane_dane.clear();
        getline(plik, porownanie_indeksu1);
        plik.close();
        
        //zapisanie danych z pliku indeks.txt w dynamicznej tablicy, ZMIENNE: PLIK2, ZAWARTOSC_INDEKSU[], SKRYTKA, INDEKS.TXT
        fstream plik2;
        vector<string>zawartosc_indeksu;
        string skrytka;
        plik2.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/indeks.txt");
        while( !plik2.eof() )
        {
            skrytka.clear();
            getline( plik2, skrytka );
            zawartosc_indeksu.push_back(skrytka);
        }
        plik2.close();
        
        //obcinam dlugosc zawarosci indeksu, tak aby byla rowna z wprowadzanymi danymi w formie: x, y, z ZMIENNE: zawartosc_indeksu[]
        for (int i=0; i<zawartosc_indeksu.size(); i++) {
            zawartosc_indeksu[i] = zawartosc_indeksu[i].substr(0,porownanie_indeksu1.size());
        }
        
        //porowanie wprowadzonych danych z indeksem, ZMIENNE: NUMER_INDEKSU[], zawartosc_indeksu[], porownanie_indeksu1
        vector<int>numer_indeksu;
        for (int i=0; i<zawartosc_indeksu.size(); i++) {
            if (porownanie_indeksu1==zawartosc_indeksu[i]) {
                numer_indeksu.push_back(i);
            }
        }
        
        //pobranie danych z katalogu ZMIENNE: PLIK3, ZAWARTOSC_KATALOGU[], skrytka, katalog.txt
        fstream plik3;
        vector<string>zawartosc_katalogu;
        plik3.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/katalog.txt");
        while( !plik3.eof() )
        {
            skrytka.clear();
            getline( plik3, skrytka );
            zawartosc_katalogu.push_back(skrytka);
        }
        plik3.close();
        
        //zapisanie wprowadzanych danych w opowiedniej postaci i zapisanie ich w zmiennej wprowadzane_dane !! JUZ NIE JEST PRZEJSCIOWA TA ZMIENNNA! ZMIENNA: WPROWADZANE_DANE;
        plik.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/pomocniczy.txt", ios::trunc | ios::in | ios::out);
        for (int i = 0; i<ilosc_wyrazow-1; i++) {
            plik << wartosc_wyrazow[i] << ", ";
        }
        plik << wartosc_wyrazow[ilosc_wyrazow-1];
        plik.close();
        plik.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/pomocniczy.txt", ios::in);
        wprowadzane_dane.clear();
        getline(plik, wprowadzane_dane);
        plik.close();
        
        //tablica poprawnych odpowiedzi ZMIENNE: ODPOWIEDZI[], skrytka, plik3
        vector<string>odpowiedzi;
        plik3.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/katalog.txt");
        while( !plik3.eof() )
        {
            skrytka.clear();
            getline( plik3, skrytka );
            odpowiedzi.push_back(skrytka);
        }
        plik3.close();
        
        //skracanie wyrazow aby je porownac ZMIENNE: POZYCJA_DWUKROPKA, numer_indeksu, zawartosc_katalogu, wprowadzane_dane, odpowiedzi
        unsigned long pozycja_dwukropka;
        for (int i=0; i<numer_indeksu.size(); i++) {
            pozycja_dwukropka = zawartosc_katalogu[numer_indeksu[i]].find(":");
            
            zawartosc_katalogu[numer_indeksu[i]] = zawartosc_katalogu[numer_indeksu[i]].substr(0,pozycja_dwukropka);
            
            if (wprowadzane_dane.size()>zawartosc_katalogu[numer_indeksu[i]].size())
                wprowadzane_dane = wprowadzane_dane.substr(0, zawartosc_katalogu[numer_indeksu[i]].size());
            else if (wprowadzane_dane.size()<zawartosc_katalogu[numer_indeksu[i]].size())
                zawartosc_katalogu[numer_indeksu[i]] = zawartosc_katalogu[numer_indeksu[i]].substr(0, wprowadzane_dane.size());
            
            if (wprowadzane_dane==zawartosc_katalogu[numer_indeksu[i]]) {
                    cout << endl << "W bazie znalazlem to: " << odpowiedzi[numer_indeksu[i]] << endl;
            }
        }
        
     delete [] wartosc_wyrazow;
    }
}

void dodanie_ciagu()
{
    //podanie nazwy ciagu, ilosci wyrazow oraz ich wartosci
    string nazwa_ciagu;
    string skrytka;
    int l_wyrazow;
    cout << endl <<"Podaj nazwe ciagu, ktory chcesz dodac (nie uzywaj spacji): ";
    cin >> nazwa_ciagu;
    do{
    cout << "Podaj liczbe wyrazow ciagu, ktory chcesz dodac (min:3, max:20): ";
    cin >> skrytka;
        l_wyrazow = atoi(skrytka.c_str());
        if (l_wyrazow>20 or l_wyrazow<3) {
            cout << "Podales bledne dane!" << endl ;
        }
    }while (l_wyrazow>20 or l_wyrazow<3);
    
    skrytka.clear();
    
    int *wartosc_wyrazow = new int[l_wyrazow];
    for (int i=0; i<l_wyrazow; i++) {
        do {
            cout << "Podaj " << i+1 << " wyraz ciagu: ";
            cin >> skrytka;
            wartosc_wyrazow[i] = atoi(skrytka.c_str());
            
            if (wartosc_wyrazow[i]<=0) {
                cout << "Podales niepoprawne dane!" << endl;
            }
        } while (wartosc_wyrazow[i]<=0);
    }
    
    
    //zapisanie wyrazow do katalogu.txt w odpowiednim formacie
    fstream plik;
    plik.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/katalog.txt", ios::app);
    for (int i=0; i<l_wyrazow-1; i++) {
        plik << wartosc_wyrazow[i] << ", ";
    }
    plik << wartosc_wyrazow[l_wyrazow-1] << ": ";
    plik << nazwa_ciagu;
    plik << endl;
    plik.close();
    
    //policzeenie ile lini (ciagow) zapisane jest w pliku
    string linia;
    int licznik = 0;
    plik.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/katalog.txt");
    while (getline(plik, linia)) licznik ++;
    plik.close();
    
    //zapisanie indeksu do pliku
    fstream plik2;
    plik2.open("/Users/romandykyj/Xcode/encyklopedia/encyklopedia/indeks.txt", ios::app);
    for (int i=0; i<2; i++) {
        plik2 << wartosc_wyrazow[i] << ", ";
    }
    plik2 << wartosc_wyrazow[2] << ": ";
    plik2 << licznik;
    plik2 << endl;
    plik2.close();
    
    //
    delete [] wartosc_wyrazow;
    cout << endl << "Ciag zostal dodany!" << endl << endl;
}

int main() {
    char wybor;
    bool stan = true;
        cout << endl << "WITAJ W ENCYKLOPEDII CIAGOW!" << endl << endl << "MENU" << endl << "1.Szukanie ciagu w bazie" << endl << "2.Dodanie ciagu do bazy" << endl <<"3.Wyjscie";
        cout << endl << endl;
        while (stan == true) {
        cout << "Operacja (Wypisz opcje (1, 2 lub 3), a nastepnie kliknij enter): ";
        cin >> wybor;
        switch (wybor) {
            case '1':
                szukanie_ciagu();
                stan = false;
                break;
            case '2':
                dodanie_ciagu();
                stan = false;
                break;
            case '3':
                exit(0);
                break;
            default:
                cout << endl << "Podales bledne dane!" << endl << endl;
                break;
        }
    }
    return 0;
}
