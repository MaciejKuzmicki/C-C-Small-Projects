#include <iostream>
#include <string>

using namespace std;

void opis();

void wypisz(string wejscie, int pozycja, int a, int stan);

string ciag(int m, int n);

int roznica(string wejscie, int a);

int mat(int m, int n);

void mt(string wejscie, int stan, int pozycja, int poz, int pozycja1, int m, int n);


int main()
{
	opis();
	int m, n, stan =0, pozycja = 0, poz =0, pozycja1=0;
	cout << "Wczytaj liczbe m: ";
	cin >> m;
	cout << "Wczytaj liczbe n: ";
	cin >> n;
	if (m < 0 || n < 0)
	{
		cout << "Liczby musza byc nieujemne";
		return 0;
	}
	cout << "Wygenerowany ciag: "<< ciag(m, n) << endl;
	cout << "q0 " << ciag(m,n);
	mt(ciag(m, n), stan, pozycja, poz, pozycja1,m,n);
	return 0;
}

void opis()
{
	cout << " Emulator maszyny Turinga obliczajacy roznice wlasciwa" << endl;

	cout << " Roznica wlasciwa: " << endl;
	cout << "             | m - n dla m >= n" << endl;
	cout << "     m - n = |               " << endl;
	cout << "             | 0     dla m < n " << endl << endl;

	cout << " Postac maszyny Turinga:" << endl;
	cout << "     M = ({q0, q1, q2, q3, q4, a5, a6}, {0, 1}, {0, 1, B}, d, q0, B, 0)" << endl << endl; // d = δ

	cout << " Tablica przejsc:" << endl;
	cout << "     ==========================================" << endl;
	cout << "     |   d   |     0    |     1    |     B    |" << endl;
	cout << "     ==========================================" << endl;
	cout << "     |   q0  | (q1,B,P) | (q5,B,P) |     -    |" << endl;
	cout << "     |   q1  | (q1,O,P) | (q2,1,P) |     -    |" << endl;
	cout << "     |   q2  | (q3,1,L) | (q2,1,P) | (q4,B,L) |" << endl;
	cout << "     |   q3  | (q3,0,L) | (q3,1,L) | (q0,B,P) |" << endl;
	cout << "     |   q4  | (q4,0,L) | (q4,B,L) | (q6,0,P) |" << endl;
	cout << "     |   q5  | (q5,B,P) | (q5,B,P) | (q6,B,P) |" << endl;
	cout << "     |   q6  |     -    |     -    |     -    |" << endl;
	cout << "     ==========================================" << endl;
}

void wypisz(string wejscie, int pozycja, int a, int stan)
{
	string cpy = wejscie;
	int acpy = a - 1;
	int pcpy = pozycja;
	for (acpy; acpy >= pcpy; acpy--)
	{
		if (cpy[acpy] != 'B') break;
		if (cpy[acpy] == 'B') cpy[acpy] = ' ';
	}
	int i = 0;
	cout << " |- ";
	for (i; i < pozycja; i++) cout << wejscie[i];
	cout << " q" << stan << " ";
	for (i; i < a; i++) cout << cpy[i];
}

string ciag(int m, int n)
{
	string wejscie = "";
	for (int i = 0; i < m; i++) wejscie += '0';
	wejscie += '1';
	for (int i = 0; i < n; i++) wejscie += '0';
	return wejscie;
}

int roznica(string wejscie, int a)
{
	int wynik = 0;
	for (int i = 0; i < a; i++)
	{
		if (wejscie[i] == '0') wynik++;
	}
	return wynik;
}

int mat(int m, int n)
{
	if (m >= n) return m - n;
	else return 0;
}

void mt(string wejscie, int stan, int pozycja, int poz, int pozycja1, int m, int n)
{
	int a = wejscie.length();
	if (pozycja > a - 1) pozycja1 -= a;
	if ((stan == 6) || (stan == 0 && wejscie[pozycja1] == 'B') || (stan == 1 && wejscie[pozycja1] == 'B'))
	{
		cout << endl;
		cout << "Ciag zostal zaakceptowany" << endl;
		cout << "Wynik roznicy wlasciwej liczb " << m << " i " << n << " to " << roznica(wejscie, a) << endl;
		if (mat(m, n) == roznica(wejscie, a)) cout << "Wynik ten jest zgodny z matematycznym opisem roznicy wlasciwej";
		else cout << "Wynik ten nie jest zgodny z matematycznym opisem roznicy wlasciwej";
		return;
	}
	else if (stan == 0 && wejscie[pozycja1] == '0')
	{
		stan = 1;
		wejscie[pozycja] = 'B';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 0 && wejscie[pozycja1] == '1')
	{
		stan = 5;
		wejscie[pozycja] = 'B';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);

	}
	else if (stan == 1 && wejscie[pozycja1] == '0')
	{
		stan = 1;
		wejscie[pozycja] = '0';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 1 && wejscie[pozycja1] == '1')
	{
		stan = 2;
		wejscie[pozycja] = '1';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 2 && wejscie[pozycja1] == '0')
	{
		stan = 3;
		wejscie[pozycja] = '1';
		pozycja--;
		pozycja1--;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 2 && wejscie[pozycja1] == '1')
	{
		stan = 2;
		wejscie[pozycja] = '1';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 2 && wejscie[pozycja1] == 'B')
	{
		stan = 4;
		wejscie[pozycja] = 'B';
		pozycja--;
		pozycja1--;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 3 && wejscie[pozycja1] == '0')
	{
		stan = 3;
		wejscie[pozycja] = '0';
		pozycja--;
		pozycja1--;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 3 && wejscie[pozycja1] == '1')
	{
		stan = 3;
		wejscie[pozycja] = '1';
		pozycja--;
		pozycja1--;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 3 && wejscie[pozycja1] == 'B')
	{
		stan = 0;
		wejscie[pozycja] = 'B';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 4 && wejscie[pozycja1] == '0')
	{
		stan = 4;
		wejscie[pozycja] = '0';
		pozycja--;
		pozycja1--;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 4 && wejscie[pozycja1] == '1')
	{
		stan = 4;
		wejscie[pozycja] = 'B';
		pozycja--;
		pozycja1--;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 4 && wejscie[pozycja1] == 'B')
	{
		stan = 6;
		wejscie[pozycja] = '0';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 5 && wejscie[pozycja1] == '0')
	{
		stan = 5;
		wejscie[pozycja] = 'B';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 5 && wejscie[pozycja1] == '1')
	{
		stan = 5;
		wejscie[pozycja] = 'B';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	else if (stan == 5 && wejscie[pozycja1] == 'B')
	{
		stan = 6;
		wejscie[pozycja] = 'B';
		pozycja++;
		pozycja1++;
		int a = wejscie.length();
		wypisz(wejscie, pozycja, a, stan);
	}
	if (pozycja < a)pozycja1 = pozycja;
	mt(wejscie, stan, pozycja, poz, pozycja1, m, n);
}

