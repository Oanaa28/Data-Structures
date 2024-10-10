# Tema_1 SDA
## Implementarea Temei
Tema contine:
- fisierul main.c
- fisierul functii.c
- fisierul functii.h
- README.md
- Makefile
## Fisierul functii.c
Am implementat trenul folosind o structura ce contine 2 campuri:
- o lista (in care sunt vagoanele si santinela)
- pozitia mecanicului.
Lista utilizata este de tip struct vagon si contine urmatoarele campuri:
- informatia de tip char
- doi pointeri catre vag. precedent, respectiv urmator

Pentru implementarea cozii am utilizat o structura ce contine doua campuri (ambele de tip TLista2):
- inc - adresa primei celule din coada
- sf - adresa ultimei celule din coada

Coada dublu inlantuita utilizeaza o lista de tip struct comanda care contine urmatoarele campuri:
- informatia de tip char*
- doi pointeri catre comanda precedenta, respectiv urmatoare

In acest fisier se afla de asemenea antetele tuturor functiilor ce sunt implementate in fisierul functii.c.

## FUNCTII (functii.c)

Acest fisier contine definiitile tuturor functiilor utilizate in aceasta tema.

 - ## Operatiile de tip UPDATE: 

### Move_Left
Pentru realizarea acestei operatii am implementat functia Mutare_Stanga. Functia primeste ca parametru un pointer la structura de tip TTren si are rolul de a muta pozitia mecanicului in vagonul anterior din tren.
(Trenulet -> m = Trenulet -> m -> pre)
Daca mecanicul nu se afla deja in primul vagon, atunci pozitia mecanicului este actualizata cu cea anterioara, altfel mecanicul ajunge pe ultima pozitie din tren.
```
Trenulet -> m = Trenulet -> s -> pre;
```

### Move_Right

Pentru realizarea acestei operatii am implementat functia Mutare_Dreapta. Functia primeste ca parametru un pointer la structura de tip TTren si are rolul de a muta pozitia mecanicului in vagonul urmator din tren.
Trenulet -> m = Trenulet -> m -> urm;
Daca mecanicul nu se afla pe ultimul nod dinaintea santinelei, acesta ajunge in vagonul urmator, altfel se insereaza un nou vagon, iar mecanicul se muta in vagonul nou inserat.
```
InserareVag_dreapta('#', Trenulet);
```
### Write
Pentru realizarea acestei operatii am implementat functia Actualizare.
Functia primeste ca parametri un pointer la structura de tip TTren si un element de tip char. Rolul acestei functii este de a actualiza informatia din vagonul in care se afla mecanicul. Astfel, functia acceseaza informatia actuala gasita la poztia mecanicului si o schimba, atribuindu-i noua informatie primita ca parametru. 
```
Trenulet -> m -> info = info_nou;
```
### Clear_Cell
Pentru realizarea acestei operatii am implementat functia Decuplare_Vagon, care primeste ca parametru un pointer la structura de tip TTren.
Rolul acestei functii este de a elimina vagonul in care se afla mecanicul.
Daca vagonul eliminat a fost singurul, trenul revine in forma initiala.
Realizez acest lucru prin apelul functiei Initializare_tren.

### Clear_All
Pentru realizarea acestei operatii am implementat functia Decuplare_Vagoane, care are drept scop stergerea vagoanelor si readucerea trenului in starea initiala.
Functia apeleaza Dezalocare_Tren care sterge fiecare vagon si elibereaza memoria utilizata de acestea. La final eliberez memoria pentru santinela si apoi pentru trenulet in sine.
Odata eliberat, trenul revine la forma initala si este returnat de catre functie.

### Insert_Left

Pentru realizarea acestei operatii am implementat functia InserareVag_stanga,
care are drept scop inserarea unui vagon in stanga vagonului in care se afla mecanicul in acel moment.
In cazul in care mecanicul se afla pe prima pozitie (in primul vagon dupa locomotiva), functia va afisa mesajul "ERROR".
Altfel, functia foloseste variabila aux(noul vagon), pentru care aloca memorie, ii adauga informatia primita ca parametru si actualizeaza legaturile necesare pt. adaugarea acestuia in trenulet.

### Insert_Right

Pentru realizarea acestei operatii am implementat functia InserareVag_dreapta,
care are drept scop inserarea unui vagon in dreapta vagonului in care se afla mecanicul in acel moment.
Functia aloca memoria necesara unui vagon in variabila aux, ii adauga informatia primita ca parametru si ii actualizeaza legaturile necesare pt. adaugarea acestuia in trenulet.

- ## Operatiile de tip SEARCH:

### Search

Pentru realizarea acestui task am utilizat functia Cautare_Circulara. Aceasta are scopul de a verifica daca exista o serie de vagoane vecine ale caror inscriptii formeaza un anumit sir.
Functia foloseste un pointer la char pentru a retine in acesta sirul format de vagoanele trenului prin parcurgerea circulara, lucru de care se ocupa functia Construire_sir :
```
    char *sir = Construire_sir(Trenulet);
```
In cadrul functiei Construire_sir se parcurge circular trenuletul(de la pozitia mecanicului la dreapta pana ajunge la ultimul vagon neparcurs dinaintea pozitiei mecanicului, salvata in variabila pozitie_initiala) :
```
while (Trenulet -> m -> urm != pozitie_initiala) {
        if (Trenulet -> m != Trenulet -> s) {
            *(sir_construit + i) = Trenulet -> m -> info;
            i++;
        }
        Trenulet -> m = Trenulet -> m -> urm;
    }
```
Dupa ce a fost construit sirul, ii este adaugqt terminatorul de sir si incepe cautarea prin sir.
- Cand sirul cautat transmis prin parametru a fost gasit (gasit == 1), se opreste cautarea si se elibereaza memoria sirului construit initial. 

