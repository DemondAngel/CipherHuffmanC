//Parte del codigo es reciclado del curso de Estructura de Datos de UPIITA
//Part of this code was recycled of UPIITA's Estructura de Datos course.
#ifndef _Cipher_h
#define _Cipher_h
#include <stdio.h>
#include <stdlib.h>
#define MAXIMO(i,d) (((i)>(d))?(i):(d))

typedef struct _Nodo{
	int dato;
	struct _Nodo *izquierda;
	struct _Nodo *derecha;
}Nodo;

Nodo * crear (int d){
	Nodo * nuevo;
	nuevo = (Nodo *)malloc(sizeof(Nodo));
	nuevo->dato = d;
	nuevo->izquierda=NULL;
	nuevo->derecha=NULL;
	return nuevo;
	
}

Nodo *insertar(Nodo * arbol, int d){
	Nodo * raiz;
	Nodo * nuevo;
	
	nuevo = crear(d);
	
	if(arbol==NULL){
		return nuevo;
	}else{
		raiz=arbol;
		while(raiz!=NULL){
			if(nuevo->dato > raiz->dato){
				if(raiz->derecha==NULL){
				raiz->derecha=nuevo;
				return arbol;	
				}else{
					raiz=raiz->derecha;	
				}
			}else{
				if(raiz->izquierda==NULL){
					raiz->izquierda=nuevo;
					return arbol;
				}else{
					raiz=raiz->izquierda;
				}
				
			}
		}
	}
	
}


void preorder(Nodo * raiz){
	if(raiz!=NULL){
		printf("%d\n",raiz->dato);
		preorder(raiz->izquierda);
		preorder(raiz->derecha);
	}
}

void inorder(Nodo * raiz){
	if(raiz!=NULL){
		inorder(raiz->izquierda);
		printf("%d\n",raiz->dato);
		inorder(raiz->derecha);
	}
}

void posorder(Nodo * raiz){
	if(raiz!=NULL){
		posorder(raiz->izquierda);
		posorder(raiz->derecha);
		printf("%d\n",raiz->dato);
	}
}

void moverIzquierda(Nodo ** arbol){
	Nodo * aux1;
	Nodo * aux2;
	
	aux2 = (*arbol);
	aux1 = (*arbol)->izquierda;
	
	while(aux1->derecha!=NULL){
		aux2 = aux1;
		aux1 = aux1->derecha;
	}
	(*arbol)->dato = aux1->dato;
	if(aux2 == (*arbol))
		aux2->izquierda = aux1->izquierda;
	else
		aux2->derecha = aux1->izquierda;
	
	(*arbol)=aux1;
}

void borrar(Nodo ** arbol, int buscar){
	Nodo * aux;
	if(*(arbol)==NULL){
		printf("\nNO EXISTE EL NODO A BORRAR");
	}else{
		if(buscar < (*arbol)->dato)
		borrar(&(*arbol)->izquierda,buscar);
		else if(buscar > (*arbol)->dato)
		borrar(&(*arbol)->derecha,buscar);
		if(buscar == (*arbol)->dato){
			aux = (*arbol);
			if(aux->izquierda==NULL)
			(*arbol)=aux->derecha;
			else if(aux->derecha==NULL)
			(*arbol) = aux->izquierda;
			else
			moverIzquierda(&aux);
			free(aux);
			
		}
	}
	
}

int altura(Nodo *arbol){
	if(arbol==NULL)
	return 0;
	else 
	return MAXIMO(altura(arbol->izquierda)+1,altura(arbol->derecha)+1);
	
}

#endif _Cipher_h




