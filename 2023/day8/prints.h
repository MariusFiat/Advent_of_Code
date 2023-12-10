#ifndef __PRINTS_H
#define __PRINTS_H

typedef struct{
    char key[4], left[4], right[4];
}Data_t;

void printDirections(const char* arrayDirections, const int size);
void printData(const Data_t arrayData[], const int size);

#endif