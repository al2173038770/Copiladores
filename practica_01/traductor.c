#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define diccEspIng "diccionarioEI.txt"
#define diccIngEsp "diccionarioIE.txt"

struct diccBidirec{
    char espaniol[50];
    char ingles[50];
};

void menuInicio();
void obtenerFrase(char *frase);
void traducirFrase(char frase[],char archivo[],int tipo);
int buscarPalabra(char tokenFrase[],struct diccBidirec diccionario[], int numeroPalabras, int tipo);
void obtenerDiccionario(char archivo[],struct diccBidirec diccionario[],int tamanio, int tipo);
int comprobarTipoTraduccion(char archivo[]);
int numeroLineas(char archivo[]);
int comprobacionArchivo(FILE *f);

int main(){
    menuInicio();
    return 0;
}

void menuInicio(){
    printf("Elegir traduccion: \n");
    printf("\n1. Espaniol --> Ingles");
    printf("\n2. Ingles --> Espaniol");
    printf("\nOpcion: ");
    
    int tipo;
    scanf("%i",&tipo);

    if(tipo == 1){
        char frase[100];
        obtenerFrase(frase);
        traducirFrase(frase,diccEspIng,tipo);
    }
    else if(tipo== 2){
        char frase[100];
        obtenerFrase(frase);
        traducirFrase(frase,diccIngEsp,tipo);  
    }else{
        printf("Opcion no valida");
    }
}
/*
struct diccBidirec separarPalabra(char *dicc){
    struct diccBidirec diccionario;
    char *tokenDicc;

    tokenDicc= strtok(dicc,"=");
    strcpy(diccionario.espaniol,tokenDicc);
    tokenDicc = strtok(NULL,";");
    strcpy(diccionario.ingles,tokenDicc);

    return diccionario;
}
*/
int comprobacionArchivo(FILE *f){
    if(f==NULL){
        printf("ERROR AL ABRIR ARCHIVO");
        fclose(f);
        return 0;
    }
}

int numLineas(char archivo[]){
    char dicc[100];
    int count = 0;

    FILE *f = fopen (archivo,"r");

    if(comprobacionArchivo(f)==0){ 
        return 0;
    }
    
    fflush(stdin);

    fgets(dicc,100,f);
    while(!feof(f)){
        fgets(dicc,100,f);
        fflush(stdin);
        count++;            
    }

    fclose(f);
    return count;
}

int comprobarTipoTraduccion(char archivo[]){
    if(strcmp(archivo,diccEspIng)==0){
        return 1;
    }
    else if(strcmp(archivo,diccIngEsp)==0){
        return 2;
    }
}

void obtenerDiccionario(char archivo[],struct diccBidirec diccionario[],int tamanio,int tipo){
    FILE *f = fopen(archivo,"r");
    if(comprobacionArchivo(f)==0){ 
        return;
    }
    
    int i;
    char *token;    
    char reng[100];

        if(tipo==1){            
            for(i=0;i<tamanio;i++){
                fgets(reng,100,f);
                fflush(stdin);            
                token = strtok(reng,"=");
                strcpy(diccionario[i].espaniol,token);        
                token = strtok(NULL,";");
                strcpy(diccionario[i].ingles,token);
            }
        }
        else if(tipo==2){            
             for(i=0;i<tamanio;i++){
                fgets(reng,100,f);
                fflush(stdin);            
                token = strtok(reng,"=");
                strcpy(diccionario[i].ingles,token);        
                token = strtok(NULL,";");
                strcpy(diccionario[i].espaniol,token);
            }   
        }else{
            printf("Tipode traduccion no identificado");
        }

    fclose(f);
}

int buscaPalabra(char tokenFrase[],struct diccBidirec diccionario[],int numeroPalabras,int tipo){
    int i;
    if(tipo == 1){        
        for(i=0;i<numeroPalabras;i++){
            if(strcmp(diccionario[i].espaniol,tokenFrase)==0){
                return i;
            }
        }
    }else if(tipo == 2){
        for(i=0;i<numeroPalabras;i++){
            if(strcmp(diccionario[i].ingles,tokenFrase)==0){
                return i;
            }
        }
    }

    printf("\n Palabra * %s * no existe en diccionario!!!!\n",tokenFrase);
    return -1;

}

void traducirFrase(char frase[],char archivo[],int tipo){
    char *tokenFrase;
    int numeroPalabras = numLineas(archivo);
    int posicion;
    struct diccBidirec diccionario[numeroPalabras];    
    char traduccion[100]="T: ";
    
    obtenerDiccionario(archivo,diccionario,numeroPalabras,tipo);
    tokenFrase = strtok(frase," ");

    while(tokenFrase){
        posicion = buscaPalabra(tokenFrase,diccionario,numeroPalabras,tipo);        
        if(posicion == -1){            
            strcat(traduccion," ");
            strcat(traduccion,tokenFrase);
        }else{
            strcat(traduccion," ");
            if(tipo == 1){
                strcat(traduccion,diccionario[posicion].ingles);
            }else if(tipo == 2){
                strcat(traduccion,diccionario[posicion].espaniol);
            }
        }

        tokenFrase=strtok(NULL," ");
    }            
    printf("%s",traduccion);
}

void obtenerFrase(char *frase){
    fflush(stdin);
    printf("Introduce frase: ");
    scanf("%[^\n]",frase);
}



