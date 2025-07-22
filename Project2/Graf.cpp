#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include "Graf.h"

Graf::Graf(int n, int e) :n(n), e(e)
{
	cntCvorova = 0;
	cntGrana = 0;
    //inicijalizuje se niz duzine cvorova i grana
	cvorovi = new Korisnik[n]; 
	odnosi = new Grana[e];
	//memset(cvorovi[i]->optr, 0, n * sizeof(int));
	for (int i = 0; i < n; i++) {
		cvorovi[i].optr = 0;
	}
    for (int i=0; i<e;i++) {
        odnosi[i].dest = -1;
        odnosi[i].w = -1;
    }
}
//destruktor
Graf::~Graf()
{
	delete[] cvorovi;
	delete[] odnosi;
}

void Graf::povecaj_cvorovi(int novon)
{
	if (novon >= n) {
		Korisnik* temp = new Korisnik[novon];
		//memcpy(temp, cvorovi, n * sizeof(Korisnik));
        for (int i = 0; i < n; i++) {
            temp[i].ime = cvorovi[i].ime;
            temp[i].optr = cvorovi[i].optr;
        }
		//memset(temp + n, cvorovi[n-1].optr, (novon - n) * sizeof(Korisnik));
        for (int i = n; i < novon; i++) {
            temp[i].optr = cntGrana; //jer zadnji cvorovi u nizu nemaju grane
        }
		delete[] cvorovi;
		cvorovi = temp;
		n = novon;
	}
	else {
		cout << "Greska pri menjanju velicine niza" << endl;
	}
}


void Graf::povecaj_grane(int novoe)
{
	if (novoe >= e) {
		Grana* temp = new Grana[novoe];
		//memcpy(temp, odnosi, cntGrana * sizeof(Grana));
        for (int i = 0; i < e; i++) {
            temp[i].dest = odnosi[i].dest;
            temp[i].w = odnosi[i].w;
        }
        for(int i=e; i<novoe; i++) {
            temp[i].dest = -1;
            temp[i].w = -1;

        }
		delete[] odnosi;
		odnosi = temp;
		e = novoe;
	}
	else {
		cout << "Greska pri menjanju velicine niza " << endl;
	}
}

void Graf::addCvor(string& ime){

	if (cntCvorova >= n) {
		povecaj_cvorovi(cntCvorova+1);
	}
	cvorovi[cntCvorova].ime = ime;
    cvorovi[cntCvorova].optr = cntGrana;
	cntCvorova++;
}

void Graf::addGranu(string& ime, string& dest, double w)
{
    if (w<0 || w>1) {
        cout << "Greska nije validna tezina grane (tezina moze biti izmedju 0 i 1)" << endl;
        return;
    }
    if (cntGrana >= e) {
        povecaj_grane(cntGrana+1);
    }
    int id = -1;
    int iddest = -1;
    for (int i = 0; i < cntCvorova; i++) {
        if (cvorovi[i].ime == ime) {
            id = i;
        }
        else if(cvorovi[i].ime == dest) {
            iddest = i;
        }
    }
    if (id == -1) {
        cout << "Greska nije nadjeno ime korisnika od koga krece grana" << endl;
        return;
    }
    else if (iddest == -1) {
        cout << "Greska nije nadjeno ime korisnika do koga ide grana" << endl;
        return;
    }
    //povecavaju se odnos pointeri svih cvorova posle cvora kom sam dodao granu
    for (int i = id+1; i < cntCvorova; i++) { 
        cvorovi[i].optr++;
    }
    if(id+1 == cntCvorova) {
        odnosi[cntGrana].dest = iddest;
        odnosi[cntGrana].w = w;
    }
    else{
        shiftr(odnosi, cntGrana, cvorovi[id+1].optr-1); //pomeram niz odnosi u desno da napravim mesto za novu granu
        odnosi[cvorovi[id+1].optr-1].dest = iddest;
        odnosi[cvorovi[id+1].optr-1].w = w;
    }
    cntGrana++;
}




void Graf::shiftr(Grana* arr, int size, int n) {
    if (size <= 1 || n >= size) return;

    for (int i = size; i > n; --i) {
        arr[i] = arr[i - 1];
    }
}


