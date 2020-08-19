#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
struct Tido {
    int ora, perc, ido;
};
struct Tallomas {
    Tido ind, erk;
};
int main()
{
    // 1. feladat
    Tallomas sz[21][21];
    ifstream be("vonat.txt");
    int szerelveny, allomas, ora, perc;
    string muvelet;
    int i=0;
    while(be >> szerelveny >> allomas >> ora >> perc >> muvelet)
    {
        if(muvelet=="E")
        {
            sz[szerelveny][allomas].erk.ora=ora;
            sz[szerelveny][allomas].erk.perc=perc;
            sz[szerelveny][allomas].erk.ido=ora*60+perc;
        }
        else
        {
            sz[szerelveny][allomas].ind.ora=ora;
            sz[szerelveny][allomas].ind.perc=perc;
            sz[szerelveny][allomas].ind.ido=ora*60+perc;
        }
    }
    // 2. feladat
    cout << "2. feladat" << endl;
    cout << "Az allomasok szama: " << allomas+1 << endl;
    cout << "A vonatok szama: " << szerelveny << endl;

    // 3. feladat
    cout << "3. feladat" << endl;
    int maxvarakozas=-1;
    int maxszerelveny, maxallomas;
    for(int i=1; i<=szerelveny; i++)
    {
        for(int j=1; j<allomas; j++)
        {
            int varakozas=sz[i][j].ind.ido-sz[i][j].erk.ido;
            if(varakozas>maxvarakozas)
            {
                maxszerelveny=i;
                maxallomas=j;
                maxvarakozas=varakozas;
            }
        }
    }
    cout << "A(z) " << maxszerelveny << ". vonat a(z) " << maxallomas << ". allomason " << maxvarakozas << " percet allt." << endl;

    // 4. feladat
    cout << "4. feladat" << endl;
    int vsz, vora, vperc;
    cout << "Adja meg egy vonat azonositojat! ";
    cin >> vsz;
    cout << "Adjon meg egy idopontot (ora perc)! ";
    cin >> vora >> vperc;

    // 5. feladat
    cout << "5. feladat" << endl;
    int hossz=sz[vsz][allomas].erk.ido-sz[vsz][0].ind.ido;
    cout << "A(z) "<< vsz << ". vonat utja ";
    if(hossz>2*60+22) cout << hossz-(2*60+22) << " perccel hosszabb volt az eloirtnal.";
    if(hossz==2*60+22) cout << " pontosan az eloirt ideig tartott.";
    if(hossz<2*60+22) cout << (2*60+22)-hossz << " perccel rovidebb volt az eloirtnal.";
    cout << endl;

    // 6. feladat
    stringstream konvert;
    konvert << "halad" << vsz << ".txt";
    string fajlnev;
    konvert >> fajlnev;
    ofstream ki(fajlnev);
    for(int i=1; i<=allomas; i++)
    {
        ki << i << ". allomas: " << sz[vsz][i].erk.ora << ":" << sz[vsz][i].erk.perc << endl;
    }
    ki.close();

    // 7. feladat
    cout << "7. feladat" << endl;
    int idopont=vora*60+vperc;
    for(int i=1; i<=szerelveny; i++)
    {
        if(sz[i][0].ind.ido<=idopont and idopont<sz[i][1].erk.ido)
        {
            cout << "Az " << i << ". vonat a " << 1 << ". es a " << 2 << ". allomas kozott jart." << endl;
        }
        for(int j=1; j<allomas; j++)
        {
            if(sz[i][j].erk.ido<=idopont and idopont<sz[i][j].ind.ido)
            {
                cout << "Az " << i << ". vonat a " << j << ". allomason allt." << endl;
            }
            if(sz[i][j].ind.ido<=idopont and idopont<sz[i][j+1].erk.ido)
            {
                cout << "Az " << i << ". vonat a " << j << ". es a " << j+1 << ". allomas kozott jart." << endl;
            }
        }
    }
    return 0;
}
