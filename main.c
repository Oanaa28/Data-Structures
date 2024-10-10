#include <string.h>
#include "functii.h"
#define MAXI 100

/*DIMA Oana-Mihaela - 311CB*/

int main(){
    char *fisier_intrare = "tema1.in", *fisier_iesire = "tema1.out";
    FILE *intrare = fopen(fisier_intrare, "r");
    FILE *iesire = fopen(fisier_iesire, "w");
    if (!intrare || !iesire)
        return 0;
    /*initalizare tren*/
    TTren *trenulet = Initializare_tren();
    if (!trenulet)
        return 0;
    /*initializare coada*/
    TCoada *c = InitQ();
    if(!c) return 0;
    
    char **comenzi;
    comenzi = (char**)malloc(MAXI*sizeof(char*));

    char *numar_comenzi = (char*)malloc(3*sizeof(char));
    
    fgets(numar_comenzi, 3, intrare); 
    int nr_comenzi = 0, p = 1, i;
    for ( i = strlen(numar_comenzi) - 1; i >= 0; i-- ){
        if(numar_comenzi[i] >= '0' && numar_comenzi[i] <= '9') {
            nr_comenzi += (numar_comenzi[i] - '0') * p;
            p = p * 10;
        }
    }
    for (i = 0; i <= nr_comenzi; i++) {
        comenzi[i] = (char*)calloc(MAXI, sizeof(char));
        fgets(comenzi[i], MAXI, intrare); 
        /* MAXI = numarul maxim de caractere citite in comenzi[i], inclsiv terminatorul*/
    }
    for (i = 0; i <= nr_comenzi; i++) {
        if(strstr(comenzi[i], "WRITE")) {
            IntrQ(c, comenzi[i]);
        } else {
            if(strstr(comenzi[i], "MOVE_LEFT") || strstr(comenzi[i], "MOVE_RIGHT")) {
                IntrQ(c, comenzi[i]);
            } else {
                if(strstr(comenzi[i], "CLEAR_CELL") || strstr(comenzi[i], "CLEAR_ALL")) {
                    IntrQ(c, comenzi[i]);
                } else {
                    if(strstr(comenzi[i], "INSERT_LEFT") || strstr(comenzi[i], "INSERT_RIGHT")) {
                        IntrQ(c, comenzi[i]);
                    } else {
                        if(strstr(comenzi[i], "SEARCH_LEFT") || strstr(comenzi[i], "SEARCH_RIGHT") || strstr(comenzi[i], "SEARCH")) {
                            IntrQ(c, comenzi[i]);
                        } else {
                            if (strstr(comenzi[i], "SHOW_CURRENT")) {
                                Afisare_Curent(trenulet, iesire);
                            } else { 
                                if (strstr(comenzi[i], "SHOW")) {
                                    Afisare(trenulet, iesire);
                                } else {
                                    if (strstr(comenzi[i], "SWITCH")) {
                                        c = InversareQ(c);
                                    } else {
                                        if(strstr(comenzi[i], "EXECUTE")) {
                                            if (strstr(c -> inc ->info, "SEARCH_LEFT")) {
                                                char *sir_cautat = (char*)malloc(10*sizeof(char));
                                                int lungime = strlen("SEARCH_LEFT"), j;
                                                for (j = 0; j < strlen(c -> inc -> info) - lungime ; j++)
                                                    sir_cautat[j] = c -> inc -> info[j + 1 + lungime];
                                                Cautare_Stanga(trenulet, sir_cautat, iesire);
                                                free(sir_cautat);
                                            } else {
                                                if (strstr(c -> inc ->info, "SEARCH_RIGHT")) {
                                                    char *sir_cautat = (char*)malloc(10*sizeof(char));
                                                    int lungime = strlen("SEARCH_RIGHT"), j;
                                                    for (j = 0; j < strlen(c -> inc -> info) - lungime; j++)
                                                        *(sir_cautat + j) = c -> inc -> info[j + 1 + lungime];
                                                    Cautare_Dreapta(trenulet, sir_cautat, iesire);
                                                    free(sir_cautat);
                                                } else {
                                                    if(strstr(c -> inc -> info, "SEARCH")) {
                                                        char *sir_cautat = (char*)malloc(10*sizeof(char));
                                                        int lungime = strlen("SEARCH"), j;
                                                        for (j = 0; j < strlen(c -> inc -> info) - lungime; j++)
                                                            sir_cautat[j] = c -> inc -> info[j + 1 + lungime];
                                                        Cautare_Circulara(trenulet, sir_cautat, iesire);
                                                        free(sir_cautat);
                                                    } else {
                                                        if(strstr(c -> inc -> info, "MOVE_RIGHT")) {
                                                            Mutare_Dreapta(trenulet);
                                                        } else {
                                                            if(strstr(c -> inc -> info, "MOVE_LEFT")) {
                                                                Mutare_Stanga(trenulet);
                                                            } else {
                                                                if(strstr(c -> inc -> info, "WRITE")) {
                                                                    char informatie;
                                                                    int lungime = strlen("WRITE");
                                                                    informatie = c -> inc -> info[1 + lungime];
                                                                    Actualizare(trenulet, informatie);
                                                                } else {
                                                                    if(strstr(c -> inc -> info, "INSERT_LEFT")) {
                                                                    char informatie;
                                                                    int lungime = strlen("INSERT_LEFT");
                                                                    informatie = c -> inc -> info[1 + lungime];
                                                                    InserareVag_stanga(informatie, trenulet, iesire);   
                                                                    } else {
                                                                        if(strstr(c -> inc -> info, "INSERT_RIGHT")) {
                                                                            char informatie;
                                                                            int lungime = strlen("INSERT_RIGHT");
                                                                            informatie = c -> inc -> info[1 + lungime];
                                                                            InserareVag_dreapta(informatie, trenulet);   
                                                                        } else {
                                                                            if(strstr(c -> inc -> info, "CLEAR_CELL")) {
                                                                                Decuplare_Vagon(trenulet);
                                                                            } else {
                                                                                if(strstr(c -> inc -> info, "CLEAR_ALL")) {
                                                                                    trenulet = Decuplare_Vagoane(trenulet);
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        ExtrQ(c);
                                    }
                                }
                            }
                        }
                    }
                }
            }  
    }
}
    Dezalocare_Tren(&trenulet);
    free(numar_comenzi);
    for(i = 0; i <= nr_comenzi; i++) {
        free(comenzi[i]);
    }
    free(comenzi);
    DistrQ(&c);
    fclose(intrare);
    fclose(iesire);
    return 0;

}