#include <iostream>
using namespace std;
#include "Uzytkownik.h"

Uzytkownik::Uzytkownik()
{

}

Uzytkownik::~Uzytkownik()
{

}

void Uzytkownik::ustawIdUzytkownika(int id)
{
    idUzytkownika=id;
}

void Uzytkownik::ustawNazweUzytkownika(string nazwa)
{
    nazwaUzytkownika=nazwa;
}

void Uzytkownik::ustawHasloUzytkownika(string haslo)
{
    hasloUzytkownika=haslo;
}

int Uzytkownik::pobierzIdUzytkownika()
{
    return idUzytkownika;
}

string Uzytkownik::pobierzNazweUzytkownika()
{
    return nazwaUzytkownika;
}

string Uzytkownik::pobierzHasloUzytkownika()
{
    return hasloUzytkownika;
}
