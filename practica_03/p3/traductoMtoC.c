#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define aM "M.txt"
#define aC "C.txt"

char expC[]={};
char expM[]={};
void estadoS(char cadena[]);
void estadoA(char cadena[]);
void estadoB(char cadena[]);
void estadoC(char cadena[]);
void estadoD(char cadena[]);
void estadoE(char cadena[]);
void estadoF(char cadena[]);
void estadoG(char cadena[]);
void separaIgual(char cadena[]);
void sepAster(char cadena[]);
void sepOperArit(char cadena[],char oper);
void forPotecia(char cadena[]);
void formaRaiz(char cadena[]);

void leerFormula(){
    FILE *f = fopen(aM,"r");
    if(f==NULL){
        return;
    }
    while(!feof(f)){
        fgets(expM,100,f);
    }
}
void escribirFormula(){
    FILE *f;
    f = fopen(aC,"at");
    if(f == NULL){
        printf("Error al abrir archivo");
        return;
    }
    else{
        fprintf(f,"%s;\n",expC);
        fclose(f);
    }
}

int main(){
    leerFormula();
    estadoS(expM);
    escribirFormula();
    return 0;

}


void separaIgual(char cadena[]){
    char *token;

    token=strtok(cadena,"=");

    estadoA(token);

    strcat(expC,"=");

    token=strtok(NULL,'\0');
    fflush(stdin);
    estadoA(token);

}

void sepAster(char cadena[]){
    char *token;
    //Separamos el interior de la cadena

    token=strtok(cadena,"(");   //Quitamos el primer parentesis

    strcat(expM,"(");            //Instertamos el caracter en la expresion C

    token=strtok(NULL,")");     //Separamos el contenido entre parentesis
    estadoA(token);             //Enviamos el contenido al estadoA

    strcat(expM,")");           //Al retornar lo escrito en la expresion C cerramos parentesis

    //Verificamos si existe mas contenido;
    token=strtok(NULL,'\0');
    if(strlen(token)!=0){
        //Si encontramos mas contenido lo enviamos nuevamente al estadoS
        estadoA(token);
    }
}

void sepOperArit(char cadena[],char oper){
    char *token;
    char op[2]={oper,'\0'};

    token=strtok(cadena,op);             //Se toma la primera parte de la cadena para seguir analizandola
    estadoA(token);                     //Enviamos la cadena

                                        //Una vez retornado la parte derecha insertamos la operacion aritmetica
    if(oper==':'){
        char div[2]={(char)92,'\0'};    //Dado que la divicion es el uni que no se parece a C lo cambiamos
        strcat(cadena,div);             //Se pone caracter
    }else{
        strcat(cadena,op);
    }

    token=strtok(NULL,'\0');            //Se toma la segunda parte de la cadena para seguir analizandola
    estadoA(token);                     //Eviamos la seguna parte del operador
}

void forPotecia(char cadena[]){
    char *token;
    //Base
    token=strtok(expM,"^");

    //Exponente
    strcat(expC,"pow(");        //Escribimos que es una potencia
    estadoA(token);             //Eviamos la base al estadoS
    strcat(expC,",");           //Ecribios en el lenguaje C que la base ya se esctribio;
    token=strtok(NULL,'\0');    //Separamos el exponente de la cadena
    estadoA(token);             //Enviamos el exponente al estado S
    strcat(expC,")");           //Una vez impreso en lenguaje C cerramos la expresion
}

void formaRaiz(char cadena[]){
    char s1 = (char)92;     //Caracter '\'
    char s2 = (char)47;     //Caracter '/'

    char b1[2]={s1,'\0'};
    char b2[2]={s2,'\0'};

    if(cadena[0]==s1){
        if(cadena[1]=='2'){
            if(cadena[2]==s2){
                //Es raiz cuadrada
                strcat(expC,"sqrt(");   //Escribimos en lenguaje C

                char *token;
                token=strtok(cadena,b2); //Separamos lo que sigue despues de '/'
                token=strtok(NULL,'\0');
                                        //Eviamos el contenido de la raiz al estado A
                estadoA(token);
                strcat(expC,")");       //Al retotar el valor de la exprecion imprimimos el parentesis final
            }
        }
        else{
            //Raiz a la N
            char *token1,*token2;

            token1=strtok(cadena,s1);   //Separamo contenido entre "\" "/"
            token1=strtok(NULL,s2);

            token2=strtok(NULL,'\0');    //Separamos contenido despues de "/"

            strcat(expC,"pow(");
                estadoA(token2);
            strcat(expC,",1/(");
                estadoA(token1);
            strcat(expC,"))");
            return;
        }
    }
    return;
}


void estadoG(char cadena[]){
    strcat(expC,cadena);
    return;
}

void estadoF(char cadena[]){
    char r=(char)92;
    if(cadena[0] == r){ //Comparamos el valor de la primera cadena con el valor en ascsii "\" para saber si es raiz
        formaRaiz(cadena);
        return;
    }
    estadoG(cadena);
    return;
}

void estadoE(char cadena[]){
    int i=0;
    char logaritmo[]="log_10";
    char subCad[6];
    memcpy(subCad,&cadena[0],6);

    if(strcmp(subCad,logaritmo)==0){
        char *token;
        token=strtok(cadena,"(");
        strcat(expC,"log(");
        estadoA(cadena);
        strcat(expC,"log)");
    }else{
        estadoF(cadena);
    }
    return;
}

void estadoD(char cadena[]){
    int i=0;
    while(cadena[i]!='\0'){
        if(cadena[i]=='^'){
            int posGorro=i;
            forPotecia(cadena);
            return;
        }
        i++;
    }
    estadoE(cadena);
    return;

}

void estadoC(char cadena[]){
    int i=0;
    while(cadena[i]!='\0'){
        if(cadena[i]=='+'){
            sepOperArit(cadena,cadena[i]);
            return;
        }
        else if(expM[i]=='-'){
            sepOperArit(cadena,cadena[i]);
            return;
        }
        i++;
    }
    estadoD(cadena);
    return;
}

void estadoB(char cadena[]){
    int i=0;
    //Mientras el caracter de la expresion Matematica no sea "fin de cadena" se analiza el siguiente caracter
    while(cadena[i]!='\0'){
        if(cadena[i]=='*'){                   //Si se encuetra el caracter '+' en la cadena
            sepOperArit(cadena,cadena[i]);
            return;
        }else if(cadena[i]==':'){
            sepOperArit(cadena,cadena[i]);
            return;
        }
        i++;
    }
    //Si no es un simbolo aritmetica el contenido pasa al estado A
    estadoC(cadena);
    return;
}

void estadoA(char cadena[]){
    if(cadena[0]=='('){                           // Si en el arreglo expM en la posicion del apuntador es asterisco
        sepAster(cadena);                          //Separamos el contenido de asterisco y retornamos al estado S
    }
    else{
        estadoB(cadena);
    }
    return;
}

void estadoS(char cadena[]){
    int i=0;

    while(cadena[i]!='\0'){
    //Si se encuentra una igualdad separamos la cadean en dos
        if(cadena[i]=='='){
            separaIgual(cadena);
            return;
        }
        i++;
    }
    estadoA(cadena);
    return;
}
