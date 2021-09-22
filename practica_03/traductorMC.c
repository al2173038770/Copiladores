#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "lectura.h"

char expM[100]={};
char expC[100]={};

int indiceC=0;
int indiceM=0;


/*
void estadoA(char expM[]){
    printf("stateA: %s\n",expM); 
}

//Funcio de separar funcion aritmetica de cadena y envia valor a su respectivo estado
void sepOpArit(int sizeM, int sizeC){
    char *token;
    char *simbolo=expM[*posM];
    //Separamos la primera parte de la expresion aritmetica:
        //Ejemplo:      [S1]  +  S2 
    token=strtok(expM,simbolo);            
    //Enviamos la parte [S1] al estado S en busca de parentesis o simbolos aritmetico 
    stateS(token);

    //Despues del simbolo aritmetico '+' el resto [S2] lo enviamos nuevamentea al estado S
    token=strtok(NULL,"/0");
    stateS(token);
}
*/
void sepAster(int sizeM, int sizeC){
    char *token;
    //Separamos el interior de la cadena 
    token=strtok(expM,'(');
    expC[posC]='(';        //Escribimos en arreglo el asterisco
            //Elebamos el puntero
    
    token=strtok(NULL,')');         //Separamos el contenido de asterisco 
    stateS(token,expC,posM,posC);   //Enviamos el contenido de asterisco a estado S

    expC[*posC]=')';        //Una vez retornado el contenido de asterisco cerramos el asterisco
    *posC=*posC+1;          //Incrementamos el contenido que ocupa el asterisco
}

void estadoS(){
    //expM[4]='a';
    //printf("%s\n",expM);
    if(expM[posM]=='('){                  // Si en el arreglo expM en la posicion del apuntador es asterisco
        sepaAster(); //Separamos el contenido de asterisco y retornamos al estado S
    }

    //Mientras el caracter de la expresion Matematica no sea "fin de cadena" se analiza el siguiente caracter
    int i=0;
    while(expM[i]!='\0'){

        if(expM[i=='+'){//Si se encuetra el caracter '+' en la cadena
            *posM=*posM+i;  //Se la posicion de 'i' para modificar el apuntado de la expresion matematica
            sepOpArit(expM,expM,posM,posC);//Se envia la cadena, con la posicion del apuntado 
            break;
        }
        else if(expM[*i]=='-'){
            *posM=*posM+i;
            sepOpArit(expM,expM,posM,posC);
            break;
        }
        else if(expM[i]=='*'){
            *posM=*posM+i;
            sepOpArit(expM,expM,posM,posC;
            break;
        }
        else if(expM[i]==':'){
            *posM=*posM+i;
            sepOpArit(expM,expM,posM,posC);
            break;
        }
        //
        i++;
        a=expM[*posM];
    }

    //Si no es un simbolo aritmetica el contenido pasa al estado A 
    estadoA(expM);
}

void estadoI(){
    int i=0, tempS=0;
    while(expM[i]!='\0'){                  
        if(expM[i]=='='){                   //Si se encuentra una igualdad separamos la cadean en dos
            char *token;
            token=strtok(expM,"=");
            tempS=strlen(expM);
            estadoS(tempS);
            posM+=tempS+1;

            token=strtok(NULL,"\0");
            tempS=strlen(expM);
            estadoS(newSize,sizeC);
            posM+=tempS;
            
            posC=strlen(expC);
        }
        i++;
    }
    if(strlen(expeC)!=0){
        estadoS();
    }
}

int main(){
    
    int sizeM=0, sizeC=0;
    scanf("%s",expM);
    sizeM=strlen(expM);

    printf("\n%s %d\n",expM, sizeM);

    

    return 0;

}

