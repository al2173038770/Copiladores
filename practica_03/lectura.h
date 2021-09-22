#ifndef lectura_h
#include <stdio.h>
#include <string.h>
#define fileM "M.txt"

struct ecuaciones{
    

};

void leerM(char reng[]){
    FILE *f;
    f = fopen(fileM,"r");
    
    if(f==NULL){
        printf("ERROR AL ABRIR ARCHIVO");
        return;
    }

    char *token;
    while(!feof(f)){
        fgets(reng,100,f);
        fflush(stdin);
    }
    fclose(f);
}

#endif