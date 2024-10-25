#include <iostream>

using namespace std;

class Osoba{
public:
    string imie;
    string nazwisko;
    int id;

    Osoba(string imie, string nazwisko, int id):imie(imie), nazwisko(nazwisko), id(id){}

    virtual void wyswietlInformacje(){
        cout<< "Imie: " <<imie<< ", Nazwisko: "<<nazwisko<<", ID: "<<id<<endl;
    }

    virtual void edytujDane(){
        cout<< " Nowe imie: ";
        cin>> imie;
        cout<< " Nowe nazwisko: ";
        cin>> nazwisko;
        cout<< " Nowy nr ID: ";
        cin>> id;
    }

    virtual int typOsoby(){
        return 0;
    }
};

class Wykladowca:public Osoba{
public:
    string tytul;

    Wykladowca(string imie, string nazwisko, int id, string tytul):Osoba(imie, nazwisko, id), tytul(tytul){}

    void wyswietlInformacje()override{
        Osoba::wyswietlInformacje();
        cout<< "Tytul: "<<tytul<<endl;
    }

    void edytujDane()override{
        Osoba::edytujDane();
        cout<< "Podaj nowy tytul: ";
        cin>> tytul;
    }

    int typOsoby()override{
        return 1;
    }
};

class StudentLicencjackie:public Osoba{
public:
    int rokStudiow;

    StudentLicencjackie(string imie, string nazwisko, int id, int rokStudiow):Osoba(imie, nazwisko, id), rokStudiow(rokStudiow){}

    void wyswietlInformacje()override{
        Osoba::wyswietlInformacje();
        cout<< "Rok studiow: "<<rokStudiow<< endl;
    }

    void edytujDane()override{
        Osoba::edytujDane();
        cout<< "Podaj nowy rok studiow: ";
        cin>>rokStudiow;
    }

    int typOsoby()override{
        return 2;
    }
};

class StudentMagisterskie:public Osoba{
public:
    int idOpiekuna;

    StudentMagisterskie(string imie, string nazwisko, int id, int idOpiekuna):Osoba(imie, nazwisko, id), idOpiekuna(idOpiekuna){}

    void wyswietlInformacje()override{
        Osoba::wyswietlInformacje();
        cout<< "ID opiekuna: "<<idOpiekuna<<endl;
    }

    void edytujDane() override{
        Osoba::edytujDane();
        cout<< "Podaj nowe ID opiekuna: ";
        cin>>idOpiekuna;
    }

    int typOsoby()override{
        return 3;
    }
};

class PracownikAdministracyjny:public Osoba{
public:
    string dzial;

    PracownikAdministracyjny(string imie, string nazwisko, int id, string dzial):Osoba(imie, nazwisko, id), dzial(dzial){}

    void wyswietlInformacje() override{
        Osoba::wyswietlInformacje();
        cout<< "Dzial " << dzial<<endl;
    }

    void edytujDane()override{
        Osoba::edytujDane();
        cout << "Podaj nowy dzial: ";
        cin >> dzial;
    }

    int typOsoby()override{
        return 4;
    }
};

const int MAX_OSOB = 45;
Osoba* osoby[MAX_OSOB];
int liczbaOsob = 0;

void dodajOsobe(){
    if (liczbaOsob>=MAX_OSOB){
        cout << "Limit osob osiagniety." <<endl;
        return;
    }

    int stanowisko, id;
    string imie, nazwisko, tytul, dzial;
    int rokStudiow, idOpiekuna;

    cout<< "Wybierz stanowisko osoby (1 - Wykladowca, 2 - Student Licencjackie, 3 - Student Magisterskie, 4 - Pracownik Administracyjny): ";
    cin>> stanowisko;
    cout<< "Podaj imie: ";
    cin>> imie;
    cout<< "Podaj nazwisko: ";
    cin>> nazwisko;
    cout<< "Podaj ID: ";
    cin>> id;

    switch (stanowisko){
        case 1:
            cout<< "Podaj tytul naukowy: ";
            cin>> tytul;
            osoby[liczbaOsob++] = new Wykladowca(imie, nazwisko, id, tytul);
            break;
        case 2:
            cout<< "Podaj rok studiow: ";
            cin>> rokStudiow;
            osoby[liczbaOsob++] = new StudentLicencjackie(imie, nazwisko, id, rokStudiow);
            break;
        case 3:
            cout<< "Podaj ID opiekuna: ";
            cin>> idOpiekuna;
            osoby[liczbaOsob++] = new StudentMagisterskie(imie, nazwisko, id, idOpiekuna);
            break;
        case 4:
            cout<< "Podaj dzial: ";
            cin>> dzial;
            osoby[liczbaOsob++] = new PracownikAdministracyjny(imie, nazwisko, id, dzial);
            break;
        default:
            cout<< "Nieprawidlowy wybor!" << endl;
            break;
    }
}

void wyswietlWszystkieOsoby(){
    for (int i=0; i<liczbaOsob; i++){
        osoby[i]->wyswietlInformacje();
    }
}

void wyswietlGrupy(int typ){
    for (int i=0; i<liczbaOsob; i++){
        if (osoby[i]->typOsoby() == typ){
            osoby[i]->wyswietlInformacje();
        }
    }
}

void edytujOsobe(){
    int id;
    cout<< "Podaj ID osoby do edycji: ";
    cin>> id;
    for (int i=0; i<liczbaOsob; i++){
        if(osoby[i]->id==id){
            osoby[i]->edytujDane();
            return;
        }
    }
    cout<<"Nie znaleziono osoby o podanym numerze ID!"<<endl;
}

void usunOsobe(){
    int id;
    cout<<" ID osoby do usuniecia: ";
    cin>>id;
    for(int i = 0; i < liczbaOsob; i++){
        if (osoby[i]->id == id){
            delete osoby[i];
            for (int j=i; j<liczbaOsob-1; j++){
                osoby[j]=osoby[j + 1];
            }
            liczbaOsob--;
            cout<<"Osoba zostala usunieta."<<endl;
            return;
        }
    }
    cout<<"Nie ma osoby o tym ID!"<<endl;
}

int main(){
    int wybierz;
    do{
        cout<< "1. Dodaj osobe\n";
        cout<< "2. Wyswietl wszystkie osoby\n";
        cout<< "3. Wyswietl wykladowcow\n";
        cout<< "4. Wyswietl studentow licencjat\n";
        cout<< "5. Wyswietl studentow magister\n";
        cout<< "6. Wyswietl pracownikow administracyjnych\n";
        cout<< "7. Edytuj dane osoby\n";
        cout<< "8. Usun osobe\n";
        cout<< "9. Wyjdz\n";
        cout<< "Wybierz opcje: ";
        cin>> wybierz;

        switch (wybierz) {
            case 1:
                dodajOsobe();
                break;
            case 2:
                wyswietlWszystkieOsoby();
                break;
            case 3:
                wyswietlGrupy(1);
                break;
            case 4:
                wyswietlGrupy(2);
                break;
            case 5:
                wyswietlGrupy(3);
                break;
            case 6:
                wyswietlGrupy(4);
                break;
            case 7:
                edytujOsobe();
                break;
            case 8:
                usunOsobe();
                break;
            case 9:
                break;
            default:
                cout<< "Nieprawidlowa opcja, sprobuj ponownie."<<endl;
                break;
        }
    } while(wybierz!= 9);


    for (int i=0; i< liczbaOsob; i++){
        delete osoby[i];
    }

    return 0;
}
