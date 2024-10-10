#include <stdlib.h>
#include <stdio.h>
#include "functii.h"
#include <string.h>
#define MAXI 100

/*DIMA Oana-Mihaela - 311CB*/

TLista Initializare()
{
    TLista s;
    s  = (TLista)malloc(sizeof(TVag));
    if(!s) return NULL;
    s -> info = '0';
    s -> urm = s;
    s -> pre = s;
    return s;
}

void InserareVag1(char informatie, TTren *Trenulet)
{
    /*inserarea primului vagon din tren*/
    TLista aux = (TLista) malloc(sizeof(TVag));
    if (aux) {
        /*daca alocarea a avut loc cu succes*/
        aux -> info = informatie;
        aux -> urm = Trenulet -> s -> urm;
    	aux -> pre = Trenulet -> s;
        if (Trenulet -> s -> urm) Trenulet -> s -> urm -> pre = aux;
        Trenulet -> s -> urm = aux;
    }
}

void InserareVag_stanga(char informatie, TTren *Trenulet, FILE *fisier_iesire)
{
    /* mecanicul se afla pe prima pozitie */
    if (Trenulet -> m -> pre == Trenulet -> s) {
        fprintf(fisier_iesire, "ERROR\n");
        return;
    }
    else {
        /* alocare memorie pt. noul vagon*/
        TLista aux = (TLista) malloc(sizeof(TVag));

        aux -> info = informatie;
        /*realizarea legaturilor pt. noul vagon*/
        aux -> urm = Trenulet -> m;
        aux -> pre = Trenulet -> m -> pre;

        Trenulet -> m -> pre -> urm = aux;
        aux -> urm -> pre = aux;
        Trenulet -> m = Trenulet -> m -> pre;
    }
}

void InserareVag_dreapta(char informatie, TTren *Trenulet)
{
    /*inserarea unui vagon in dreapta mecanicului*/
    TLista aux = (TLista) malloc(sizeof(TVag));
    if (aux) {
        /*daca alocarea memoriei pt noul vagon a avut loc cu succes*/
        aux -> info = informatie;
        aux -> urm = Trenulet -> m -> urm;
    	aux -> pre = Trenulet -> m;
        if (Trenulet -> m -> urm) Trenulet -> m -> urm -> pre = aux;
        Trenulet -> m -> urm = aux;
        Trenulet -> m = Trenulet -> m -> urm;
    }
}

TTren *Initializare_tren()
{
    TTren *trenulet = (TTren*)malloc(sizeof(TTren));
    trenulet -> s = Initializare();
    /* adaugare vagon 1 */
    InserareVag1('#', trenulet);
    /* mecanicul se afla initial pozitionat in primul vagon*/
    trenulet -> m = trenulet -> s -> urm;
    return trenulet;
}

void Mutare_Stanga(TTren *Trenulet)
{
    if (Trenulet -> m != Trenulet -> s -> urm) {
        /* mecanicul nu se afla in primul vagon*/
        Trenulet -> m = Trenulet -> m -> pre;
    }
    else {
        /* mecanicul se afla in primul vagon*/
        Trenulet -> m = Trenulet -> s -> pre;
    }
}

void Mutare_Dreapta(TTren *Trenulet)
{
    if (Trenulet -> m -> urm != Trenulet -> s) {
        /* mecanicul nu se afla pe ultimul nod dinaintea santinelei */
        Trenulet -> m = Trenulet -> m -> urm;
    }
    else {
        InserareVag_dreapta('#', Trenulet);
    }
}

void Actualizare(TTren *Trenulet, char info_nou)
{
    /*adaug informatia noua in vagonul in care se afla mecanicul*/
    Trenulet -> m -> info = info_nou;
}

void Decuplare_Vagon(TTren *Trenulet)
{
    TLista p = Trenulet -> m;    
    p -> pre -> urm = p -> urm;
    p -> urm -> pre = p -> pre;
    /* cazul in care vagonul eliminat e primul */
    if (Trenulet -> m -> pre == Trenulet -> s) {
        Trenulet -> m = Trenulet -> s -> pre;
    }
    else {
        Trenulet -> m = Trenulet -> m -> pre;
    }
    free(p);
    /* daca vagonul eliminat a fost singurul, trenul revine in forma initiala */
    if (Trenulet -> s -> urm == Trenulet -> s){
        Trenulet = Initializare_tren();
    }
}

void Dezalocare_Tren(TTren **Trenulet)
{
    /*verifica daca trenul este NULL*/
    if ((*Trenulet) == NULL) {
        return;
    }
    TLista p = (*Trenulet) -> s -> urm;
    while (p != (*Trenulet) -> s) {
        TLista c = p;
        p = p -> urm;
        /*eliberez memoria pt fiecare vagon in parte*/
        free(c);
    }
    /*eliberez memoria pt locomotiva*/
    free((*Trenulet) -> s);
    free((*Trenulet));
}

