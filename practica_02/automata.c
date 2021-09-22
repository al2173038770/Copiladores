#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definiciones extra para poder leer codigo
#define Entero 0
#define Flotante 1

//Declaracion de alfabeto y cadeanas de apoyo
const char alfabeto[12]={'0','1','2','3','4','5','6','7','8','9','.'};
char n[50],s[50];

        

//Estructura que almacenara el tipo de dato
struct Numero{
    int dato[2];
    int tipo;
};

int estado0(char c){
    int i,t_al = sizeof(alfabeto);
    //Analizaremos del 0 al 9 a exepcion del ultimo elemento " . "
    for(i=0;i<t_al-2;i++){
        if(c == alfabeto[i]){
            //Si pertenece al alfabeto concatenamos y segimos en el estado q0
                printf(" estado q0\n");
                char cadenaTem[2];
                cadenaTem[0] = c;
                cadenaTem[1]='\0';
                strcat(n,cadenaTem);
            return 0;
        }
    }
    //Si no se encuetra el numero pasamos al estado q1
    if(c == alfabeto[t_al-2]){
        printf(" pasando a q1\n");
        return 1;
    }
    else{
        return -1;
    }
}

int estado1(char c){
    int i,t_al = sizeof(alfabeto);
    //Analizaremos del 0 al 9 a exepcion del ultimo elemento " . "
    for(i=0;i<t_al-2;i++){
        if(c == alfabeto[i]){
            //Si se encuntra el numero nos matenemos en q1
            printf(" estado q1\n");
            char cadenaTem[2];
            cadenaTem[0] = c;
            cadenaTem[1] = '\0';
            strcat(s,cadenaTem);
            return 1;
        }
    }
    //Si no se encuetra pasamos al estado q2
    if(c == alfabeto[t_al-2]){
        printf(" pasando a q2\n");
        return 2;
    }
    else{
        return -1;
    }
}

void estado2(){
    //Dado que caiga en este estado deja de pertenecer al lenguaje
    printf(" en estado q2\n");
    printf("\n No puede continuar ya que existen mas de dos puntos");            
}

struct Numero automataFND(char cadena[]){
    int i=0;
    int t = strlen(cadena);
    struct Numero num;
    //Lo iniciamos tipo 1 que sera entero 
    num.tipo=Entero;
    int edo = 0;
    
    while(i<t){
        if(edo == 0){
            printf("%c esta en",cadena[i]);
            edo = estado0(cadena[i]);
        }else if(edo == 1){                
            //Si llegamos al estado 1 automaticamente se cataloga como flotante
            printf("%c esta en",cadena[i]);
            edo = estado1(cadena[i]); 
            num.tipo = Flotante;
        }else if(edo == 2){
            //Si llega a este estado no pertenece al lenguaje
            estado2();
            num.tipo = -1;
            return num;
        
        }else if(edo < 0){
            //Si el valor del estado segun estado1() o estado2() es negativo
            //Se debe a que no existe el valor dentro de las tramas de transición
            //ya que no el simbolo no existe en el alfabeto
            printf("\nNo pertece %c en el alfabeto" ,cadena[i]);
            num.tipo = -1;
            return num;
        }
        i++; 
    }
    num.dato[0] = atoi(n);
    
    if(num.tipo == Flotante){
        num.dato[1] = atoi(s);
        return num;
    }
    
    return num;
}

int main(){
    //Cadena que sera evaluada en el automata
    char cadena[] = "1231414.1234141341";
    struct Numero num = automataFND(cadena);
    int i;
    
    printf("\n El numero [entero,decimal] = [%i,%i]  ",num.dato[0],num.dato[1]);
    if(num.tipo==Entero)    
        printf("es un entero");
    else if(num.tipo==Flotante)
        printf("es un flotante");
    else
        printf("\n no es un numero ni flotante ni entero");

    return 0;
}
