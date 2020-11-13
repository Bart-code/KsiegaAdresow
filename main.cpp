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



fstream plik;

Osoba * dodajOsobe(Osoba * PoczatekListyOsob)
{
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::app);
    Osoba * w_osoba=new Osoba;
    if(PoczatekListyOsob==NULL){
        w_osoba->id=1;
    }
    else w_osoba->id=PoczatekListyOsob->id+1;
    plik<<w_osoba->id<<"|";
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


void zapiszListeDoPliku(Osoba * PoczatekListyOsob)
{
    Osoba *wybranaOsoba = PoczatekListyOsob;
    string linia,idString;
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::trunc);
    while(1)
    {
        if(wybranaOsoba->nastepnaOsoba==NULL) break;
        else wybranaOsoba=wybranaOsoba->nastepnaOsoba;
    }

    while(wybranaOsoba!=NULL)
    {
        linia="";
        idString=to_string(wybranaOsoba->id);
        linia = idString + '|' + wybranaOsoba->imie + '|' + wybranaOsoba->nazwisko + '|' + wybranaOsoba->numerTelefonu + '|' +wybranaOsoba->email + '|' + wybranaOsoba->adres + '|';
        plik<<linia<<endl;
        wybranaOsoba=wybranaOsoba->poprzedniaOsoba;
    }
    plik.close();
}


void edytujDaneOsoby(Osoba * konkretnaOsoba,Osoba * PoczatekListyOsob)
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
    zapiszListeDoPliku(PoczatekListyOsob);
}

bool usunOsobeZListy(Osoba * konkretnaOsoba,Osoba * PoczatekListyOsob)
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
    zapiszListeDoPliku(PoczatekListyOsob);
    return true;
}

void wyszukajOsobe(Osoba * PoczatekListyOsob)
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
                else if(pozycjaMenu==2) edytujDaneOsoby(pomocnicza,PoczatekListyOsob);
                else if(pozycjaMenu==3) if(usunOsobeZListy(pomocnicza,PoczatekListyOsob)) return;
            }
        }
        pomocnicza=pomocnicza->nastepnaOsoba;
    }
}

Osoba * wczytajDaneZPliku(Osoba * PoczatekListyOsob)
{
    if(plik.good()==true)
    {
        plik.open("ksiazkaAdresowa.txt",ios::in);
        string linia,pomocniczy;

        while(getline(plik,linia))
        {
            Osoba * w_osoba=new Osoba;
            int i=0,j=0;
            while(linia[i]!='|') i++;
            pomocniczy=linia.substr(0,i);
            w_osoba->id = atoi(pomocniczy.c_str());
            j=++i;
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
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    return PoczatekListyOsob;
}

bool sprawdzCzyIstniejeTakiLogin(vector<Uzytkownik> uzytkownicy,string login){
    int dlugoscWektoraUzytkownikow=uzytkownicy.size();
    for(int i=0;i<dlugoscWektoraUzytkownikow;i++){
        if(uzytkownicy[i].login==login) return true;
    }
    return false;
}

vector<Uzytkownik> rejestracja(vector<Uzytkownik> uzytkownicy){
    string login, haslo;
    Uzytkownik uzytkownik;
    system("cls");
    cout << "Ksiega adresowa" << endl<<endl;
    cout<<"Podaj login: ";
    cin>>login;
    while(sprawdzCzyIstniejeTakiLogin(uzytkownicy,login)){
        cout<<endl<<"Podany login juz istnieje !"<<endl<<"Wprowadz login ponownie: ";
        cin>>login;
    }
    uzytkownik.login=login;
    cout<<"Podaj haslo: ";
    cin>>haslo;
    uzytkownik.haslo=haslo;
    uzytkownicy.push_back(uzytkownik);
    return uzytkownicy;
}

int main()
{
    Osoba * PoczatekListyOsob=NULL;
    int pozycjaMenu=0;
    int IdOgolne=0;
    bool czyZalogowano=false;
    PoczatekListyOsob=wczytajDaneZPliku(PoczatekListyOsob);
    vector <Uzytkownik> uzytkownicy;
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
                PoczatekListyOsob=dodajOsobe(PoczatekListyOsob);
                break;
            }
            case 2:
            {
                wyszukajOsobe(PoczatekListyOsob);
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
                break;
            }
            }
        }
    }
}
