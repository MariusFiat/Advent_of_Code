#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void printArray(const unsigned long int array[], const int size){
    for(int i = 0; i < size; i++){
        printf("%lu ", array[i]);
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

    printf("Minimul este -> %llu\n", min);
    return min;
}

void scoatereMapare(char* line, unsigned long long int* dest, unsigned long long int* src, unsigned long long int* range){
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

unsigned long long int citireDate(char* File);

void cautareSeeds(char* File, int* contor){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului2\n");
        exit(-1);
    }

    char line[500];
    char* p = NULL;
    unsigned long long int valueStart, range2;
    unsigned long long int* arraySeeds = NULL;
    int contorSeeds = 0;
    unsigned long long int val, min;
    
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
        valueStart = atol(p); //Salvez valoare de start seed

        p = strtok(NULL, " ");
        range2 = atol(p); //Salvez range seed
        
        for(unsigned long int i = valueStart + 1; i < valueStart + range2; i++){ //Adaug seeds de la valueStart pana la valueStart + range2 - 1;
            arraySeeds = realloc(arraySeeds, (contorSeeds + 1) * sizeof(unsigned long long int));
            if(!arraySeeds){
                fprintf(stderr, "Eroare la alocarea memoriei pentru seeds!\n");
                exit(-1);
            }
            arraySeeds[contorSeeds++] = i;
        }
        
        val = citireDate(File);
        if(val < min){
            min = val;
        }

        free(arraySeeds);
        p = strtok(NULL, " ");
        printf("Da\n");
    }

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului2\n");
        exit(-1);
    }
    printf("Valoarea minima este -> %llu\n", min);
}

unsigned long long int citireDate(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului sursa!\n");
        exit(-1);
    }

    char line[500];
    char* p = NULL;
    unsigned long long int* arraySeeds = NULL;
    int* arrayDaConversie = NULL;
    int contorSeeds = 0;
    unsigned long int valueStart;
    unsigned long int range2;

    if(fgets(line, 500, f) == NULL){
        fprintf(stderr, "Date incorecte!\n");
        exit(-1);
    }
    /*
    p = strtok(line, " "); //Elimin cuvantul seeds din prima linie;
    p = strtok(NULL, " ");
    */
    /*
    while(p){
        arraySeeds = realloc(arraySeeds, (contorSeeds + 1) * sizeof(unsigned long long int));
        if(!arraySeeds){
            fprintf(stderr, "Eroare la alocarea memoriei pentru seeds!\n");
            exit(-1);
        }
        arraySeeds[contorSeeds++] = atol(p);
        valueStart = atol(p); //Salvez valoare de start seed

        p = strtok(NULL, " ");
        range2 = atol(p); //Salvez range seed
        
        for(unsigned long int i = valueStart + 1; i < valueStart + range2; i++){ //Adaug seeds de la valueStart pana la valueStart + range2 - 1;
            
        }
        p = strtok(NULL, " ");
        printf("Da\n");
    }
    arrayDaConversie = calloc(sizeof(int), contorSeeds * sizeof(int));
    //printArray(arraySeeds, contorSeeds);
    */

    unsigned long long int dest, src, range, val;

    while(fgets(line, 500, f) != NULL){
        if(strlen(line) < 3){
            //printArray(arraySeeds, contorSeeds);
            //printf("\n");
            continue;
        }
        else if(isdigit(line[0]) == 0){
            //arrayDaConversie = resetareArrayConversie(arrayDaConversie, contorSeeds);
            //printArray(arrayDaConversie, contorSeeds);
            continue;
        }
        else{
            scoatereMapare(line, &dest, &src, &range);
            //printf("%llu %llu %llu\n", dest, src, range);
            
            for(int i = 0; i < contorSeeds; i++){
                val = arraySeeds[i];
                if(arrayDaConversie[i] == 0){
                    arraySeeds[i] = convertor(dest, src, range, arraySeeds[i]);
                    if(arraySeeds[i] != val){
                        arrayDaConversie[i] = 1;
                    }
                }
            }
        }
    }
    //printArray(arraySeeds, contorSeeds);
    unsigned long long int  min = calculMin(arraySeeds, contorSeeds);
    //printf("Convertor dest 49 src 53 range 8 -> %ld\n", convertor(49, 53, 8, 53));

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului!\n");
        exit(-1);
    }
    free(arrayDaConversie);
    free(arraySeeds);
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