TTren *Decuplare_Vagoane(TTren *Trenulet)
{
    Dezalocare_Tren(&Trenulet);
    /*trenul revine la forma initiala*/
    Trenulet = Initializare_tren();
    return Trenulet;
}

TTren *Cautare_pozitie(TTren *Trenulet, int nr_iteratii)
{
    while (nr_iteratii) {
        if (Trenulet -> m -> urm == Trenulet -> s) {
            Trenulet -> m = Trenulet -> s -> urm;
        }
        else {
            Trenulet -> m = Trenulet -> m -> urm;
        }
        nr_iteratii --;
    }
    return Trenulet;
}

TTren *Cautare_pozitie_stanga(TTren *Trenulet, int nr_iteratii)
{
    while (nr_iteratii) {
        Trenulet -> m = Trenulet -> m -> pre;
        nr_iteratii --;
    }
    return Trenulet;
}

TTren *Cautare_pozitie_dreapta(TTren *Trenulet, int nr_iteratii)
{
    while (nr_iteratii) {
        Trenulet -> m = Trenulet -> m -> urm;
        nr_iteratii --;
    }
    return Trenulet;
}

char *Construire_sir(TTren *Trenulet)
{
    int i = 0;
    /*salvarea pozitei initiale a mecanicului*/
    TLista pozitie_initiala = Trenulet -> m;
    /*alocare memorie pt sirul construit*/
    char *sir_construit = (char*)calloc(MAXI, sizeof(char));

    while (Trenulet -> m -> urm != pozitie_initiala) {
        if (Trenulet -> m != Trenulet -> s) {
            *(sir_construit + i) = Trenulet -> m -> info;
            i++;
        }
        Trenulet -> m = Trenulet -> m -> urm;
    }
    if(Trenulet -> m -> urm == pozitie_initiala) {
        *(sir_construit + i) = Trenulet -> m -> info;
        *(sir_construit + i + 1) = '\0';
    } else {
        *(sir_construit + i) = '\0';
    }
    Trenulet -> m = pozitie_initiala;
    return sir_construit;
}

char *Construire_sir_dreapta(TTren *Trenulet)
{
    int i = 0;
    /*salvarea pozitei initiale a mecanicului*/
    TLista pozitie_initiala = Trenulet -> m;
    /*alocare memorie pt sirul construit*/
    char *sir_construit = (char*)calloc(MAXI, sizeof(char));
    while (Trenulet -> m != Trenulet -> s) {
        *(sir_construit + i) = Trenulet -> m -> info;
        Trenulet -> m = Trenulet -> m -> urm;
        i++;
    }
    Trenulet -> m = pozitie_initiala;
    return sir_construit;
}

char *Construire_sir_stanga(TTren *Trenulet)
{
    int i = 0;
    /*salvarea pozitiei initiale a mecanicului*/
    TLista pozitie_initiala = Trenulet -> m;
    /*aloc memorie pt sirul construit*/
    char *sir_construit = (char*)calloc(MAXI, sizeof(char));
    while (Trenulet -> m != Trenulet -> s) {
        *(sir_construit + i) = Trenulet -> m -> info;
        Trenulet -> m = Trenulet -> m -> pre;
        i++;
    }
    Trenulet -> m = pozitie_initiala;
    return sir_construit;
}

void Cautare_Circulara(TTren *Trenulet, char *sir_cautat, FILE* fisier_iesire)
{  
    char *sir = Construire_sir(Trenulet);
    /*terminatorul de sir*/
    *(sir_cautat + strlen(sir_cautat) - 1) = '\0';
    int i = 0, gasit = 0;
    /*parcurgerea pentru a gasi sirul cautat*/
    while(*(sir + i)) {
        if(strstr(sir, sir_cautat) == (sir + i)) {
            gasit = 1;
            break;
        }
        i++;
    }
    free(sir);
    if (!gasit) {
        /*daca nu am gasit sirul cautat*/
        fprintf(fisier_iesire, "ERROR\n");
        return;
    }
    Trenulet = Cautare_pozitie(Trenulet, i);
}

void Cautare_Stanga(TTren *Trenulet, char *sir_cautat, FILE* fisier_iesire)
{
    char *sir = Construire_sir_stanga(Trenulet);
    /* adaugare terminator de sir */
    *(sir_cautat + strlen(sir_cautat) - 1) = '\0';
    int i = 0, gasit = 0;
    /*parcurgerea pentru a gasi sirul cautat*/
    while(*(sir + i)) {
        if (strstr(sir, sir_cautat) == (sir + i)) {
            gasit = 1;
            break;
        }
        i++;
    } 
    free(sir);
    if (!(gasit)) {
        /*daca nu am gasit sirul cautat*/
        fprintf(fisier_iesire, "ERROR\n");
        return;
    }
    Trenulet = Cautare_pozitie_stanga(Trenulet, i + strlen(sir_cautat) - 1);
}

