#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

int check(string e, string f, int g, int h)
{
	int p = 0;
	int o = min(g, h);
	for (int i = 0; i < o; i++)
	{
		if (e[i] != f[i]) p = 1;
	}
	if (p == 0 && g == h) return 2;
	if (p == 0) return 1;
	return 0;
}


int main()
{
	cout << "Podaj ilosc lancuchow znajdujaca sie w listach: " << endl;
	int a;
	cin >> a;
	string* tab = new string[a];
	string* tab1 = new string[a];
	cout << "Wczytaj liste A: " << endl;
	for (int i = 0; i < a; i++) cin >> tab[i];
	cout << "Wczytaj liste B: " << endl;
	for (int i = 0; i < a; i++) cin >> tab1[i];
	string c = "";
	string d = "";
	vector <int> wektor;
	int ster = 1;
	while (ster)
	{
		cout << "Aby zakonczyc program wpisz 0, aby kontynuowac podaj wartosc od 1 do " << a << ":" <<endl;
		cin >> ster;
		if (ster > a)
		{
			cout << "Podano zla wartosc, program konczy swoje dzialanie";
			return 0;
		}
		if (ster == 0)
		{
			cout << "Zakonczono dzialanie programu";
			return 0;
		}
		c += tab[ster - 1];
		d += tab1[ster - 1];
		wektor.push_back(ster);
		int z = c.length();
		int w = d.length();
		int r = check(c, d, z, w);
		if (r == 2)
		{
			cout << "Znaleziono rozwiazanie: ";
			for (int i = 0; i < wektor.size(); i++) cout << wektor[i] << " ";
			cout << endl;
			cout << "Utworzony ciag dla indeksow podanych wyzej to: " << c;
			return 0;
		}
		if (r == 1)
		{
			cout << "Szukamy dalej rozwiazania: " << endl;
			cout << "Pierwszy ciag: "<<c << endl;
			cout << "Drugi ciag: " << d << endl;
		}
		if (r == 0)
		{
			cout << "Brak rozwiazania, ciagi " << c << " oraz " << d << " roznia sie od siebie";
			return 0;
		}
	}
		
	return 0;
}