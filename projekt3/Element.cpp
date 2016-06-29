#include "stdafx.h"
#include "Element.h"


Element::Element()
{
}

Element::~Element()
{
}

void Element::laduj(int w, int s){
	waga = w;
	wielkosc = s;
}

int Element::podaj_wage(){
	return waga;
}

int Element::podaj_wielkosc(){
	return wielkosc;
}

void Element::drukuj(){
	cout << waga << " " << wielkosc << endl;
}

double Element::podaj_iloraz(){
	double stosunek;
	stosunek = (double)waga / (double)wielkosc;
	return stosunek;
}

void Element::zeruj(){
	waga = 0;
	wielkosc = 0;
}