void Cautare_Dreapta(TTren *Trenulet, char *sir_cautat, FILE* fisier_iesire)
{
    char *sir = Construire_sir_dreapta(Trenulet);
    /* adaugare terminator de sir */
    *(sir_cautat + strlen(sir_cautat) - 1) = '\0';
    int i = 0, gasit = 0;
    /*parcurgerea pentru a gasi sirul cautat*/
    while(*(sir + i)) {
        if (strstr(sir, sir_cautat) == (sir + i)) {
            gasit = 1;
            break;
        }
        i++;
    } 
    free(sir);
    if (!(gasit)) {
        /*daca nu am gasit sirul cautat*/
        fprintf(fisier_iesire, "ERROR\n");
        return;
    }
    Trenulet = Cautare_pozitie_dreapta(Trenulet, i + strlen(sir_cautat) - 1);
}

void Afisare_Curent(TTren *Trenulet, FILE *fisier_iesire)
{
    /* afiseaza carecterul inscriptionat pe vagonul curent*/
    /* corespunzator pozitiei curente a mecanicului*/

    fprintf(fisier_iesire, "%c\n", Trenulet -> m -> info);
}

void Afisare(TTren *Trenulet, FILE *fisier_iesire)
{
    TLista aux = Trenulet -> s -> urm;

    while (aux != Trenulet -> s) {
        if (aux == Trenulet -> m) {
            /*marcarea pozitieo mecanicului*/
            fprintf(fisier_iesire, "|%c|", aux -> info);
        }
        else {
            fprintf(fisier_iesire, "%c", aux -> info);
        }
        aux = aux -> urm;
    }
    fprintf(fisier_iesire, "\n");
}

TCoada *InitQ()
{
    TCoada *c = (TCoada*)malloc(sizeof(TCoada));
    if (!c) return NULL;
    c -> inc = NULL;
    c -> sf = NULL;
    return c;
}

void IntrQ(TCoada *c, char *comanda)
{
    /* adauga element la sfarsitul cozii */
    /*alocare memorie*/
    TLista2 new = (TLista2)malloc(sizeof(TComanda));
    if(!new) return;
    new -> urm = NULL;
    new -> pre = NULL;
    /*adaugare informatia*/
    new -> info = (char*)malloc(MAXI * sizeof(char));
    strcpy(new -> info, comanda);
    /*creare legaturi*/
    if (c -> sf == NULL) {
        c -> inc = new;
        c -> sf = new;
    }
    else {
        new -> pre = c -> sf;
        c -> sf -> urm = new;
        c -> sf = new;
    }
}

void ExtrQ(TCoada *c)
{  
    /* extrage element din coada si ii elibereaza memoria aferenta*/
    if (c->inc == NULL || c->sf == NULL) { 
        return;
    }
    
    TLista2 aux = c->inc;
    
    if (c->sf == c->inc) {
        c->inc = NULL;
        c->sf = NULL;
    } else { 
        c->inc = c->inc->urm; 
        c->inc->pre = NULL; 
    }
    
    free(aux->info);
    free(aux); 
}

void ResetQ(TCoada *c)
{
    /* distrugerea celulelor cozii*/
    if (c -> inc == NULL || c->sf == NULL) {
    return;
    }
    TLista2 aux;
    while (c -> inc != c -> sf) {         
        aux = c -> inc;
        c -> inc = c -> inc -> urm;   
        free(aux->info);
        free(aux);
    }
    free(c -> sf -> info);
    free(c -> sf);
    c -> sf = NULL;
}

void DistrQ(TCoada **c)
{ 
    /* distruge coada */
    ResetQ(*c);
    free(*c);
    *c = NULL;
}

TCoada *InversareQ(TCoada *c)
{
    /* inversare coada*/
    if (c -> inc == NULL || c -> sf == NULL) {
        return NULL;
    }
    TCoada *invers = InitQ();
    if(!invers) return 0;
    while(c -> sf != c -> inc) {
        IntrQ(invers, c -> sf -> info);
        free(c -> sf -> info);
        c -> sf = c -> sf -> pre;
        free(c -> sf -> urm);
    }
    if (c -> sf == c -> inc) {
        IntrQ(invers, c -> inc -> info);
        free(c -> sf -> info);
        free(c -> sf);
    }
    free(c);
    return invers;
}