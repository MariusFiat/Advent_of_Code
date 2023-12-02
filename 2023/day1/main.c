#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

void prelucrareDate2(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului de input!\n");
        exit(-1);
    }

    char line[500], ch;
    int cntLinii = 0, digit1 = 0, digit2 = 0, sum = 0;
    bool ok1 = false, ok2 = false;

    while(fgets(line, 500, f) != NULL){
        digit1 = 0; digit2 = 0;
        ok1 = false; ok2 = false;
        cntLinii++;

        for(int i = 0; i < strlen(line); i++){
            if(isdigit(line[i]))
            {
                ok1 = true;
                ch = line[i];
                digit1 = atoi(&ch);  //? De ce aici folosesc  &ch
                for(int i = strlen(line)-1; i >= 0; i--){
                    if(isdigit(line[i]))
                    {
                        if(ok1 == true){
                            ok2 = true;
                            ch = line[i];
                            digit2 = atoi(&ch); //? Si aici;
                            break;
                        }
                    }
                }
                if(ok2 == true)
                {
                    sum += digit1 * 10 + digit2;
                    printf("Sum %d is %d\n", cntLinii, sum);
                    break;
                }
            }
        }
    }

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului de input!\n");
        exit(-1);
    }
}

//Partea 2;
void cautaDigitCuLitere(char* line, int* firstDigit ,int* lastDigit, int* firstSpot, int* secondSpot){
    char *one = NULL, *two = NULL, *three = NULL, *four = NULL, *five = NULL, *six = NULL, *seven = NULL, *eight = NULL, *nine = NULL;
    //bool b1 = false, b2 = false, b3 = false, b4 = false, b5 = false, b6 = false, b7 = false, b8 = false, b9 = false;

    one = strstr(line, "one");
    two = strstr(line, "two");
    three = strstr(line, "three");
    four = strstr(line, "four");
    five = strstr(line, "five");
    six = strstr(line, "six");
    seven = strstr(line, "seven");
    eight = strstr(line, "eight");
    nine = strstr(line, "nine");

    //int first = strlen(line), last = 0;
    int l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, l8 = 0, l9 = 0;
    
    // Diferenta dintre pointeri  == 0 daca cifra e fix la inceputul liniei, > 0  daca cifra e in dreapta, -1 daca nu o gasesc
    l1 = one != NULL ? one - line : -1;
    l2 = two != NULL ? two - line : -1;
    l3 = three != NULL ? three - line : -1;
    l4 = four != NULL ? four - line : -1;
    l5 = five != NULL ? five - line : -1;
    l6 = six != NULL ? six - line : -1;
    l7 = seven != NULL ? seven - line : -1;
    l8 = eight != NULL ? eight - line : -1;
    l9 = nine != NULL ? nine - line : -1;

    int array[9] = {l1, l2, l3, l4, l5, l6, l7, l8, l9};

    //bool ok = false;
    int max = -1;
    int maxv = -1;
    int minv = -1;
    int min = strlen(line);

    for(int i = 1; i <= 9; i++){
        if(array[i-1] != -1)
        {
            if(array[i-1] <= min){
                min = array[i-1];
                *firstSpot = array[i-1];
                minv = i;
            }
            if(array[i-1] >= max){
                max = array[i-1];
                maxv = i;
                *secondSpot = array[i-1];
            }
        }
    }
    *firstDigit = minv;
    *lastDigit = maxv;
}

void prelucrareDate3(char* File){
    FILE* f = fopen(File, "r");
    if(!f){
        fprintf(stderr, "Eroare la deschiderea fisierului de input!\n");
        exit(-1);
    }

    char line[200], ch;
    int cntLinii = 0, digit1 = 0, digit2 = 0, sum = 0, digit1Litere = 0, digit2Litere = 0;
    int secondSpot = 0, firstSpot = 0, lastFirstSpot = 0, lastSecondSpot = 0;
    bool ok = false, okdigit = false;
    char numere[9][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    

    while(fgets(line, 200, f) != NULL){
        digit1 = 0; digit2 = 0, digit1Litere = 0, digit2Litere = 0;
        firstSpot = 0, secondSpot = 0;
        cntLinii++;
        ok = false;
        okdigit = strchr(line, '1') == NULL && strchr(line, '2') == NULL && strchr(line, '3') == NULL && strchr(line, '4') == NULL && strchr(line, '5') == NULL && strchr(line, '6') == NULL && strchr(line, '7') == NULL && strchr(line, '8') == NULL && strchr(line, '9') == NULL;
        

        cautaDigitCuLitere(line, &digit1Litere, &digit2Litere, &firstSpot, &secondSpot);
        //printf("digit1Litere %d digit2Litere %d firstSpot %d secondspot %d\t", digit1Litere, digit2Litere, firstSpot, secondSpot);
        if(digit1Litere != -1){
            ok = true;
            lastFirstSpot = firstSpot;
            while(true){
                if(strstr(line + lastFirstSpot, numere[digit1Litere-1]) != NULL)
                {
                    lastFirstSpot = line - strstr(line + lastFirstSpot, numere[digit1Litere - 1]);
                }
                else
                {
                    break;
                }
            }

            while(true){
                if(strstr(line + lastSecondSpot, numere[digit2Litere - 1]) != NULL)
                {
                    lastSecondSpot = line - strstr(line + lastSecondSpot, numere[digit2Litere - 1]);
                }
                else
                {
                    break;
                }
            }
        }

        printf("%d %d\n", lastFirstSpot, lastSecondSpot);
        for(int i = 0; i < strlen(line); i++){
            if(isdigit(line[i]))
            {
                if(ok){
                    if(i < firstSpot){
                        ch = line[i];
                        digit1 = atoi(&ch);
                        break;
                    }
                    else
                    {
                        
                        digit1 = digit1Litere;
                        break;
                    }
                }
                else
                {
                    ch = line[i];
                    digit1 = atoi(&ch);  //? De ce aici folosesc  &ch
                    break;
                }
            }
            // else if(!okdigit)
            // {
            //     if(ok){
            //         digit1 = digit1Litere;
            //         break;
            //     }
            // }
            if(digit1 == 0){
                digit1 = digit1Litere;
            }
        }
        for(int i = strlen(line)-1; i >= 0; i--){
            if(isdigit(line[i]))
            {
                if(ok){
                    if(secondSpot < i){
                        ch = line[i];
                        digit2 = atoi(&ch); //? Si aici;
                        break;
                    }
                    else
                    {
                        digit2 = digit2Litere;
                        break;
                    }
                }
                else
                {
                    ch = line[i];
                    digit2 = atoi(&ch); //? Si aici;
                    break;
                }
            }
            // else if(!okdigit)
            // {
            //     if(ok){
            //         digit2 = digit2Litere;
            //         break;
            //     }
            //}
            if(digit2 == 0){
                digit2 = digit2Litere;
            }
        }

        sum += digit1 * 10 + digit2;
        printf("Sum %d is %d -> digit1 %d digit2 %d\n", cntLinii, sum, digit1, digit2);
    }

    if(fclose(f) != 0){
        fprintf(stderr, "Eroare la inchiderea fisierului de input!\n");
        exit(-1);
    }
}


int main(void){
    char File[10] = "in2.txt";

    //prelucrareDate2(File);
    prelucrareDate3(File);
    return 0;
}