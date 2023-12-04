#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool cautaNumar(const int* sir2, const int contor2, const int x){
    for(int i = 0; i < contor2; i++){
        if(sir2[i] == x){
            return true;
        }
    }
    return false;
}

void afisareSir(const int sir[], const int size){
    for(int i = 0; i < size; i++){
        printf("%d ", sir[i]);
    }
}

int prelucrareLinie(char* line){
    int scorCurent = 0;
    int *sir1 = NULL, *sir2 = NULL;
    int contor1 = 0, contor2 = 0;
    int careSir = 0;

    char* line2 = malloc(500 * sizeof(char));
    if(!line2){
        fprintf(stderr, "Eroare la alocare line2!\n");
        exit(-1);
    }

    char* l1 = line, *l2 = NULL; //Aici pastrez referintele la care tai;

    char *p = strtok_r(line, ":", &l1);
    char* p2 = NULL;

    p = strtok_r(NULL, "|", &l1);
    while(p){ //Acum ca am obtinut numerele din stanga, le copiez in alta linie pentru a putea taia iar cu alt pointer;
        strncpy(line2, p, 500);
        l2 = line2;
        careSir++;

        if(careSir == 1){ //Tai si adaug in primul sir;
            p2 = strtok_r(line2, " ", &l2);
            while(p2){
                sir1 = realloc(sir1, (contor1 + 1) * sizeof(int));
                if(!sir1){
                    fprintf(stderr, "Eroare la alocarea memoriei pentru primul sir de numere!\n");
                    exit(-1);
                }

                sir1[contor1++] = atoi(p2);
                p2 = strtok_r(NULL, " ", &l2);
            }
        }
        else{
            p2 = strtok_r(NULL, " ", &l2);
            while(p2){
                sir2 = realloc(sir2, (contor2 + 1) * sizeof(int));
                if(!sir2){
                    fprintf(stderr, "Eroare la alocarea memoriei pentru al doilea sir de numere!\n");
                    exit(-1);
                }

                sir2[contor2++] = atoi(p2);
                p2 = strtok_r(NULL, " ", &l2);
            }
        }
        p = strtok_r(NULL, "|", &l1);
    }

    //printf("Sirul 1 este -> "); afisareSir(sir1, contor1); printf("\n");
    //printf("Sirul 2 este -> "); afisareSir(sir2, contor2); printf("\n");

    scorCurent = 0;
    for(int i = 0; i < contor1; i++){
        if(cautaNumar(sir2, contor2, sir1[i])){
            if(scorCurent == 0){
                scorCurent = 1;
            }
            else
            {
                scorCurent *= 2;
            }
        }
    }


    free(line2);
    free(sir1);
    free(sir2);
    return scorCurent;
}

void citireDate(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului sursa!\n");
        exit(-1);
    }

    int sumaPuncte = 0;
    char line[500];
    while(fgets(line, 500, f) != NULL){
        line[strlen(line)-1] = ' ';
        line[strlen(line)] = '|'; //Adaug un caracter pentru a usura citirea;
        sumaPuncte += prelucrareLinie(line);
    }

    printf("Suma punctelor este -> %d\n", sumaPuncte);
    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului sursa!\n");
        exit(-1);
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Numar invalid de argumente!\n");
        exit(-1);
    }

    citireDate(argv[1]);
    return 0;
}