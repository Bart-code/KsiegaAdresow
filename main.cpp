#include <iostream>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template < class T >
string to_string( T t )
{
    stringstream ss;
    ss << t;
    return ss.str();
}

struct Osoba{
    int id;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    Osoba * nastepnaOsoba;
    Osoba * poprzedniaOsoba;
};

struct Uzytkownik{
    int numerID;
    string login;
    string haslo;
};

fstream plik, plikTymczasowy;

Osoba * dodajOsobe(Osoba * PoczatekListyOsob, int idObecnegoUzytkownika)
{
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::app);
    Osoba * w_osoba=new Osoba;
    if(PoczatekListyOsob==NULL){
        w_osoba->id=1;
    }
    else w_osoba->id=PoczatekListyOsob->id+1;
    plik<<w_osoba->id<<"|";
    w_osoba->idUzytkownika=idObecnegoUzytkownika;
    plik<<w_osoba->idUzytkownika<<"|";
    cout<<"Podaj imie: ";
    cin>>w_osoba->imie;
    plik<<w_osoba->imie<<"|";
    cout<<"Podaj nazwisko: ";
    cin>>w_osoba->nazwisko;
    plik<<w_osoba->nazwisko<<"|";
    cout<<"Podaj numer telefonu: ";
    cin.ignore( 1000, '\n' );
    getline(cin,w_osoba->numerTelefonu);
    plik<<w_osoba->numerTelefonu<<"|";
    cout<<"Podaj e-mail: ";
    cin>>w_osoba->email;
    plik<<w_osoba->email<<"|";
    cout<<"Podaj adres zamieszkania: "<<endl;
    cin.ignore( 1000, '\n' );
    getline(cin,w_osoba->adres);
    plik<<w_osoba->adres<<"|"<<endl;
    w_osoba->nastepnaOsoba=PoczatekListyOsob;
    w_osoba->poprzedniaOsoba=NULL;
    if (w_osoba->nastepnaOsoba!=NULL ) w_osoba->nastepnaOsoba->poprzedniaOsoba=w_osoba;
    PoczatekListyOsob=w_osoba;
    cout<<endl<<"   Dodano osobe";
    Sleep(1200);
    plik.close();
    return PoczatekListyOsob;
}

void wyswietlListe(Osoba * PoczatekListyOsob)
{
    Osoba * pomocnicza=PoczatekListyOsob;
    int pozycjaMenu=0;
    system("cls");
    cout << "Ksiega adresowa" << endl<<endl;
    if(pomocnicza==NULL) cout<<"Ksiega Twoich znajomych jest pusta !"<<endl<<endl;
    while(pomocnicza!=NULL)
    {
        cout<<"Imie: "<<pomocnicza->imie<<endl;
        cout<<"Nazwisko: "<<pomocnicza->nazwisko<<endl;
        cout<<"Numer telefonu: "<<pomocnicza->numerTelefonu<<endl;
        cout<<"E-mail: "<<pomocnicza->email<<endl;
        cout<<"Adres zamieszkania: "<<pomocnicza->adres<<endl<<endl;
        pomocnicza=pomocnicza->nastepnaOsoba;
    }
    cout<<"1. Powrot";
    while(1)
    {
        cin>>pozycjaMenu;
        if(pozycjaMenu==1) break;
    }
}


