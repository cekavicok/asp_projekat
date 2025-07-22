#include <iostream>
#include <fstream>
#include "Graf.h"
using namespace std;



int main() {
    int izbor;
    string fajl;
    ifstream file;
    int maxC = 0;
    int maxG = 0;
    string cvorovi;
    string grancica;
    double w = 0;
    bool grafInitialized = false;
    Graf* g = nullptr;
    do {
        cout << "---------------------------------" << endl;
        cout << "1) Ucitaj graf iz fajla" << endl;
        cout << "2) Dodaj cvor" << endl;
        cout << "3) Dodaj granu" << endl;
        cout << "4) Ukloni cvor" << endl;
        cout << "5) Ukloni granu" << endl;
        cout << "6) Ispisi graf" << endl;
        cout << "7) Obrisi graf" << endl;
        cout << "8) Lajkuj objavu" << endl;
        cout << "9) Najveca komponenta grafa" << endl;
        cout << "10) Najverovatniji put izmedju dva korisnika" << endl;
        cout << "11) K-ti korisnik sa najvecim uticajem" << endl;
        cout << "12) Izadji iz menija" << endl;
        cout << "---------------------------------" << endl;
        cin >> izbor;

        switch (izbor) {
            case 1:
                cout << "Unesite ime fajla (bez txt): ";
                cin >> fajl;
                file.open(fajl + ".txt");

                if (!file.is_open()) {
                    cout << "Ne postoji fajl" << endl;
                } else {
                    file >> maxC >> maxG;
                    //cout << "maxC: " << maxC << ", maxG: " << maxG << endl;
                    g = new Graf(maxC, maxG);
                    grafInitialized = true;
                    for(int i=0; i<maxC;i++) {
                        file >> cvorovi;
                       // cout << cvorovi << endl;
                        g->addCvor(cvorovi);
                    }
                    for(int i=0; i<maxG; i++){
                        file >> grancica;
                        file >> cvorovi;
                        file >> w;
                        g->addGranu(grancica, cvorovi, w);
                    }
                    file.close();
                }
                break;

            case 2: {
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                string ime;
                cout << "Unesite ime cvora: ";
                cin >> ime;
                g->addCvor(ime);
                break;
            }
            case 3: {
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                string ime, dest;
                double w;
                cout << "Unesite ime cvora pocetka: ";
                cin >> ime;
                cout << "Unesite ime cvora kraja: ";
                cin >> dest;
                cout << "Unesite tezinu grane: ";
                cin >> w;
                g->addGranu(ime, dest, w);
                break;
            }
            case 4: {
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                string ime;
                cout << "Unesite ime cvora za uklanjanje: ";
                cin >> ime;
                g->uklanjanjeCvora(ime);
                break;
            }
            case 5: {
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                string ime, dest;
                cout << "Unesite ciju granu hocete da se ukloni: ";
                cin >> ime;
                cout << "Sa kime: ";
                cin >> dest;
                g->uklanjanjeGrane(ime, dest);
                break;
            }
            case 6: {
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                cout << *g;
                break;
            }
            case 7: {
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                delete(g);
                g= nullptr;
                grafInitialized = false;
                break;
            }
            case 8:
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                cout << "Unesite ime korisnika koji lajkuje: ";
                cin >> grancica;
                cout << "Unesite ime korisnika ciju objavu lajkuje: ";
                cin >> cvorovi;
                g->lajkuj(grancica, cvorovi);
                break;

            case 9:
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                g->najvecakomp();
                break;

            case 10:
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                cout << "Unesite ime pocetnog korisnika: ";
                cin >> grancica;
                cout << "Unesite ime krajnjeg korisnika: ";
                cin >> cvorovi;
                g->najverovatnijiPut(grancica, cvorovi);
                break;

            case 11:
                if (!grafInitialized) {
                    cout << "Graf nije ucitan" << endl;
                    break;
                }
                int k;
                cout << "Unesite k: ";
                cin >> k;
                g->najuticajnijiKorisnik(k);
                break;

            case 12:
                cout << "Izlaz iz programa." << endl;
                break;
            default:
                cout << "Nepoznata opcija, molimo pokusajte ponovo." << endl;
        }
    } while (izbor != 12);

    return 0;

}
