#pragma once
#include "stdafx.h"
class Macierz
{
protected:
	unsigned int W, K;
	int **macierz;
public:
	Macierz(unsigned int _W, unsigned int _K);
	~Macierz();
	void kasuj();
	bool wstaw(unsigned int r, unsigned int c, unsigned int waga);
	void wyswietl();
	unsigned int wierzcholki();
	unsigned int krawedzie();
	int podaj_wage(int a, int b);
	Krawedz* podaj_min(int i);
};

