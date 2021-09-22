#ifndef archivoEL_h
#define aM M.txt
#define aC C.txt
void leerFormula(){
    FILE *f = fopen(aM,"r");
    if(comprobacionArchivo(f)==0){
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



#endif
