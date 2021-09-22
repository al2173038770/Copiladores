#ifndef estados_h


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

#endif
