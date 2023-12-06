#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void printArray(const unsigned long long int array[], const int size){
    for(int i = 0; i < size; i++){
        printf("%llu ", array[i]);
    }
    printf("\n");
}

unsigned long long int convertor(const unsigned long long int dest, const unsigned long long int src, const unsigned long long int range, const unsigned long long int value){
    unsigned long long int newValue = value;
    if(value >= src && value < src + range){
        if(src >= dest){
            newValue = value - (src - dest);
        }
        else
        {
            newValue = (dest - src) + value;
        }
    }
    return newValue;
}

unsigned long long int calculMin(const unsigned long long int array[], const int size){
    unsigned long long int min = array[0];
    for(int i = 1; i < size; i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    //printf("Minimul este -> %llu\n", min);
    return min;
}

void scoatereMapare(char* line, unsigned long int* dest, unsigned long int* src, unsigned long int* range){
    char* p = NULL;
    if(line != NULL){
        *dest = atol(line);
        p = strtok(line, " ");
        p = strtok(NULL, " ");
        *src = atol(p);
        p = strtok(NULL, "\n");
        *range = atol(p);
    }
}

int* resetareArrayConversie(int* array, const int size){
    for(int i = 0; i < size; i++){
        array[i] = 0;
    }
    return array;
}

void citireDate(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului sursa!\n");
        exit(-1);
    }

    char line[500];
    char* p = NULL;
    unsigned long long int* arraySeeds = NULL, *arraySeeds2 = NULL;
    int* arrayDaConversie = NULL;
    int contorSeeds = 0;
    int contor2 = 0;
    int contor = 0;
    unsigned long long int value;
    unsigned long long int minim;

    if(fgets(line, 500, f) == NULL){
        fprintf(stderr, "Date incorecte!\n");
        exit(-1);
    }
    p = strtok(line, " "); //Elimin cuvantul seeds din prima linie;
    p = strtok(NULL, " ");
    while(p){
        arraySeeds = realloc(arraySeeds, (contorSeeds + 1) * sizeof(unsigned long long int));
        if(!arraySeeds){
            fprintf(stderr, "Eroare la alocarea memoriei pentru seeds!\n");
            exit(-1);
        }
        arraySeeds[contorSeeds++] = atol(p);

        /*
        valueStart = atol(p); //Salvez valoare de start seed

        p = strtok(NULL, " ");
        range2 = atol(p); //Salvez range seed
        
        for(unsigned long int i = valueStart + 1; i < valueStart + range2; i++){ //Adaug seeds de la valueStart pana la valueStart + range2 - 1;
            arraySeeds = realloc(arraySeeds, (contorSeeds + 1) * sizeof(unsigned long int));
            arraySeeds[contorSeeds++] = i;
        }
        */
        p = strtok(NULL, " ");
    }

    //printf("Numarul de valori seeds este -> %d\n", contorSeeds);
    //Aici o sa vreau sa fac o bucla in care sa calculez fiecare set de seeds;
    while(contor2 < contorSeeds)
    {
        //printf("Da\n");
        contor = arraySeeds[contor2 + 1];
        arraySeeds2 = realloc(arraySeeds2, contor * sizeof(unsigned long long int));
        arrayDaConversie = calloc(sizeof(int), contor * sizeof(int));

        if(!arraySeeds2){
            fprintf(stderr, "Memorie insuficienta arrayseeds2!\n");
            exit(-1);
        }

        if(!arrayDaConversie){
            fprintf(stderr, "Memorie insuficienta arrayDaConversie!\n");
            exit(-1);
        }

        for(int i = 0; i < contor; i++){
            *(arraySeeds2 + i) = i + arraySeeds[contor2];
        }

        //printArray(arraySeeds2, contor);
        unsigned long int dest, src, range, val;

        fseek(f, 0, SEEK_SET);
        while(fgets(line, 500, f) != NULL){
            if(strlen(line) < 3){
                //printArray(arraySeeds, contorSeeds);
                //printf("\n");
                continue;
            }
            else if(isdigit(line[0]) == 0){
                arrayDaConversie = resetareArrayConversie(arrayDaConversie, contor);
                //printArray(arrayDaConversie, contorSeeds);
                continue;
            }
            else{
                scoatereMapare(line, &dest, &src, &range);
                //printf("%lu %lu %lu\n", dest, src, range);
                
                for(int i = 0; i < contor; i++){
                    val = arraySeeds2[i];
                    if(arrayDaConversie[i] == 0){
                        arraySeeds2[i] = convertor(dest, src, range, arraySeeds2[i]);
                        if(arraySeeds2[i] != val){
                            arrayDaConversie[i] = 1;
                        }
                    }
                }
                
            }
            
            value = calculMin(arraySeeds2, contor);
            if(value < minim){
                minim = value;
            }

            if(contor2 == 0){
                minim = value;
            }

            //free(arrayDaConversie);
            //free(arraySeeds2);
        }
        contor2 += 2;
    }
    //printArray(arraySeeds, contorSeeds);
    free(arrayDaConversie);
    free(arraySeeds);
    free(arraySeeds2);

    //printf("Convertor dest 49 src 53 range 8 -> %ld\n", convertor(49, 53, 8, 53));
    printf("Pozitia minima este -> %llu\n", minim);

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului!\n");
        exit(-1);
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Numar invalid de argumentr!\n");
        exit(-1);
    }

    citireDate(argv[1]);
    return 0;
}


//Ce am invatat de aici;
/*
    ?Functia atoi se foloseste pe int;
    ?Pentru numere mai mari am nevoie de atol altfel im taie din numar si am numere negative, care nu intra in memoria stabilita;
    ?Sa am grija la dimensiunea datelor cu care lucrez!;
*/