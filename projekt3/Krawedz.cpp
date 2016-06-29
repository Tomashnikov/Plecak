#include "stdafx.h"
#include "Krawedz.h"


Krawedz::Krawedz(){
	w1 = 0;
	w2 = 0;
	waga = 0;
}

void Krawedz::wstaw(int a, int b, int w)
{
	w1 = a;
	w2 = b;
	waga = w;
}

int Krawedz::podaj_w1(){
	return w1;
}

int Krawedz::podaj_w2(){
	return w2;
}

Krawedz::~Krawedz()
{
}

int Krawedz::podajwage(){
	return waga;
}

void Krawedz::reset(){
	w1 = 0;
	w2 = 0;
	waga = 0;
}

void Krawedz::drukuj(){
	cout << w1 << " " << w2 << " " << waga << endl;
}

void Krawedz::operator=(Krawedz a){
	w1 = a.w1;
	w2 = a.w2;
	waga = a.waga;
}