void Graf::uklanjanjeGrane(string& ime, string& dest)
{
	int id = -1;
	int iddest = -1;
	for (int i = 0; i < n; i++) {
		if (cvorovi[i].ime == ime) {
			id = i;
		}
		else if (cvorovi[i].ime == dest) {
			iddest = i;
		}
	}
	if (id == -1) {
		cout << "Greska nije nadjeno ime korisnika od koga krece grana" << endl;
		return;
	}
	else if (iddest == -1) {
		cout << "Greska nije nadjeno ime korisnika do koga ide grana" << endl;
		return;
	}
	
	int start = cvorovi[id].optr;
    int end = 0;
    if(id+1 == cntCvorova) {
        end = cntGrana;
    }
    else
    {
        end = cvorovi[id+1].optr;
    }
    if ((end - start) == 0) {
        cout << "Nema nijednu granu pa ne moze nista da se ukloni" << endl;
        return;
    }
    //nadjem granu za otklanjanje i siftujem levo da je izbrisem
    for (int i = start; i < end; i++) {
        if (odnosi[i].dest == iddest) {
            shiftl(odnosi, cntGrana, i);
            odnosi[cntGrana-1].dest = -1;//zadnji element ide na -1 tj pocetno stanje
            odnosi[cntGrana-1].w = -1;
            for (int j = id+1; j < n; j++) {
                cvorovi[j].optr--;
            }
            cntGrana--;
            return;
        }

    }
    cout << "Greska nije nadjeno ime korisnika do koga ide grana" << endl;
}


void Graf::uklanjanjeCvora(string& ime) 
{
	int id = 0;
	for (int i = 0; i < n; i++) {
		if (cvorovi[i].ime == ime) {
			id = i;
		}
	}
	if (id == -1) {
		cout << "Greska nije nadjeno ime korisnika" << endl;
		return;
	}
    int end;
    int start = cvorovi[id].optr;
    if(id+1 == cntCvorova) {
        end = cntGrana;
    } else end = cvorovi[id+1].optr;
    for(int i = 0; i<(end-start); i++) {
        uklanjanjeGrane(cvorovi[id].ime, cvorovi[odnosi[cvorovi[id].optr].dest].ime);
    }
    int cnt = 0;
    while(cnt<cntGrana){
        int j = 0;
        if(odnosi[cnt].dest == id) {
            for(j = 0; j < cntCvorova; j++){
                if(cvorovi[j].optr > cnt) {
                    break;
                }
            }
            j--;
            uklanjanjeGrane(cvorovi[j].ime, ime);
            continue;
        }
        else if(odnosi[cnt].dest > id) {
            odnosi[cnt].dest--;
            cnt++;
        }
        else cnt++;
    }
    if (cntCvorova <= 1 || id >= cntCvorova) return;

    for (int i = id; i < cntCvorova-1; i++) {
        cvorovi[i] = cvorovi[i + 1];
    }
    cvorovi[cntCvorova-1].optr = -1;
    cvorovi[cntCvorova-1].ime = "";
    cntCvorova--;


}



void Graf::shiftl(Grana* arr, int size, int dest) {
	if (size <= 1 || dest >= size - 1) return;

	for (int i = dest; i < size-1; i++) {
		arr[i] = arr[i + 1];
	}
}

ostream &operator<<(ostream &stream, Graf &graf) {
    int start;
    int end;
    for(int i=0;i<graf.cntCvorova;i++) {
        stream << graf.cvorovi[i].ime + " -> ";
        start = graf.cvorovi[i].optr;
        if(i+1 == graf.cntCvorova) {
            end = graf.cntGrana;
        } else end = graf.cvorovi[i+1].optr;
        if(end - start) {
            for(int i=start;i<end;i++) {
                stream << graf.cvorovi[graf.odnosi[i].dest].ime + "(" << graf.odnosi[i].w << ")";
                if(i == end-1) {
                    stream << endl;
                }else{
                    stream << ", ";
                }
            }
        }else {
            stream << "Nema prijatelja" << endl;
        }
    }
    return stream;
}

void Graf::lajkuj(string &k1, string &k2) {
    int id1 = -1;
    int id2 = -1;

    for (int i = 0; i < cntCvorova; i++) {
        if (cvorovi[i].ime == k1) {
            id1 = i;
        }
        else if (cvorovi[i].ime == k2) {
            id2 = i;
        }
    }

    if (id1 == -1 || id2 == -1) {
        cout << "Greska: Jedan od korisnika ne postoji." << endl;
        return;
    }
    int end;
    int start = cvorovi[id1].optr;
    if(id1+1 == cntCvorova) {
        end = cntGrana;
    } else end = cvorovi[id1+1].optr;
    for(int i=start; i<end; i++) {
        if(odnosi[i].dest == id2) {
            odnosi[i].w += 0.1;
            if(odnosi[i].w > 1.0) {
                odnosi[i].w = 1.0;
            }
            cout << k1 << " je lajkovao objavu korisnika " << k2 << endl;
            return;
        }
    }
    addGranu(k1, k2, 0.1);
    cout << k1 << " je lajkovao objavu korisnika " << k2 << endl;
}