- Daca sirul cautat nu a fost gasit (gasit == 0) se afiseaza in fisier mesajul "ERROR" si se iese din functie.

In cazul in care sirul cautat a fost gasit, mut mecanicul pe prima pozitie din sir, utilizand functia Cautare_pozitie :
```
Trenulet = Cautare_pozitie(Trenulet, i);
```
Functia Cautare_pozitie primeste 2 parametri:
- un pointer catre o structura de tip TTren
- o variabila de tip int ce retine cate mutari au fost realizate pentru a gasi sirul cautat

### Seach_Right

Functia utilizata pentru acest task este Cautare_Dreapta.
Aceasta apeleaaza functia Construire_sir_dreapta, functie ce construieste sirul aferent parcurgerii trenuletului din pozitia initiala a mecanicului pana la utimul vagon dinaintea locomotivei, inclusiv.
Odata construit, sirul primeste terminatorul de sir si este parcurs de functia Cautare_Dreapta, in vederea gasirii sirului cautat primit ca parametru.
- Cand sirul cautat a fost gasit (gasit == 1), se opreste cautarea si se elibereaza memoria sirului construit initial. 

- Daca sirul cautat nu a fost gasit (gasit == 0) se afiseaza in fisier mesajul "ERROR" si se iese din functie.

In cazul in care sirul cautat a fost gasit, mut mecanicul pe ultima pozitie din sir, utilizand functia Cautare_pozitie_dreapta:
```
Trenulet = Cautare_pozitie_dreapta(Trenulet, i + strlen(sir_cautat) - 1);
```
Functia Cautare_pozitie_dreapta primeste 2 parametri:
- un pointer catre o structura de tip TTren
- o variabila de tip int ce retine cate mutari au fost realizate pentru a gasi sirul cautat

### Search_Left

Analog, pentru aceasta functie am procedat similar cu operatia Search_Right.
Functia utilizata pentru acest task este Cautare_Stanga.
Aceasta apeleaaza functia Construire_sir_stanga, functie ce construieste sirul aferent parcurgerii trenuletului din pozitia initiala a mecanicului pana la primul vagon dupa locomotiva, inclusiv.
Odata construit, sirul primeste terminatorul de sir si este parcurs de functia Cautare_Stanga, in vederea gasirii sirului cautat primit ca parametru.
- Cand sirul cautat a fost gasit (gasit == 1), se opreste cautarea si se elibereaza memoria sirului construit initial. 
- Daca sirul cautat nu a fost gasit (gasit == 0) se afiseaza in fisier mesajul "ERROR" si se iese din functie.
In cazul in care sirul cautat a fost gasit, mut mecanicul pe ultima pozitie din sir, utilizand functia Cautare_pozitie_stanga:
```
Trenulet = Cautare_pozitie_stanga(Trenulet, i + strlen(sir_cautat) - 1);
```
Functia Cautare_pozitie_stanga primeste 2 parametri:
- un pointer catre o structura de tip TTren
- o variabila de tip int ce retine cate mutari au fost realizate pentru a gasi sirul cautat

- ## Operatiile de tip QUERY

### Show_Current

Pentru realizarea acestui task am utilizat functia Afisare_Curent care are drept scop afisarea inscriptiei vagonului in care se afla mecanicul. Functia afiseaza aceasta informatie in fisierul primit ca parametru. 
```
fprintf(fisier_iesire, "%c\n", Trenulet -> m -> info);
```

### Show

Pentru realizarea acestui task am utilizat functia Afisare care are drept scop afisarea trenuletului. Functia parcurge trenuletul si afiseaza  in fisierul tansmis ca parametru inscriptia de pe fiecare vagon, marcand pozitia mecanicului cu ('| |').

### Switch

Pentru realizarea acestei operatii am folosti functia InversareQ, functie ce are ca sccop inversarea cozii primite ca parametru. Functia creeaza o alta coada in care pune elementele cozii initiale in ordine inversa.
Functia elibereaza memoria utilizata de coada intiala si returneaza in final noua coada inversata.

### Execute 

Am realizat aceasta operaatie in fisierul main.c, odata cu parcurgerea operatiilor primite.

## Fisierul main.c

In main am declarat cele 2 fisiere: fisierul de intrare, respectiv cel de iesire, pe care apoi le-am deschis.
Am initalizat o variabila de tip TTren numita trenulet si o coada numita c.

Am salvat numarul comenzilor citite in variabila de tip sir de caractere numar_comenzi, variabila pe care am convertit-o intr-un numar de tip int: nr_comenzi, pentru utilizarea ulterioara.

Am salvat comenzile pe parcursul citirii in vectorul de string-uri comenzi.

Le-am parcurs si le-am adaugat in coada pe cele de tip UPDATE si SEARCH.

In cazul comenzilor de tip QUERY, am apelat direct functiile aferente. 

Odata ce am intalnit operatia EXECUTE, am verificat ce comanda se afla la inceputul cozii in acel moment si am apelat functia corespunzatoare numelui, apoi am scos comanda din coada.

In cazul operatiilor ce utilizeaza anumiti parametri/string-uri citite din fisier, le-am extras in variabile separate si am apelat functiile aferente utilizand aceste variabile.

In final, am eliberat memoria pentru:
- tren
- vectorul de comenzi
- coada
si am inchis fisierele.
