#include <stdio.h>
#include <stdlib.h>


void calculPosibilitati(const long int array1[], const long int array2[], const int size){
    long long int castiguriTotale = 1;
    for(int i = 0; i < size; i++){
        long long int valoareCurenta = 1, castig = 0, cazuriCastigatoare = 0;
        while(valoareCurenta < array1[i] /* && castig >= castigPrecedent */){
            //castigPrecedent = castig;
            castig = (array1[i] - valoareCurenta) * valoareCurenta;
            if(castig > array2[i]){
                //printf("Valoare -> %d\n", valoareCurenta);
                cazuriCastigatoare++;
            }
            valoareCurenta++;
        }
        //printf("Cazuri castigatoare index %d -> %d\n", i, cazuriCastigatoare);
        castiguriTotale *= cazuriCastigatoare;
    }
    printf("Castiguri totale posibile -> %lld\n", castiguriTotale);
}

void citireDate(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului de input!\n");
        exit(-1);
    }

    char line[100];
    fgets(line, 100, f);

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului de input!\n");
        exit(-1);
    }
}

int main(int argc, char* argv[]){
    //input 2;
    // int array1[] = {7, 15, 30};
    // int array2[] = {9, 40, 200};
    // int size = 3;

    //input mare
    
    // int array1[] = {46, 80, 78, 66};
    // int array2[] = {214, 1177, 1402, 1024};
    // int size = 4;
    

    //calculPosibilitati(array1, array2, size);
    
    //input mic partea 2;
    // int array3[] = {71530};
    // int array4[] = {940200};
    // calculPosibilitati(array3, array4, 1);

    //input mare partea2;
    long int array3[] = {46807866};
    long int array4[] = {214117714021024};
    calculPosibilitati(array3, array4, 1);

    return 0;
}