#pragma once
#include "stdafx.h"
class Plecak
{
	int wielkosc;
	int zajete;
	int waga;
	Element* lista;
public:
	Plecak(int _wielkosc, int _ilosc);
	~Plecak();
	bool sprawdz(Element kandydat);
	void dodaj(Element* element);
	void drukuj();
	bool sprawdz();
	int podaj_wage();
};