void zapiszListeDoPliku(Osoba * PoczatekListyOsob, int idObecnegoUzytkownika)
{
    Osoba *wybranaOsoba = PoczatekListyOsob;
    string linia,idString,idUzytkownikaString,pomocniczy;
    int i,j, idUzytkownika;
    plik.close();
    plik.open("ksiazkaAdresowa.txt",ios::in);
    plikTymczasowy.open("ksiazkaAdresowaTymczasowa.txt",ios::out|ios::trunc);
    if(plik.good()){
    while(getline(plik,linia))   //zapisanie adresatow innych uzytkownikow
    {
        i=0; j=0;
        while(linia[i]!='|') i++;
        j=++i;
        while(linia[i]!='|') i++;
        pomocniczy=linia.substr(j,i-j);
        idUzytkownika = atoi(pomocniczy.c_str());  //uzyskanie idUzytkownika aktualnej osoby
        cout<<endl<<idUzytkownika<<endl;
        system("pause");
        if(idUzytkownika!=idObecnegoUzytkownika) plikTymczasowy<<linia<<endl;
    }
    }
    else cout<<"Nie mozna otworzyc pliku do zapisu";
    system("pause");
    while(wybranaOsoba!=NULL)   //zapisanie adresatow obecnego uzytkownika
    {
        idString=to_string(wybranaOsoba->id);
        idUzytkownikaString=to_string(wybranaOsoba->idUzytkownika);
        linia = idString + '|'+idUzytkownikaString + '|' + wybranaOsoba->imie + '|' + wybranaOsoba->nazwisko + '|' + wybranaOsoba->numerTelefonu + '|' +wybranaOsoba->email + '|' + wybranaOsoba->adres + '|';
        plikTymczasowy<<linia<<endl;
        wybranaOsoba=wybranaOsoba->nastepnaOsoba;
    }
    plik.close();
    plikTymczasowy.close();
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::trunc);
    plikTymczasowy.open("ksiazkaAdresowaTymczasowa.txt",ios::in);
    while(getline(plikTymczasowy,linia)) plik<<linia<<endl;   //przepisanie plikow
    plik.close();
    plikTymczasowy.close();

}


void edytujDaneOsoby(Osoba * konkretnaOsoba,Osoba * PoczatekListyOsob, int idObecnegoUzytkownika)
{
    system("cls");
    int pozycjaMenu=0;
    string nowaDana;
    cout<<"Wybierz dane do edycji"<<endl;
    cout<<"1. Imie"<<endl;
    cout<<"2. Nazwisko"<<endl;
    cout<<"3. Numer telefonu"<<endl;
    cout<<"4. E-mail"<<endl;
    cout<<"5. Adres zamieszkania"<<endl<<endl;
    cout<<"6. Powrot"<<endl;
    do
    {
        cin>>pozycjaMenu;
    }
    while(pozycjaMenu<1||pozycjaMenu>6);
    system("cls");
    switch(pozycjaMenu)
    {
    case 1:
    {
        cout<<"Wprowadz nowe imie: ";
        cin>>nowaDana;
        konkretnaOsoba->imie=nowaDana;
        break;
    }
    case 2:
    {
        cout<<"Wprowadz nowe nazwisko: ";
        cin>>nowaDana;
        konkretnaOsoba->nazwisko=nowaDana;
        break;
    }
    case 3:
    {
        cout<<"Wprowadz nowy numer telefonu: "<<endl;
        cin.ignore( 1000, '\n' );
        getline(cin,nowaDana);
        konkretnaOsoba->numerTelefonu=nowaDana;//.substr(30);
        break;
    }
    case 4:
    {
        cout<<"Wprowadz nowy e-mail: ";
        cin>>nowaDana;
        konkretnaOsoba->email=nowaDana;
        break;
    }
    case 5:
    {
        cout<<"Wprowadz nowy adres: "<<endl;
        cin.ignore( 1000, '\n' );
        getline(cin,nowaDana);
        konkretnaOsoba->adres=nowaDana;//.substr(21);
        break;
    }
    case 6:
        return;
    }
    zapiszListeDoPliku(PoczatekListyOsob,idObecnegoUzytkownika);
}

bool usunOsobeZListy(Osoba * konkretnaOsoba,Osoba * PoczatekListyOsob, int idObecnegoUzytkownika)
{
    char wybor;
    cout<<"Czy na pewno chcesz usunac osobe z listy ?"<<endl<<"TAK - t  /  NIE - n"<<endl;
    do cin>>wybor;
    while(wybor!='t'&&wybor!='n');
    if(wybor=='n') return false;
    Osoba * aktualnaOsoba=PoczatekListyOsob;
    while(aktualnaOsoba!=konkretnaOsoba){
        aktualnaOsoba=aktualnaOsoba->nastepnaOsoba;
    }
    if(aktualnaOsoba->poprzedniaOsoba==NULL)
    {
        PoczatekListyOsob=aktualnaOsoba->nastepnaOsoba;
        aktualnaOsoba->nastepnaOsoba->poprzedniaOsoba=NULL;
    }
    else if(aktualnaOsoba->nastepnaOsoba==NULL)
    {
        aktualnaOsoba->poprzedniaOsoba->nastepnaOsoba=NULL;
    }
    else
    {
            aktualnaOsoba->poprzedniaOsoba->nastepnaOsoba=aktualnaOsoba->nastepnaOsoba;
    aktualnaOsoba->nastepnaOsoba->poprzedniaOsoba=aktualnaOsoba->poprzedniaOsoba;
    }
    zapiszListeDoPliku(PoczatekListyOsob,idObecnegoUzytkownika);
    return true;
}

