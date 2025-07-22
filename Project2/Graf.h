#ifndef Graf_H
#define Graf_H
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
class Graf
{

	struct Grana{
		int dest; 
		double w;
	};

	struct Korisnik{
		//odmah ga inicijalizujem na 0 jer sam imao warning ali radim to i u konstruktoru
		int optr = 0; //odnos pointer 
		string ime;
	};

	int cntCvorova; //koliko trenutno ima cvorova
	int cntGrana; //koliko trenutno ima grana
	Korisnik* cvorovi; 
	Grana* odnosi; 
	int n; //broj cvorova
	int e; //broj grana

public:
	Graf(int n, int e); //inicijalizuje graf - zavrseno
	~Graf(); //destruktor - zavrseno
	void povecaj_cvorovi(int novon); //povecava niz cvorovi - zavrseno
	void povecaj_grane(int novoe); //povecava niz grane - zavrseno
	void addCvor(string& ime); //zavrseno
	void addGranu(string& ime, string& dest, double w);
	void uklanjanjeGrane(string& ime, string& dest);
	void uklanjanjeCvora(string& ime);
	void shiftr(Grana* arr, int size, int n); //dodajem elem
	void shiftl(Grana* arr, int size, int dest); //gubim elem
    friend ostream& operator<< (ostream& stream, Graf& graf);
    void lajkuj(string& k1, string& k2);
    void dfs(int start, bool *visited, int* stek, int& sp, int* komp, int& kompsize);
    void najvecakomp();
    void najverovatnijiPut(string& startime, string& endime);
    double** napraviMatricu();
    void najuticajnijiKorisnik(int uticajni);
};
#endif
