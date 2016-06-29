// projekt3.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
void P_plecakowy();
void P_przeglad(Element* dana, int ilosc, int wielkosc);
void P_optymalizacyjny(Element* dana, int ilosc, int wielkosc);
void K_komiwojazer();
void K_przeglad(Macierz dane);
void K_optymalizacyjny(Macierz dane);

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	while (true){
		char zn;
		cout << "Podaj opcje(p-problem plecakowy k-komiwojazer z-zamknij): ";
		cin >> zn;
		switch (zn){
		case 'p': P_plecakowy(); break;
		case 'k': K_komiwojazer(); break;
		case 'z': return 0;
		default: cout << "Brak opcji!" << endl; break;
		}
	}
	return 0;
}

void P_plecakowy(){
	fstream plik;
	string nazwa;
	bool error = false;
	do{
		if (error){
			cout << "Nie ma takiego pliku!\n";
		}
		cout << "Podaj nazwe pliku: ";
		cin >> nazwa;
		nazwa += ".txt";
		plik.open(nazwa);
		error = true;
	} while (!plik.is_open());
	int wielkosc, ilosc;
	int a, b;
	plik >> wielkosc;
	plik >> ilosc;
	Plecak plecak(wielkosc, ilosc);
	Element* elementy = new Element[ilosc];
	cout << "Elementy:\nw s\n";
	for (int i = 0; i < ilosc; i++){
		Element* nowy = new Element();
		plik >> a;
		plik >> b;
		nowy->laduj(b, a);
		nowy->drukuj();
		elementy[i] = *nowy;
	}
	while (true){
		char zn;
		cout << "Podaj opcje(p-przeglad zupelny z-zachlanny w-wstecz): ";
		cin >> zn;
		switch (zn){
		case 'p': P_przeglad(elementy, ilosc, wielkosc); break;
		case 'z': P_optymalizacyjny(elementy, ilosc, wielkosc); break;
		case 'w': return;
		default: cout << "Brak opcji!" << endl; break;
		}
	}
}

void P_przeglad(Element* dana, int ilosc, int wielkosc){
	Pomiar czas;
	czas.start();
	bool* wyst¹pienie = new bool[ilosc];
	for (int i = 0; i < ilosc; i++)
		wyst¹pienie[i] = false;
	int i = 0;
	int waga, rozmiar;
	Plecak* rozwiazanie = new Plecak(wielkosc, ilosc);
	bool koniec = false;
	while (!koniec){
		Plecak* wygenerowane = new Plecak(wielkosc, ilosc);
		i = waga = rozmiar = 0;
		while (wyst¹pienie[i]){
			wyst¹pienie[i] = false;
			i++;
			if (i >= ilosc){
				koniec = true;
				break;
			}
		}
		if (koniec)
			break;
		wyst¹pienie[i] = true;
		for (int i = 0; i < ilosc; i++){
			if (wyst¹pienie[i]){
				wygenerowane->dodaj(&dana[i]);
			}
		}
		if (wygenerowane->sprawdz() && rozwiazanie->podaj_wage()<wygenerowane->podaj_wage()){
			delete rozwiazanie;
			rozwiazanie = wygenerowane;
		}
		else
			delete wygenerowane;
	}
	delete[] wyst¹pienie;
	rozwiazanie->drukuj();
	cout << czas.podaj() << endl;
}

void P_optymalizacyjny(Element* dana, int ilosc, int wielkosc){
	Pomiar czas;
	czas.start();
	double* stosunek = new double[ilosc];
	Plecak* rozwiazanie = new Plecak(wielkosc, ilosc);
	for (int i = 0; i < ilosc; i++){
		stosunek[i] = dana[i].podaj_iloraz();
	}
	int nr;
	double max;
	bool koniec = false;
	while (!koniec){
		max = stosunek[0];
		nr = 0;
		for (int i = 1; i < ilosc; i++){
			if (max < stosunek[i]){
				max = stosunek[i];
				nr = i;
			}
		}
		if (max == 0){
			koniec = true;
			break;
		}
		stosunek[nr] = 0;
		if (rozwiazanie->sprawdz(dana[nr])){
			rozwiazanie->dodaj(&dana[nr]);
		}
	}
	rozwiazanie->drukuj();
	cout << czas.podaj() << endl;
}

