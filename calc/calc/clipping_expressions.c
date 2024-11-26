#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "laba.h"

int clipping_expressions()
{
    FILE* file = fopen("program.txt", "r");
    FILE* const_file = fopen("constant_expressions.txt", "w");

    char* str = (char*)calloc(100, sizeof(char));
    char* find= (char*)calloc(100, sizeof(char));
    char c;
    int k = 0;
    
    while(fgets(str, 100, file) != NULL){
        //printf("str = %s\n", str);
        if((find = strchr(str, '=')) != NULL){
            while((c = *++find) != ';')
                fputc(c, const_file);
            fputc('\n', const_file);
            k++;
        }
    }


    fclose(file);
    fclose(const_file);

    return k;
}
