#include <cmath>
#include <math.h>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
#define M_PI 3.14159265
#define M 17 ///ILOSC MIEJSCOWOSCI W PLIKU TEKSTOWYM

class Data ///PRZETRZYMYWANIE MIASTA I JEGO WSPOLRZEDNYCH
{
public:
    string miasto;
    double x;
    double y;
    Data(string miasto="", double x=0, double y=0)
    {
        this->miasto=miasto;
        this->x=x;
        this->y=y;
    }
    double get(){return x;}
    ~Data(){}
};

class Data_Connect ///PRZETRZYMYWANIE 2 MIEJSCOWOSCI I ODLEGLOSCI MIEDZY NIMI
{
public:
    string miasto1;
    string miasto2;
    double dlugosc;
    Data_Connect(string miasto1="", string miasto2="", double dlugosc=0)
    {
        this->miasto1 = miasto1;
        this->miasto2 = miasto2;
        this->dlugosc = dlugosc;
    }
    ~Data_Connect() {}
};
void AddData(fstream &plik, Data *X, fstream &plik2) ///POBIERANIE DANYCH Z PLIKU
{
    string tekst;
    int rz=0;
    while (!plik.eof())
    {
        string stopnieX="";
        string minutyX="";
        string stopnieY="";
        string minutyY="";
        string nazwa ="";
        getline(plik,tekst);
        int i=0;
        stopnieX = stopnieX + tekst[i] + tekst[i+1];
        i+=2;
        while (tekst[i]<'0' || tekst[i]>'9'){i++;}
        if(tekst[i] != '0')
        {
            minutyX=minutyX+tekst[i]+tekst[i+1];
        }
        else
        {
            minutyX=minutyX+tekst[i+1];
        }
        i+=2;
        while (tekst[i]< '0' || tekst[i]>'9'){i++;}
        stopnieY = stopnieY + tekst[i]+tekst[i+1];
        i+=2;
        while (tekst[i]<'0' || tekst[i]>'9'){i++;}
        if (tekst[i] != '0')
        {
            minutyY = minutyY + tekst[i]+ tekst[i+1];
        }
        else
        {
            minutyY = minutyY + tekst[i+1];
        }
        i+=2;
        for(i; i<tekst.length();i++){nazwa = nazwa + tekst[i];}

        double Xx = stof(stopnieX) + ((stof(minutyX))/60);
        double Yy = stof(stopnieY) + ((stof(minutyY))/60);
        cout << nazwa << "\t" << Xx << "\t" << Yy << endl;
        Data d(nazwa, Xx, Yy);
        X[rz]=d;
        rz++;
    }
}

void Graph(double **graph, Data*X)///FUNKCJA WSPOMAGAJACA DO TWORZENIA PLIKU WYJSCIOWEGO
{
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(j==i)
            {
                graph[i][j]=0;
            }
            else///ZASTOSOWANIE WZORU NA ODLEGLOSC W LINI PROSTEJ(WIKIPEDIA)
            {
                double tmp1 = X[j].x - X[i].x; //x2-x1
                double tmp2 = X[j].y - X[i].y; //y2-y1
                double tmp3 = cos(X[i].x * M_PI / 180); //cos(x1*pi/180)
                graph[i][j] = sqrt(pow(tmp1, 2) + pow(tmp3*tmp2, 2))*(40075.704 / 360);
            }
        }
    }
}

double MinKey(double *key, bool *mstSet)///FUNKCJA DO ZNALEZIENIA WIERZCHOLKA,MINIMALNA WARTOSC KLUCZA Z ZESTAWU WIERZCHOLKOW
{
    double min = INT_MAX, min_index;
    for(int a=0; a<M; a++)
    {
        if(mstSet[a] == false && key[a] < min)
        {
            min=key[a], min_index=a;
        }
    }
    return min_index;
}

void print(int *parent, double **graph, Data *X, fstream &plik, Data_Connect **d)///DRUKOWANIE POLACZONYCH MIAST Z ODLEGLOSCIAMI (KONSOLA CMD)
{
    double sum=0;
    for(int i=1; i<M; i++)
    {
        for(int m=0; m<M; m++)
        {
            for(int k=0; k<M; k++)
            {
                if((X[parent[i]].miasto == d[m][k].miasto1 && X[i].miasto == d[m][k].miasto2)||
                   (X[parent[i]].miasto == d[m][k].miasto2 && X[i].miasto == d[m][k].miasto1))
                {
                    d[m][k].dlugosc=graph[i][parent[i]];
                }
            }
        }
        cout<<X[parent[i]].miasto <<" - "<<X[i].miasto<<" \t"<<graph[i][parent[i]]<<" \n";
        sum=sum+graph[i][parent[i]];
    }
    cout<<endl<<sum;
}

void primMST(double **graph, Data *X, fstream &plik, Data_Connect **data)///AGLORYTM PRIMA
{
    ///TABLICA DO PRZECHOWYWANIA MST
    int parent[M];
    double *key = new double[M];
    ///REPREZENTOWANIE ZESTAWU WIERZCHOLKOW W MST
    bool *mstSet=new bool[M];
    ///OZNACZAMY WSZYSTKIE KEY JAKO NIESKONCZONE
    for(int i=0; i<M; i++){key[i]=INT_MAX, mstSet[i] = false;}
    ///TWORZYMY KLUCZ ZERO ABY ZOSTAL ON WYBRANY JAKO PEIRWSZY WIERZCHOLEK
    key[0]=0;
    parent[0]=-1;
    ///MST Z M WIERZCHOLKAMI
    for(int count =0; count < M -1; count++)
    {
        ///MINIMALNY WIERZCHOLEK
        int u=MinKey(key,mstSet);
        ///DODAJEMY WYBRANY WIERZCHOLEK DO ZESTAWU MST
        mstSet[u]=true;
        ///AKTUALIZUJEMY WARTOSCI KLUCZA I INDEKSU W SASIEDNICH WIERZCHOLKACH
        ///POD UWAGE BIERZEMY TYLKO TE KTORE NIE SA JESZCZE W ZESTAWIE MST
        for(int a=0; a<M; a++)
        {
            if(graph[u][a]&&mstSet[a]==false && graph[u][a] < key[a])
            {
                parent[a]=u, key[a]=graph[u][a];
            }
        }
    }
    print(parent,graph,X,plik,data);
}

int main()
{
    fstream plik;
    plik.open("miasta.txt", fstream::in);
    fstream plik2;
    plik2.open("wynik.txt", fstream::out);
    Data X[M];
    AddData(plik, X, plik2);
    double **graph = new double*[M];
    for (int i = 0; i < M; i++){graph[i] = new double[M];}
    Data_Connect **dataC = new Data_Connect*[M];
    for (int i = 0; i < M; i++){dataC[i] = new Data_Connect[M];}
    Graph(graph, X);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0 ; j < M; j++)
        {
            dataC[i][j].miasto1 = X[i].miasto;
            dataC[i][j].miasto2 = X[j].miasto;
        }
    }
    primMST(graph, X, plik2, dataC);

    for (int i = 0; i < M; i++)
    {
        plik2<<"\t" << X[i].miasto;
    }
    plik2 << endl;
    for (int i = 0; i < M; i++)
    {
        plik2 << X[i].miasto;
        for (int j = 0 ; j < M; j++)
        {
            plik2 << "\t" << graph[i][j];
        }
        plik2 << endl;
    }
    plik2.close();
    plik.close();
    return 0;
}
