#ifndef herramienta_h
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
forPotecia(char cadena[]);
void formaRaiz(char cadena[]);

void separaIgual(char cadena[]){
    char *token;

    token=strtok(cadena,"=");
    printf("%s\n",token);

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

#endif
