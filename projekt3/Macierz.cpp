#include "stdafx.h"
#include "Macierz.h"

Macierz::Macierz(unsigned int _W, unsigned int _K)
{
	W = _W;
	K = _K;
	macierz = new int*[W];
	for (int i = 0; i < W; i++){
		macierz[i] = new int[W];
		for (int j = 0; j < W; j++){
			macierz[i][j] = 0;
		}
	}
}

Macierz::~Macierz()
{
}

void Macierz::kasuj(){
	for (int i = 0; i < W; i++){
		delete[] macierz[i];
	}
	delete[] macierz;
}

bool Macierz::wstaw(unsigned int r, unsigned int c, unsigned int waga){
	if (macierz[r][c]>0)				//czy krawêdz istnieje
		return false;
	macierz[r][c] = waga;
	return true;
}

void Macierz::wyswietl(){
	for (int i = 0; i < W; i++){
		for (int j = 0; j < W; j++){
			cout << macierz[i][j] << " ";
		}
		cout << endl;
	}
}

unsigned int Macierz::wierzcholki(){
	return W;
}

unsigned int Macierz::krawedzie(){
	return K;
}

int Macierz::podaj_wage(int a, int b){
	return macierz[a][b];
}

Krawedz* Macierz::podaj_min(int a){
	Krawedz* ret = new Krawedz[W];
	for (int i = 0; i < W; i++)
		ret[i].wstaw(a, i, macierz[a][i]);
	int i = 0;
	Krawedz x;
	for (int j = W - 2; j >= 0; j--){
		x = ret[j];
		i = j + 1;
		while ((i < W) && (x.podajwage() > ret[i].podajwage())){
			ret[i - 1] = ret[i];
			i++;
		}
		ret[i - 1] = x;
	}
	return ret;
}