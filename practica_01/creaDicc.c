#include <stdio.h>
#include <stdlib.h>
#define diccEI "diccionarioIE.txt"
#define diccIE "diccionarioEI.txt"

void menuPetition();
void dictionaryIE(char i[],char e[]);
void dictionaryEI(char e[],char i[]);

int main(){
    menuPetition();    
    return 0;
}

void dictionaryIE(char i[],char e[]){
    FILE *f; 
    f = fopen(diccIE,"at");
    if(f == NULL){
        printf("Error al abrir archivo");
        return;
    }
    else{   
        fprintf(f,"%s=%s;\n",i,e); 
        fclose(f);
    }
}

void dictionaryEI(char e[],char i[]){
    FILE *f;
    f = fopen(diccEI,"at");
    if(f == NULL){
        printf("Error al abrir archivo");
        return;
    }
    else{   
        fprintf(f,"%s=%s;\n",e,i); 
        fclose(f);
    }
}

void menuPetition(){
    printf("Enter words in spanish and your translate: ");
    int j=0;
    for(j= 0;j<20;j++){
        char e[50];
        char i[50];

        printf("\nSpanish : ",j+1);
        scanf("%s",e);
        printf("\nIngles : ");
        scanf("%s",i);

        dictionaryEI(e,i);
        dictionaryIE(i,e);
    }
}

