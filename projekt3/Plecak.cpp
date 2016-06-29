#include "stdafx.h"
#include "Plecak.h"


Plecak::Plecak(int _wielkosc, int _ilosc)
{
	lista = new Element[_ilosc];
	for (int i = 0; i < _ilosc; i++){
		lista[i].zeruj();
	}
	wielkosc = _wielkosc;
}

Plecak::~Plecak()
{
	delete[] lista;
}

bool Plecak::sprawdz(Element kandydat){
	return (zajete + kandydat.podaj_wielkosc() <= wielkosc);
}

void Plecak::dodaj(Element* element){
	waga += element->podaj_wage();
	zajete += element->podaj_wielkosc();
	int i = 0;
	while (lista[i].podaj_wielkosc() != 0){
		i++;
	}
	lista[i] = *element;
}

void Plecak::drukuj(){
	cout << "Elementy:\nw s\n";
	for (int i = 0; lista[i].podaj_wielkosc() != 0; i++){
		lista[i].drukuj();
	}
	cout << "Plecak:\nw s\n";
	cout << waga << " " << zajete << endl;
}

bool Plecak::sprawdz(){
	return zajete <= wielkosc;
}

int Plecak::podaj_wage(){
	return waga;
}