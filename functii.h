#include <stdio.h>
#include <stdlib.h>

/*DIMA Oana-Mihaela - 311CB*/

typedef struct vagon{
    char info;
    struct vagon *pre, *urm;
}TVag, *TLista;

typedef struct trenulet{
    TLista m; /* pozitia mecanicului */
    TLista s; /* lista cu santinela(locomotiva) */
}TTren;

typedef struct comanda{
    char* info;
    struct comanda *pre, *urm;
}TComanda, *TLista2;

typedef struct coada{
    TLista2 inc; /* adresa primei celule din coada*/
    TLista2 sf; /* adresa ultimei celule din coada*/
}TCoada;

TLista Initializare(); /* initializare lista dublu inlantuita cu santinela */
TTren *Initializare_tren(); /* initializare tren */
void InserareVag1(char informatie, TTren *Trenulet); /* inserarea primului vagon */
void InserareVag_dreapta(char informatie, TTren *Trenulet); /* Inserare vagon dupa */
void InserareVag_stanga(char informatie, TTren *Trenule, FILE *fisier_iesire); /* Inserare vagon inainte */
void Actualizare(TTren *Trenulet, char info_nou);
void Mutare_Stanga(TTren *Trenulet);
void Mutare_Dreapta(TTren *Trenulet);
void Decuplare_Vagon(TTren *Trenulet);
void Dezalocare_Tren(TTren **Trenulet);
TTren *Decuplare_Vagoane(TTren *Trenulet);
TTren *Cautare_pozitie(TTren *Trenulet, int nr_iteratii);
char *Construire_sir(TTren *Trenulet);
char *Construire_sir_dreapta(TTren *Trenulet);
char *Construire_sir_stanga(TTren *Trenulet);
void Cautare_Circulara(TTren *Trenulet, char *sir_cautat, FILE *fisier_iesire);
void Cautare_Stanga(TTren *Trenulet, char *sir_cautat, FILE *fisier_iesire);
void Cautare_Dreapta(TTren *Trenulet, char *sir_cautat, FILE *fisier_iesire);
void Afisare_Curent(TTren *Trenulet, FILE *fisier_iesire);
void Afisare(TTren *Trenulet, FILE *fisier_iesire);
TCoada *InitQ();
void IntrQ(TCoada *c, char *comanda);
void ExtrQ(TCoada *c);
void ResetQ(TCoada *c);
void DistrQ(TCoada **c);
TCoada *InversareQ(TCoada *c);