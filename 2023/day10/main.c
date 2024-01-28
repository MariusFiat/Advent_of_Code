#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE_LINE 500
#define START_CH 'S'

void printMatriceDate(char** matriceDate, const int numarLinii, const int numarColoane){
    for(int i = 0; i < numarLinii; i++){
       printf("%s", matriceDate[i]);
    }
}

void cautaStart(char** matriceDate, const int numarLinii, const int numarColoane, int* xStart, int* yStart){
    for(int i = 0; i < numarLinii; i++){
        for(int j = 0; j < numarColoane; j++){
            if(matriceDate[i][j] == START_CH){
                *xStart = i; *yStart = j;
            }
        }
    }
}

/*
    Folosesc 3 functii, una principala de unde incep modificarea matricei de date[..]
    [..] si celelalte doua cu care plec in directii opuse pe ruta circulara pana cand[..]
    ajung la un punct comun;
*/

// void cautaRamura1(char** matriceDate, const int numarLinii, const int numarColoane, int* xCauta1, int* yCauta1){ 
    
// }

// void cautaRamura2(char** matriceDate, const int numarLinii, const int numarColoane, int* xCauta2, int* yCauta2){

// }

void urmatorulPas(char** matriceDate, const int numarLinii, const int numarColoane, const int xCurent, const int yCurent, int* nextX, int* nextY){
    if(matriceDate[xCurent][yCurent] == '|')
    {
        if(isdigit(matriceDate[xCurent - 1][yCurent]))
        {
            *nextX = xCurent + 1;
            *nextY = yCurent;
        }
        else
        {
            *nextX = xCurent - 1;
            *nextY = yCurent;
        }
    }
    else if(matriceDate[xCurent][yCurent] == '-'){
        if(isdigit(matriceDate[xCurent][yCurent-1])){
            *nextX = xCurent;
            *nextY = yCurent + 1;
        }
        else
        {
            *nextX = xCurent;
            *nextY = yCurent - 1;
        }
    } else if(matriceDate[xCurent][yCurent] == 'L'){
        if(isdigit(matriceDate[xCurent - 1][yCurent])){
            *nextY = yCurent + 1;
            *nextX = xCurent;
        }
        else
        {
            *nextY = yCurent;
            *nextX = xCurent - 1;
        }
    } else if(matriceDate[xCurent][yCurent] == 'J'){
        if(isdigit(matriceDate[xCurent][yCurent - 1])){
            *nextX = xCurent - 1;
            *nextY = yCurent;
        }
        else{
            *nextX = xCurent;
            *nextY = yCurent - 1;
        }
    } else if(matriceDate[xCurent][yCurent] == '7'){
        if(isdigit(matriceDate[xCurent+1][yCurent])){
            *nextX = xCurent;
            *nextY = yCurent - 1;
        }
        else
        {
            *nextX = xCurent + 1;
            *nextY = yCurent;
        }
    } else if(matriceDate[xCurent][yCurent] == 'F')
    {
        if(isdigit(matriceDate[xCurent][yCurent + 1])){
            *nextX = xCurent + 1;
            *nextY = yCurent;
        }
        else{
            *nextX = xCurent;
            *nextY = yCurent + 1;
        }
    }
}

void cautaRuta(char** matriceDate, const int numarLinii, const int numarColoane, int xCauta1, int yCauta1, int xCauta2, int yCauta2, int distanta){
    if(xCauta1 == xCauta2 && yCauta1 == yCauta2)
    {
        matriceDate[xCauta1][yCauta1] = distanta;
        return;
    }
    else
    {
        int xNext1, xNext2, yNext1, yNext2;
        urmatorulPas(matriceDate, numarLinii, numarColoane, xCauta1, yCauta1, &xNext1, &yNext1);
        urmatorulPas(matriceDate, numarLinii, numarColoane, xCauta2, yCauta2, &xNext2, &yNext2);
        matriceDate[xCauta1][yCauta1] = distanta;
        matriceDate[xCauta2][yCauta2] = distanta;
        cautaRuta(matriceDate, numarLinii, numarColoane, xNext1, yNext1, xNext2, yNext2, distanta + 1);
    }
    
}

void incepeCautarea(char** matriceDate, const int numarLinii, const int numarColoane, const int xStart, const int yStart){
    int xCauta1 = -1, yCauta1 = -1, xCauta2 = -1, yCauta2 = -1;

    if(xStart > 0 && yStart > 0){
        if(matriceDate[xStart][yStart + 1] == '-'){
            xCauta1 = xStart;
            yCauta1 = yStart + 1;
        }
        else if(matriceDate[xStart][yStart - 1] == '-'){
            xCauta1 = xStart;
            yCauta1 = yCauta1 - 1;
        }

        if(matriceDate[xStart - 1][yStart] == '|'){
            xCauta2 = xStart - 1;
            yCauta2 = yStart;
        }
        else if(matriceDate[xStart + 1][yStart] == '|'){
            xCauta2 = xStart + 1;
            yCauta2 = yStart;
        }
    }
    // else
    // {
    //     if(xStart == 0){
    //         if(yStart == 0){
    //             xCauta1 = xStart;
    //             yCauta1 = yStart + 1;
    //             xCauta2 = xStart+1;
    //             yCauta2 = yStart;
    //         }
    //         else if(yStart == numarColoane - 1)
    //         {
    //             xCauta1 = xStart;
    //             yCauta1 =  yStart - 1;
    //             xCauat2 = xStart + 1;
    //             yCauta2 = yStart;
    //         }
    //         else
    //         {}
    //     }
    // }
    cautaRuta(matriceDate, numarLinii, numarColoane, xCauta1, yCauta1, xCauta2, yCauta2, 1);
}

char** citireDate(const char* File, int* numarLinii, int* numarColoane){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului de input!\n");
        exit(-1);
    }

    char** matriceDate = NULL;
    char line[SIZE_LINE];

    while(fgets(line, SIZE_LINE, f) != NULL){
        matriceDate = (char**)realloc(matriceDate, (*numarLinii + 1) * sizeof(char*));
        if(!matriceDate){
            fprintf(stderr, "Eroare la alocarea memoriei pentru o noua linie de date!\n");
            exit(-1);
        }

        matriceDate[*numarLinii] = (char*)realloc(matriceDate[*numarLinii], SIZE_LINE * sizeof(char));
        if(!matriceDate[*numarLinii]){
            fprintf(stderr, "Eroare la alocarea memoriei pentru scrierea noii linii de date!\n");
            exit(-1);
        }

        strncpy(matriceDate[(*numarLinii)++], line, SIZE_LINE);
    }

    *numarColoane = strlen(matriceDate[0]);

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului de input!\n");
        exit(-1);
    }

    return matriceDate;
}

void eliberareMemorie(char** matrice, const int size){
    for(int i = 0; i < size; i++){
        free(matrice[i]);
    }
    free(matrice);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Numar invalid de argumente!\n");
        exit(-1);
    }

    int numarLinii = 0, numarColoane = 0;
    char** matriceDate = citireDate(argv[1], &numarLinii, &numarColoane);
    printMatriceDate(matriceDate, numarLinii, numarColoane);

    int xStart, yStart;
    cautaStart(matriceDate, numarLinii, numarColoane, &xStart, &yStart);
    printf("Start -> (%d, %d)\n", xStart, yStart);

    incepeCautarea(matriceDate, numarLinii, numarColoane, xStart, yStart);
    printMatriceDate(matriceDate, numarLinii, numarColoane);

    eliberareMemorie(matriceDate, numarLinii);
    return 0;
}