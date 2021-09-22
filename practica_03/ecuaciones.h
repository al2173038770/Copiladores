#ifndef ecuaciones_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "escritura.h"

void estableceTipo(char *reng);


int logaritmo(char *reng){
    char log[5]={reng[0],reng[1],reng[2],reng[3],'\0'};
    if(strcmp(log,"log_")==0){
     //Se descarta el primer caracter de la nueva cadena
        char *quita= strrchr(reng,'_'); 
        char *sig=strdup(quita+1);
        
        //Este es solo una bandera para que no continuo buscando elementos en el puntero
        if(sig[0]=='\0'){
            return 0;
        } 
        estableceTipo(sig);
        return 1;
    }
    return 0;
}

int numero(char c,char reng[]){
    int num[10] = {0,1,2,3,4,5,6,7,8,9};
    int i;
    char n[2]={c,'\0'};

    for(i=0;i<10;i++){
        if(atoi(n)==num[i]){
            strcat(lengC,n);
            
            //Se descarta el primer caracter de la nueva cadena
            char *quita= strrchr(reng,c); 
            char *sig=strdup(quita+1);

            //Este es solo una bandera para que no continuo buscando elementos en el puntero
            if(sig[0]=='\0'){
                return 0;
            }

            estableceTipo(sig); 
            return 1;
        }
    }
    return 0;
}

int parentesisEcu(char c, char *reng){    
    int ascii = 40; //Numero ascii de " ( "

    if(c== (char) ascii){
        char *parentesis, *token,*quita;
        token = strtok(reng,")");
        quita = strrchr(token,(char)ascii);
        parentesis = strdup(quita+1);
        
        strcat(lengC,"(");
        if(parentesis[0]=='\0'){
            return 0;
        }
        estableceTipo(parentesis);

        strcat(lengC,")");
        return 1;
    }
    return 0; 
}

int raizEcu(char c, char *reng){
    int ascii = 92; //Numero ascii de " \ "

    if(c == (char) ascii ){
        char *base, *token,*quita;
        token = strtok(reng,"/"); //Se consige token a "/"
        quita = strrchr(token,(char)ascii);//Se obtiene la posición de "\"
        base = strdup(quita+1); //Se separa el valor de la raiz
        
        if(atoi(base)==2){
            strcat(lengC,"sqrt("); //Concatena caracteres
            
            if(base[0]=='\0'){
                return 0;
            }
            estableceTipo(base);
            
            strcat(lengC,")");
            return 1;
        }else{

            strcat(lengC,"pow(");
            token=strtok(NULL,"\0");//Se mantiene con la misma cadena por eso se pone NULL
            if(token[0]=='\0'){
                return 0;
            }   
            estableceTipo(token); 
            
            strcat(lengC,",1/");
            strcat(lengC,base);
            strcat(lengC,")");
            return 1;
        }
    }
    return 0;
}

void estableceTipo(char *reng){
    char c = reng[0];
    printf("\n%c == %s",c,reng); 

    // Restringe que la cadena reng no tenga 
    // restorna los simbolos ")" "/"
    if(reng[0]=='\0'  ){
        return;
    }

    if(numero(c,reng)==1){
        return;
    }
    
    if(parentesisEcu(c,reng)==1){
        return;
    }
    
    if(raizEcu(c,reng)==1){
        return;
    }            

    if(logaritmo(reng)==1){
        printf("\nLogaritmo");
        return;
    }

    system("pause"); 
}

#endif