void wyszukajOsobe(Osoba * PoczatekListyOsob, int idObecnegoUzytkownika)
{
    string imie, nazwisko;
    int pozycjaMenu=0, id;
    Osoba * pomocnicza=PoczatekListyOsob;
    bool pustaListaOsob=false;

    do
    {
        system("cls");
        cout << "Ksiega adresowa" << endl<<endl;
        cout << "Wyszukaj osobe"<<endl<<endl;
        cout << "1. Po imieniu"<<endl;
        cout << "2. Po nazwisku"<<endl;
        cout << "3. Powrot"<<endl;
        cin>>pozycjaMenu;
    }
    while(!(pozycjaMenu==1||pozycjaMenu==2||pozycjaMenu==3));
    switch(pozycjaMenu)
    {
    case 1:
    {
        system("cls");
        cout << "Ksiega adresowa" << endl<<endl;
        cout<<"Wprowadz imie: ";
        cin>>imie;
        cout<<endl<<endl;
        pustaListaOsob=false;
        while(pomocnicza!=NULL)
        {
            if(imie==pomocnicza->imie)
            {
                cout<<"Numer ID :"<<pomocnicza->id<<endl;
                cout<<"Imie: "<<pomocnicza->imie<<endl;
                cout<<"Nazwisko: "<<pomocnicza->nazwisko<<endl<<endl;
                pustaListaOsob=true;
            }
            pomocnicza=pomocnicza->nastepnaOsoba;
        }
        if(!pustaListaOsob)
        {
            cout<<"Nie ma osob o takim imieniu !";
            Sleep(1200);
            return;
        }
        break;
    }
    case 2:
    {
        system("cls");
        cout << "Ksiega adresowa" << endl<<endl;
        cout<<"Wprowadz nazwisko: ";
        cin>>nazwisko;
        while(pomocnicza!=NULL)
        {
            if(nazwisko==pomocnicza->nazwisko)
            {
                pustaListaOsob=true;
                cout<<"Numer ID :"<<pomocnicza->id<<endl;
                cout<<"Nazwisko: "<<pomocnicza->nazwisko<<endl;
                cout<<"Imie: "<<pomocnicza->imie<<endl<<endl;
            }
            pomocnicza=pomocnicza->nastepnaOsoba;
        }
        if(!pustaListaOsob)
        {
            cout<<"Nie ma osob o takim nazwisku !";
            Sleep(1200);
            return;
        }
        break;
    }
    case 3:
        return;
    }
    cout<<endl<<"Wprowadz ID szukanej osoby: ";
    cin>>id;
    pomocnicza=PoczatekListyOsob;
    system("cls");
    cout << "Ksiega adresowa" << endl<<endl;
    while(pomocnicza!=NULL)
    {
        if(pomocnicza->id==id)
        {
            while(1)
            {
                system("cls");
                cout<<"Ksiega adresowa"<<endl<<endl;
                cout<<"Imie: "<<pomocnicza->imie<<endl;
                cout<<"Nazwisko: "<<pomocnicza->nazwisko<<endl;
                cout<<"Numer telefonu: "<<pomocnicza->numerTelefonu<<endl;;
                cout<<"E-mail: "<<pomocnicza->email<<endl;
                cout<<"Adres zamieszkania: "<<pomocnicza->adres<<endl<<endl;
                cout<<endl<<"1. Powrot do Menu glownego"<<endl<<"2. Edycja danych"<<endl<<"3. Usun osobe z listy"<<endl;
                pozycjaMenu=0;
                cin>>pozycjaMenu;
                if(pozycjaMenu==1) return;
                else if(pozycjaMenu==2) edytujDaneOsoby(pomocnicza,PoczatekListyOsob,idObecnegoUzytkownika);
                else if(pozycjaMenu==3) if(usunOsobeZListy(pomocnicza,PoczatekListyOsob,idObecnegoUzytkownika)) return;
            }
        }
        pomocnicza=pomocnicza->nastepnaOsoba;
    }
}

