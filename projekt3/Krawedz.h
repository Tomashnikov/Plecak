#pragma once
class Krawedz
{
	int w1;
	int w2;
	int waga;
public:
	Krawedz();
	void wstaw(int a, int b, int w);
	int podajwage();
	int podaj_w1();
	int podaj_w2();
	~Krawedz();
	void reset();
	void drukuj();
	void operator=(Krawedz a);
};