void K_komiwojazer(){
	fstream plik;
	string nazwa;
	bool error = false;
	do{
		if (error){
			cout << "Nie ma takiego pliku!\n";
		}
		cout << "Podaj nazwe pliku: ";
		cin >> nazwa;
		nazwa += ".txt";
		plik.open(nazwa);
		error = true;
	} while (!plik.is_open());
	unsigned int wierzcholki, krawedzie;
	int w;
	plik >> wierzcholki;
	plik >> krawedzie;
	krawedzie = wierzcholki*(wierzcholki - 1);
	Macierz graf(wierzcholki, krawedzie);
	for (unsigned int i = 0; i < wierzcholki; i++){
		for (int j = 0; j < wierzcholki; j++){
			plik >> w;
			graf.wstaw(i, j, w);
		}
	}
	graf.wyswietl();
	while (true){
		char zn;
		cout << "Podaj opcje(p-przeglad zupelny z-zachlanny w-wstecz): ";
		cin >> zn;
		switch (zn){
		case 'p': K_przeglad(graf); break;
		case 'z': K_optymalizacyjny(graf); break;
		case 'w': return;
		default: cout << "Brak opcji!" << endl; break;
		}
	}
}

void K_przeglad(Macierz dane){
	Pomiar czas;
	czas.start();
	int tmp;													//do sprawdzania
	bool odrzuc;
	int suma;
	int wierzcholki = dane.wierzcholki();
	int* wybór = new int[wierzcholki];
	bool* odwiedzone = new bool[wierzcholki];
	int sumarozwiazania = MAXINT;
	Krawedz* rozwiazanie = new Krawedz[wierzcholki];
	for (int i = 0; i < wierzcholki; i++){
		wybór[i] = 0;
	}
	unsigned long int kombnacje = wierzcholki;
	for (int j = 1; j < wierzcholki; j++)
		kombnacje *= wierzcholki;

	for (int j = 0; j<kombnacje; j++){
		Krawedz* kandydat = new Krawedz[wierzcholki];
		suma = 0;
		odrzuc = false;
		for (int i = 0; i <= wierzcholki; i++){					//generacja kombinacji
			wybór[i]++;
			if (wybór[i] == wierzcholki){
				wybór[i] = 0;
			}
			else
				break;
		}
		for (int i = 0; i < wierzcholki; i++){
			odwiedzone[i] = false;
			kandydat[i].wstaw(i, wybór[i], dane.podaj_wage(i, wybór[i]));
		}
		tmp = 0;
		for (int i = 0; i < wierzcholki; i++){					//sprawdzanie
			suma += kandydat[i].podajwage();
			tmp = kandydat[tmp].podaj_w2();
			if (!odwiedzone[tmp])
				odwiedzone[tmp] = true;
			else{
				odrzuc = true;
				delete[] kandydat;
				break;
			}
			if (kandydat[i].podajwage() == 0){
				odrzuc = true;
				delete[] kandydat;
				break;
			}
		}
		if (!odrzuc){
			if (suma < sumarozwiazania){						//aktualizacja jeœli lepsza kobinacja
				delete[] rozwiazanie;
				rozwiazanie = kandydat;
				sumarozwiazania = suma;
			}
			else{
				delete[] kandydat;
			}
		}
	}
	cout << "Krawedzie:\nV V w\n";
	for (int i = 0; i < wierzcholki; i++){
		rozwiazanie[i].drukuj();
	}
	cout << "Suma: " << sumarozwiazania << endl;
	cout << czas.podaj() << endl;
}

void K_optymalizacyjny(Macierz dane){
	Pomiar czas;
	czas.start();
	int wierzcholki = dane.wierzcholki();
	int tmp = 0;										//wierzcho³ek w którym jest algorytm
	int prog;
	bool* odwiedzone = new bool[wierzcholki];
	for (int i = 1; i < wierzcholki; i++){
		odwiedzone[i] = false;
	}
	odwiedzone[0] = true;
	Krawedz* rozwiazanie = new Krawedz[wierzcholki];
	Krawedz* podane = new Krawedz[wierzcholki];
	Krawedz ostatnia;

	for (int i = 0; i < wierzcholki - 1; i++){
		podane = dane.podaj_min(tmp);
		prog = 0;
		do{
			prog++;
			ostatnia = podane[prog];
		} while (odwiedzone[ostatnia.podaj_w2()]);
		odwiedzone[ostatnia.podaj_w2()] = true;

		rozwiazanie[i] = ostatnia;
		tmp = rozwiazanie[i].podaj_w2();
	}
	int waga = dane.podaj_wage(tmp, 0);
	int suma = 0;
	ostatnia.wstaw(tmp, 0, waga);
	rozwiazanie[wierzcholki - 1] = ostatnia;
	cout << "Krawedzie:\nV V w\n";
	for (int i = 0; i < wierzcholki; i++){
		rozwiazanie[i].drukuj();
		suma += rozwiazanie[i].podajwage();
	}
	cout << "Suma: " << suma << endl;
	cout << czas.podaj() << endl;
}