void Graf::dfs(int start, bool *visited, int* stek, int& sp, int* komp, int& kompsize) {
    stek[++sp] = start;
    visited[start] = true;

    while(sp >= 0) {
        int v = stek[sp--];
        komp[kompsize++] = v;
        if (kompsize >= cntCvorova) return;
        int end;
        int st = cvorovi[v].optr;
        if(v+1 == cntCvorova) {
            end = cntGrana;
        } else end = cvorovi[v+1].optr;
        for(int i=st; i < end; i++) {
            if(!visited[odnosi[i].dest]) {
                visited[odnosi[i].dest] = true;
                stek[++sp] = odnosi[i].dest;
            }

        }

    }
}

void Graf::najvecakomp() {
    bool* visited = new bool[cntCvorova];
    int* stek = new int[cntCvorova];
    int* komp = new int[cntCvorova];
    int sp = -1;
    int kompsize;
    int maxkompsize = 0;
    int* najvecakomp = new int[cntCvorova];
    //int largestkompsize = 0; //?

    for(int i=0;i<cntCvorova;i++) {
        visited[i] = false;
    }
    for(int i=0; i<cntCvorova; i++) {
        if(!visited[i]) {
            kompsize = 0;
            dfs(i, visited, stek, sp, komp, kompsize);
            if(kompsize > maxkompsize) {
                maxkompsize = kompsize;
                if (kompsize > cntCvorova) kompsize = cntCvorova;
                //largestkompsize = kompsize; //?
                for(int j=0; j< kompsize; j++) {
                    najvecakomp[j] = komp[j];
                }
            }
        }
    }

    cout << "Najveca komponenta (velicina: " << maxkompsize << "): ";
    for (int i = 0; i < maxkompsize; i++) {
        if (najvecakomp[i] >= 0 && najvecakomp[i] < cntCvorova) {
            cout << cvorovi[najvecakomp[i]].ime << " ";
        }
        else {
            cout << "Greska index van opsega";
        }
        
    }
    cout << endl;

    delete[] visited;
    delete[] stek;
    delete[] komp;
    delete[] najvecakomp;



}

void Graf::najverovatnijiPut(string& startIme, string& ciljIme) {

    int id = -1;
    int iddest = -1; //id je pocetni cvor od koga trazim
    int curr = -1;

    for (int i = 0; i < cntCvorova; i++) {
        if (cvorovi[i].ime == startIme) id = i;
        if (cvorovi[i].ime == ciljIme) iddest = i;
    }

    if (id == -1 || iddest == -1) {
        cout << "Korisnici nisu pronadjeni" << endl;
        return;
    }


    double* D = new double[cntCvorova]; //ovde upisujem trenutno max rastojanje od cvora
    int* S = new int[cntCvorova]; //putanja valjda tako sto cuva cvor koji je bio pre toga
    bool* visited = new bool[cntCvorova]; //poseceni cvorovi
    int* stek = new int[cntCvorova];
    int sp = -1;


    for(int i=0; i<cntCvorova ; i++) {
        D[i] = -1; //svi su na pocetku -1
        S[i] = -1;
        visited[i] = false;
    }
    S[id] = id;
    D[id] = 0;


    int start = 0; //pocetak i kraj onog za kojeg trazim u odnosi listi
    int end = 0;
    start = cvorovi[id].optr;
    if(id+1 == cntCvorova) {
        end = cntGrana;
    }
    else
    {
        end = cvorovi[id+1].optr;
    }
    if((end-start) == 0) {cout << "Nema suseda uopste" << endl; return;}

    for(int j=start; j<end; j++) {
        D[odnosi[j].dest] = odnosi[j].w;
        S[odnosi[j].dest] = id;
    }
    visited[id] = true;
    double maxVal = D[0];
    for (int i = 1; i < cntCvorova; i++) {
        if (D[i] > maxVal) {
            maxVal = D[i];
            curr = i;
        }
    }

    for(int i=0; i<cntCvorova-1; i++) {
        start = cvorovi[curr].optr;
        if(curr+1 == cntCvorova) {
            end = cntGrana;
        }
        else
        {
            end = cvorovi[curr+1].optr;
        }
        for(int j=start; j<end; j++) {
            if(maxVal * odnosi[j].w > D[odnosi[j].dest]) {
                D[odnosi[j].dest] = maxVal * odnosi[j].w;
                S[odnosi[j].dest] = curr;
            }
        }
        visited[curr] = true;
        maxVal = D[0];
        for (int p = 1; p < cntCvorova; p++) {
            if (D[p] > maxVal) {
                if(!visited[p]) {
                    maxVal = D[p];
                    curr = p;
                }
            }
        }
        if(maxVal == -1) break;
    }

    /*for(int i = 0; i < cntCvorova; i++) {
        cout << D[i] <<", ";
    }
    cout << endl;
    for(int i = 0; i < cntCvorova; i++) {
        cout << S[i] <<", ";
    }
    cout << endl;*/

    int u = iddest;
    if(S[u] == -1) { cout<< "Nema puta do korisnika" << endl;return; };
    
    while (u != id) {
        stek[++sp] = u;
        u = S[u];
    }
    stek[++sp] = id;
    for(;sp>=0;sp--) {
        if(sp - 1 >= 0) cout<<cvorovi[stek[sp]].ime << " ("<<D[stek[sp-1]] <<") -> ";
        else cout<<cvorovi[stek[sp]].ime;

    }
    cout<<endl;

    delete []D;
    delete []S;
    delete []visited;
    delete []stek;
}

