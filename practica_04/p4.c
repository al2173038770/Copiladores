#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
	char *valor;
	struct nodo *izq;
	struct nodo *der;
	struct nodo *cen;
}Nodo;


Nodo* estadoA(char cad[]);
Nodo* estadoB(char cad[]);
Nodo* estadoC(char cad[]);

char stringAna[]={};
Nodo *arbol = NULL;

Nodo* creaNodo(){
	Nodo *nuevoNodo = (Nodo *) malloc (sizeof(Nodo *));
	nuevoNodo->cen=NULL;
	nuevoNodo->der=NULL;
	nuevoNodo->izq=NULL;
	strcpy(nuevoNodo->valor,"");
	return nuevoNodo;
}


Nodo* estadoC(char cad[]){
	Nodo* nodo=creaNodo();
	if(cad[0]=='('){
		Nodo* nodoD=creaNodo();
		Nodo* nodoI=creaNodo();
		strcpy(nodoI->valor,"(");
		strcpy(nodoD->valor,")");

		char *tokenP;	//Separamos la parte de adentro de los parentecis de la cadena

		tokenP=strtok(cad,"(");
		tokenP=strtok(tokenP,")");
		nodo->izq = nodoI;
		nodo->cen = estadoA(tokenP);				//Envimos el contenido de vuelta al estado A
		nodo->der = nodoD;
	}else{
		strcpy(nodo->valor,cad);		//Agragamos la cadena
	}
	return nodo;
}

Nodo* estadoB(char cad[]){
	Nodo* nodo=creaNodo();
	printf("EstadoB: \n");
	int tamCad= strlen(cad);			//Medimos el tamaño de la cadena principal
	char *tokenA,*tokenB;				
	tokenA=strtok(cad,"*");				//Obtemeos el token hasta el simbolo '+'
	int tamTokenA=strlen(tokenA);		//Medimos el tamaño de la cadena con token 
	if(tamCad==tamTokenA){				//Si son del mismo tamaño significa que no existe el signo '+'
		strcpy(nodo->valor,"<unit>");
		nodo->cen = estadoC(cad);		//Po lo tanto enviamos toda la cadena directamente a B
	}
	else if(tamCad>tamTokenA){
		tokenB=strtok(NULL,"\0");		//Tomamos el siguiente token hasta fin de cadena
		strcpy(nodo->valor,"*");
		nodo->izq = estadoB(tokenA);	//Enviamos la parte izquierda de la cadena 
		nodo->der = estadoC(tokenB);	//Enviamos la parte derecha de la cadena	
	}
	return nodo;
}

Nodo* estadoA(char cad[]){
	Nodo *nodo=creaNodo();
	int tamCad= strlen(cad);			//Medimos el tamaño de la cadena principal
	char *tokenA,*tokenB;				
	tokenA=strtok(cad,"+");				//Obtemeos el token hasta el simbolo '+'
	int tamTokenA=strlen(tokenA);		//Medimos el tamaño de la cadena con token 
	if(tamCad==tamTokenA){				//Si son del mismo tamaño significa que no existe el signo '+'
		strcpy(nodo->valor,"<term>");	//Po lo tanto enviamos toda la cadena directamente a B
		nodo->cen=estadoB(cad);			
	}
	else if(tamCad>tamTokenA){
		tokenB=strtok(NULL,"\0");		//Tomamos el siguiente token hasta fin de cadena
		strcpy(nodo->valor,"+");
		nodo->izq = estadoA(tokenA);	//Enviamos la parte izquierda de la cadena 
		nodo->der = estadoB(tokenB);	//Enviamos la parte derecha
	}
	return nodo;
}

int main(){
	scanf("%s",&stringAna);
	char cad[]={};
	strcpy(cad,stringAna);
	arbol = estadoA(cad);
	return 0;
}
