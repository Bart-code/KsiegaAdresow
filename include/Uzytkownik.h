#include <iostream>
using namespace std;

class Uzytkownik
{
    public:
        Uzytkownik();
        virtual ~Uzytkownik();
        void ustawIdUzytkownika(int);
        void ustawNazweUzytkownika(string);
        void ustawHasloUzytkownika(string);
        int pobierzIdUzytkownika();
        string pobierzNazweUzytkownika();
        string pobierzHasloUzytkownika();

    private:
        int idUzytkownika;
        string nazwaUzytkownika, hasloUzytkownika;
        static int NastepnyNumerId;
};

