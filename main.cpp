#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;

bool ascending = true;

void printArray(vector<int> tab)
{
    for (unsigned int i = 0; i < tab.size(); i++)
    {
        cout << tab.at(i) << " ";
    }
}

void printStringArray(vector<string> tab)
{
    for (unsigned int i = 0; i < tab.size(); i++)
    {
        cout << tab.at(i) << " ";
    }
}

void printFloatArray(vector<float> tab)
{
    for (unsigned int i = 0; i < tab.size(); i++)
    {
        cout << tab.at(i) << " ";
    }
}

void print2DArray(vector<vector<int> > tab)
{
    for (unsigned int i = 0; i < tab.size(); i++)
    {
        for(unsigned int j = 0; j < tab.at(i).size(); j++)
        {
            cout << tab.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

struct Uczen
{
    string imie;
    string nazwisko;
    int numer;
    vector<vector<int> > oceny;
    float srednia_matma;
    float srednia_polski;
    float srednia_angielski;
    float srednia;

    Uczen(string i, string n, int nr, vector<vector<int> > o)
    {
        imie = i;
        nazwisko = n;
        numer = nr;
        oceny = o;
    }

    void wypisz()
    {
        cout << "-----------------------------------------------------------" << endl;
        cout << "Imie i nazwisko: " << imie << " " << nazwisko << endl;
        cout << "Numer w dzienniku: " << numer << endl;
        cout << "Oceny z matematyki: ";
        printArray(oceny.at(0));
        cout << "Srednia z matematyki: " << srednia_matma;
        cout << endl << "Oceny z j. polskiego: ";
        printArray(oceny.at(1));
        cout << "Srednia z j. polskiego: " << srednia_polski;
        cout << endl << "Oceny z j. angielskiego: ";
        printArray(oceny.at(2));
        cout << "Srednia z j. angielskiego: " << srednia_angielski << endl;
        cout << "Srednia: " << srednia << endl;
        cout << "-----------------------------------------------------------" << endl;
    }

    void updateSrednia()
    {
        float suma_matma = 0;
        for (unsigned int i = 0; i < oceny.at(0).size(); i++)
        {
            suma_matma += oceny.at(0).at(i);
        }
        float suma_polski = 0;
        for (unsigned int i = 0; i < oceny.at(1).size(); i++)
        {
            suma_polski += oceny.at(1).at(i);
        }
        float suma_angielski = 0;
        for (unsigned int i = 0; i < oceny.at(2).size(); i++)
        {
            suma_angielski += oceny.at(2).at(i);
        }
        float suma = suma_matma + suma_polski + suma_angielski;

        srednia_matma = suma_matma/(oceny.at(0).size());
        srednia_polski = suma_polski/(oceny.at(1).size());
        srednia_angielski = suma_angielski/(oceny.at(2).size());
        srednia = suma/(oceny.at(0).size() + oceny.at(1).size() + oceny.at(2).size());
    }
};

vector<vector<int> > getVector(string s)
{
    int open = 0;
    int close = 0;
    vector<vector<int> > result;
    vector<int> subarray;
    char number = '0';
    for (unsigned int i = 0; i < s.length(); i++)
    {
        if (s[i] == '[')
        {
            open = i;
        }
        else if (s[i] == ']')
        {
            close = i;
            for (int j = open + 1; j < close; j += 2)
            {
                number = s[j];
                subarray.push_back(number - '0');
            }
            result.push_back(subarray);
            subarray.clear();
        }
    }
    return result;
}

bool imionaComp(Uczen i, Uczen j)
{
    bool result = i.imie.compare(j.imie) <= 0;
    return ascending ? result : !result;
}

bool nazwiskaComp(Uczen i, Uczen j)
{
    bool result = i.nazwisko.compare(j.nazwisko) <= 0;
    return ascending ? result : !result;
}

bool nrComp(Uczen i, Uczen j)
{
    bool result = i.numer <= j.numer;
    return ascending ? result : !result;
}

bool matmaComp(Uczen i, Uczen j)
{
    bool result = i.srednia_matma <= j.srednia_matma;
    return ascending ? result : !result;
}

bool polskiComp(Uczen i, Uczen j)
{
    bool result = i.srednia_polski <= j.srednia_polski;
    return ascending ? result : !result;
}

bool angielskiComp(Uczen i, Uczen j)
{
    bool result = i.srednia_angielski <= j.srednia_angielski;
    return ascending ? result : !result;
}

bool sredniaComp(Uczen i, Uczen j)
{
    bool result = i.srednia <= j.srednia;
    return ascending ? result : !result;
}

vector<Uczen> tab_danych;

int main()
{

    // Wczytywanie bazy danych z pliku

    fstream bazaDanych;
    bazaDanych.open("baza.txt", ios::out | ios::app | ios::in);

    string t;
    string word = "";
    int n;
    string imie;
    string nazwisko;
    int nr;
    vector<vector<int> > oceny;

    while (getline(bazaDanych, t))
    {
        n = 0;
        for (unsigned int i = 0; i < t.length(); i++)
        {
            word += t[i];
            if (t[i] == ' ')
            {
                switch(n)
                {
                    case 0:
                        {
                            imie = word;
                            break;
                        }
                    case 1:
                        {
                            nazwisko = word;
                            break;
                        }
                    case 2:
                        {
                            nr = atoi(word.c_str());
                            break;
                        }
                    case 3:
                        {
                            oceny = getVector(word);
                            break;
                        }
                }
                n += 1;
                word = "";
            }
        }
        tab_danych.push_back(Uczen(imie, nazwisko, nr, oceny));
    }
    for (unsigned int i = 0; i < tab_danych.size(); i++)
    {
        tab_danych.at(i).updateSrednia();
    }

    // Menu


    fstream bazaDanychZapis;
    bazaDanychZapis.open("baza.txt", ios::app);
    int wybor;
    do
    {
        system("cls");
        cout << "-----------------------------------" << endl;
        cout << "|    1. Zapisz do bazy danych     |" << endl;
        cout << "|    2. Wyszukaj w bazie danych   |" << endl;
        cout << "|    3. Sortowanie bazy danych    |" << endl;
        cout << "|    4. Wyjdz                     |" << endl;
        cout << "-----------------------------------" << endl;

        cin >> wybor;
        switch (wybor)
        {
            case 1:
                {
                    cout << "DODAWANIE NOWEGO UCZNIA" << endl;
                    string imie_wpr;
                    cout << "Podaj imie: ";
                    cin >> imie_wpr;

                    string nazwisko_wpr;
                    cout << "Podaj nazwisko: ";
                    cin >> nazwisko_wpr;

                    int nr_wpr = tab_danych.size() + 1;

                    int ocena = 0;
                    vector<int> oceny_matma;
                    cout << "Podaj oceny z matematyki: ";
                    while (ocena != -1)
                    {
                        cin >> ocena;
                        oceny_matma.push_back(ocena);
                    }
                    oceny_matma.pop_back();

                    ocena = 0;
                    vector<int> oceny_polski;
                    cout << "Podaj oceny z j. polskiego: ";
                    while (ocena != -1)
                    {
                        cin >> ocena;
                        oceny_polski.push_back(ocena);
                    }
                    oceny_polski.pop_back();

                    ocena = 0;
                    vector<int> oceny_angielski;
                    cout << "Podaj oceny z j. angielskiego: ";
                    while (ocena != -1)
                    {
                        cin >> ocena;
                        oceny_angielski.push_back(ocena);
                    }
                    oceny_angielski.pop_back();

                    vector<vector<int> > oceny_wprowadzone;
                    oceny_wprowadzone.push_back(oceny_matma);
                    oceny_wprowadzone.push_back(oceny_polski);
                    oceny_wprowadzone.push_back(oceny_angielski);

                    Uczen nowyUczen(imie_wpr, nazwisko_wpr, nr_wpr, oceny_wprowadzone);
                    nowyUczen.updateSrednia();
                    tab_danych.push_back(nowyUczen);

                    bazaDanychZapis << endl << nowyUczen.imie << " " << nowyUczen.nazwisko
                    << " " << nowyUczen.numer << " ";
                    for (unsigned int i = 0; i < 3; i++)
                    {
                        bazaDanychZapis << "[";
                        for (unsigned int j = 0; j < nowyUczen.oceny.at(i).size(); j++)
                        {
                            bazaDanychZapis << nowyUczen.oceny.at(i).at(j);
                            if (j != nowyUczen.oceny.at(i).size() - 1)
                            {
                                bazaDanychZapis << ",";
                            }
                        }
                        bazaDanychZapis << "]";
                        if (i != 2)
                        {
                            bazaDanychZapis << ",";
                        }
                    }
                    bazaDanychZapis << " ";

                    system("pause");

                    break;
                }
            case 2:
                {
                    system("cls");
                    cout << "-----------------------------------" << endl;
                    cout << "|    1. Imie                      |" << endl;
                    cout << "|    2. Nazwisko                  |" << endl;
                    cout << "|    3. Numer w dzienniku         |" << endl;
                    cout << "|    4. Srednia z matematyki      |" << endl;
                    cout << "|    5. Srednia z j. polskiego    |" << endl;
                    cout << "|    6. Srednia z j. angielskiego |" << endl;
                    cout << "|    7. Srednia                   |" << endl;
                    cout << "-----------------------------------" << endl;

                    int wybor2;
                    cin >> wybor2;

                    switch (wybor2)
                    {
                        case 1:
                            {
                                string imie;
                                cin >> imie;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).imie.find(imie) != string::npos)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                        case 2:
                            {
                                string nazwisko;
                                cin >> nazwisko;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).nazwisko.find(nazwisko) != string::npos)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                        case 3:
                            {
                                int nr;
                                cin >> nr;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).numer == nr)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                        case 4:
                            {
                                int p, q;
                                cin >> p >> q;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).srednia_matma >= p && tab_danych.at(i).srednia_matma <= q)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                        case 5:
                            {
                                int p, q;
                                cin >> p >> q;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).srednia_polski >= p && tab_danych.at(i).srednia_polski <= q)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                        case 6:
                            {
                                int p, q;
                                cin >> p >> q;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).srednia_polski >= p && tab_danych.at(i).srednia_polski <= q)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                        case 7:
                            {
                                int p, q;
                                cin >> p >> q;

                                for (unsigned int i = 0; i < tab_danych.size(); i++)
                                {
                                    if (tab_danych.at(i).srednia_angielski >= p && tab_danych.at(i).srednia_angielski <= q)
                                    {
                                        tab_danych.at(i).wypisz();
                                    }
                                }
                                break;
                            }
                    }
                    system("pause");
                    break;
                }
            case 3:
                {
                    system("cls");
                    cout << "-----------------------------------" << endl;
                    cout << "|    1. Imie                      |" << endl;
                    cout << "|    2. Nazwisko                  |" << endl;
                    cout << "|    3. Numer w dzienniku         |" << endl;
                    cout << "|    4. Srednia z matematyki      |" << endl;
                    cout << "|    5. Srednia z j. polskiego    |" << endl;
                    cout << "|    6. Srednia z j. angielskiego |" << endl;
                    cout << "|    7. Srednia                   |" << endl;
                    cout << "-----------------------------------" << endl;

                    int wybor2;
                    cin >> wybor2;

                    system("cls");
                    cout << "-----------------------------------" << endl;
                    cout << "|    1. Rosnaco                   |" << endl;
                    cout << "|    2. Malejaco                  |" << endl;
                    cout << "-----------------------------------" << endl;

                    int order;
                    cin >> order;

                    if (order == 1)
                    {
                        ascending = true;
                    }
                    else
                    {
                        ascending = false;
                    }


                    switch(wybor2)
                    {
                        case 1:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), imionaComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                        case 2:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), nazwiskaComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                        case 3:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), nrComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                        case 4:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), matmaComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                        case 5:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), polskiComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                        case 6:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), angielskiComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                        case 7:
                            {
                                vector<Uczen> copy_tab = tab_danych;
                                sort(copy_tab.begin(), copy_tab.end(), sredniaComp);
                                for (unsigned int i = 0; i < copy_tab.size(); i++)
                                {
                                    copy_tab.at(i).wypisz();
                                }
                                break;
                            }
                    }
                    system("pause");
                    break;
                }
        }
    }while(wybor != 4);
    bazaDanych.close();
    return 0;
}