Osoba * wczytajDaneZPliku(Osoba * PoczatekListyOsob, int idObecnegoUzytkownika)
{
    plik.close();
    plik.open("ksiazkaAdresowa.txt",ios::in);
    if(plik.good()==true)
    {
        string linia,pomocniczy;
        int idAdresata, idUzytkownika;
        while(getline(plik,linia))
        {
            Osoba * w_osoba=new Osoba;
            int i=0,j=0;
            while(linia[i]!='|') i++;
            pomocniczy=linia.substr(0,i);
            idAdresata= atoi(pomocniczy.c_str());
            j=++i;
            while(linia[i]!='|') i++;
            pomocniczy=linia.substr(j,i-j);
            idUzytkownika = atoi(pomocniczy.c_str());
            j=++i;
            if(idUzytkownika!=idObecnegoUzytkownika) continue;
            w_osoba->id =idAdresata;
            w_osoba->idUzytkownika =idUzytkownika;
            while(linia[i]!='|') i++;
            w_osoba->imie=linia.substr(j,i-j);
            j=++i;
            while(linia[i]!='|') i++;
            w_osoba->nazwisko=linia.substr(j,i-j);
            j=++i;
            while(linia[i]!='|') i++;
            w_osoba->numerTelefonu=linia.substr(j,i-j);
            j=++i;
            while(linia[i]!='|') i++;
            w_osoba->email=linia.substr(j,i-j);
            j=++i;
            while(linia[i]!='|') i++;
            w_osoba->adres=linia.substr(j,i-j);
            w_osoba->nastepnaOsoba=PoczatekListyOsob;
            w_osoba->poprzedniaOsoba=NULL;
            if (w_osoba->nastepnaOsoba!=NULL ) w_osoba->nastepnaOsoba->poprzedniaOsoba=w_osoba;
            PoczatekListyOsob=w_osoba;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.  ! " << endl;
        system("pause");
    }
    return PoczatekListyOsob;
}

vector < Uzytkownik > wczytajUzytkownikowZPliku(void){
    vector<Uzytkownik> uzytkownicy;
    string linia,login, haslo,pomocniczy;
    Uzytkownik uzytkownik;
    int id;
    plik.open("ListaUzytkownikow.txt",ios::in);
    if(plik.good()==true){
        while(getline(plik,linia)){
            int i=0,j=0;
            while(linia[i]!='|') i++;
            pomocniczy=linia.substr(0,i);
            id = atoi(pomocniczy.c_str());
            j=++i;
            while(linia[i]!='|') i++;
            login=linia.substr(j,i-j);
            j=++i;
            while(linia[i]!='|') i++;
            haslo=linia.substr(j,i-j);
            uzytkownik.numerID=id;
            uzytkownik.login=login;
            uzytkownik.haslo=haslo;
            uzytkownicy.push_back(uzytkownik);
        }
    }
    else
    {
            cout<<"Blad odczytu pliku";
            system("pause");
    }
    plik.close();
    return uzytkownicy;
}

bool sprawdzCzyIstniejeTakiLogin(vector < Uzytkownik > uzytkownicy,string login)
{
    int dlugoscWektoraUzytkownikow=uzytkownicy.size();
    for(int i=0;i<dlugoscWektoraUzytkownikow;i++){
        if(uzytkownicy[i].login==login) return true;
    }
    return false;
}

void wyswietlWektor(vector<Uzytkownik> wektorDoWyswietlenia)
{
    int rozmiar=wektorDoWyswietlenia.size();
    for(int i=0;i<rozmiar;i++)
    {
        cout<<wektorDoWyswietlenia[i].numerID<<endl<<wektorDoWyswietlenia[i].login<<endl<<wektorDoWyswietlenia[i].haslo<<endl<<endl;
    }
}

void zapiszUzytkownikowDoPliku(vector<Uzytkownik> uzytkownicy)
{
    string linia,idString;
    //plik.close();
    plik.open("ListaUzytkownikow.txt",ios::out|ios::trunc);
    if(plik.good()==true)
    {
        int rozmiarWektoraUzytkownikow=uzytkownicy.size();
        for(int i=0; i<rozmiarWektoraUzytkownikow; i++)
        {
            idString=to_string(uzytkownicy[i].numerID);
            linia=idString+'|'+uzytkownicy[i].login+'|'+uzytkownicy[i].haslo+'|';
            plik<<linia<<endl;
        }
    }
    plik.close();
}

vector < Uzytkownik > rejestracja(vector < Uzytkownik > uzytkownicy)
{
    string login, haslo;
    int rozmiar=uzytkownicy.size();
    int noweID;
    if(!(uzytkownicy.empty())) noweID=uzytkownicy[rozmiar-1].numerID+1;
    else noweID=1;
    Uzytkownik uzytkownik;
    system("cls");
    cout << "Ksiega adresowa" << endl<<endl;
    cout<<"Podaj login: ";
    cin>>login;
    while(sprawdzCzyIstniejeTakiLogin(uzytkownicy,login))
    {
        cout<<endl<<"Podany login juz istnieje !"<<endl<<"Wprowadz login ponownie: ";
        cin>>login;
    }
    uzytkownik.login=login;
    cout<<"Podaj haslo: ";
    cin>>haslo;
    uzytkownik.haslo=haslo;
    uzytkownik.numerID=noweID;
    uzytkownicy.push_back(uzytkownik);
    zapiszUzytkownikowDoPliku(uzytkownicy);
    return uzytkownicy;
}

int zaloguj(vector < Uzytkownik > uzytkownicy)
{
    string login,haslo;
    int id=0;
    int rozmiar=uzytkownicy.size();
    system("cls");
    cout << "Ksiega adresowa" << endl<<endl;
    cout<<"Podaj login: ";
    cin>>login;
    if(sprawdzCzyIstniejeTakiLogin(uzytkownicy , login)){
        cout<<"Podaj haslo: ";
        cin>>haslo;
        for(int i=0;i<rozmiar;i++)
        {
            if(uzytkownicy[i].login==login)
            {
                cout<<"Udalo sie zalogowac !"<<endl<<"Twoj numer ID to:"<<uzytkownicy[i].numerID;
                system("pause");
                return uzytkownicy[i].numerID;
            }
        }

    }
    else cout<<"Nie ma uzytkownika o takim loginie !";
    return id;
}

int main()
{
    Osoba * PoczatekListyOsob=NULL;
    int pozycjaMenu=0;
    int IdOgolne=0;
    bool czyZalogowano=false;
    vector <Uzytkownik> uzytkownicy;
    plik.close();
    uzytkownicy=wczytajUzytkownikowZPliku();
    while(true)
    {
        system("cls");
        cout << "Ksiega adresowa" << endl<<endl;
        cout<<"1. Logowanie"<<endl<<"2. Rejestracja"<<endl<<"3. Zakoncz prace"<<endl<<endl<<"Twoj wybor: ";
        cin>>pozycjaMenu;
        switch(pozycjaMenu)
            {
            case 1:
                {
                    IdOgolne=zaloguj(uzytkownicy);
                    if(IdOgolne!=0) czyZalogowano=true;
                    PoczatekListyOsob=wczytajDaneZPliku(PoczatekListyOsob,IdOgolne);
                    break;
                }
            case 2:
                {
                    uzytkownicy=rejestracja(uzytkownicy);
                    break;
                }
            case 3:
                {
                    exit(0);
                }
            }
        while(czyZalogowano)
        {

            pozycjaMenu=0;
            system("cls");
            cout << "Ksiega adresowa" << endl<<endl;
            cout << "1. Dodaj nowa osobe"<<endl<<"2. Wyszukaj osobe"<<endl<<"3. Wyswietl liste osob"<<endl<<"4. Wyloguj"<<endl<<endl<<"Twoj wybor: ";
            cin>>pozycjaMenu;
            switch(pozycjaMenu)
            {
            case 1:
            {
                PoczatekListyOsob=dodajOsobe(PoczatekListyOsob,IdOgolne);
                break;
            }
            case 2:
            {
                wyszukajOsobe(PoczatekListyOsob,IdOgolne);
                break;
            }
            case 3:
            {
                wyswietlListe(PoczatekListyOsob);
                break;
            }
            case 4:
            {
                IdOgolne=0;
                czyZalogowano=false;
                PoczatekListyOsob=NULL;
                break;
            }
            }
        }
    }
}