double** Graf::napraviMatricu() {
    double** mat = new double*[cntCvorova];
    for (int i = 0; i < cntCvorova; i++) {
        mat[i] = new double[cntCvorova];
    }


    for(int i=0; i < cntCvorova; i++) {
        for(int j=0; j<cntCvorova; j++) {
            mat[i][j] = 0;
            if(i==j)mat[i][j] = 0;
        }
    }
    for(int i=0; i< cntCvorova;i++) {
        int end = 0;
        int start = cvorovi[i].optr;
        if(i+1 == cntCvorova) {
            end = cntGrana;
        }
        else
        {
            end = cvorovi[i+1].optr;
        }
        for(int j = start; j< end; j++) {
            mat[i][odnosi[j].dest] = odnosi[j].w;
        }
    }
    return mat;

    /*for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout << mat[i][j] << " ";

        cout << endl;
    }*/
}


void Graf::najuticajnijiKorisnik(int uticajni) {
    if (uticajni < 1 || uticajni > cntCvorova) return;

    double** mat = napraviMatricu();

    double* uticaj = new double[cntCvorova];
    double* noviUticaj = new double[cntCvorova];
    double* sortiraniUticaji = new double[cntCvorova];

    char** korisnici = new char* [cntCvorova];
    for (int i = 0; i < cntCvorova; i++) {
        korisnici[i] = new char[30];
        uticaj[i] = 1.0 / cntCvorova;
    }


    for (int k = 0; k < cntCvorova; k++) {
        for (int i = 0; i < cntCvorova; i++) {
            noviUticaj[i] = (1.0 - 0.85) / cntCvorova;
            for (int j = 0; j < cntCvorova; j++) {
                if (mat[j][i] > 0) {
                    noviUticaj[i] += 0.85 * mat[j][i] * uticaj[j];
                }
            }
        }
        for (int i = 0; i < cntCvorova; i++) {
            uticaj[i] = noviUticaj[i];
        }
    }

    for (int i = 0; i < cntCvorova; i++) {
        const char* ime = cvorovi[i].ime.c_str();
        strncpy(korisnici[i], ime, 29);
        korisnici[i][29] = '\0';
        sortiraniUticaji[i] = uticaj[i];
    }

    for (int i = 0; i < cntCvorova - 1; i++) {
        for (int j = 0; j < cntCvorova - i - 1; j++) {
            if (sortiraniUticaji[j] < sortiraniUticaji[j + 1]) {
                double tempUticaj = sortiraniUticaji[j];
                sortiraniUticaji[j] = sortiraniUticaji[j + 1];
                sortiraniUticaji[j + 1] = tempUticaj;

                char tempIme[30];
                strcpy(tempIme, korisnici[j]);
                strcpy(korisnici[j], korisnici[j + 1]);
                strcpy(korisnici[j + 1], tempIme);
            }
        }
    }

    cout << "k-ti najuticajniji korisnik (uticaj): " << korisnici[uticajni - 1] << " ("
        << sortiraniUticaji[uticajni - 1] << ")" << endl;

    delete[] uticaj;
    delete[] noviUticaj;
    delete[] sortiraniUticaji;

    for (int i = 0; i < cntCvorova; ++i) {
        delete[] korisnici[i];
    }
    delete[] korisnici;

    for (int i = 0; i < cntCvorova; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}
