#pragma once
class Element
{
	int wielkosc;
	int waga;
public:
	Element();
	~Element();
	void laduj(int w, int s);
	void zeruj();
	int podaj_wage();
	int podaj_wielkosc();
	void drukuj();
	double podaj_iloraz();
};

