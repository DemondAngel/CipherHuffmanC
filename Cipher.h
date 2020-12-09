//Parte del codigo es reciclado del curso de Estructura de Datos de UPIITA
//Part of this code was recycled of UPIITA's Estructura de Datos course.
#ifndef _Cipher_
#define _Cipher_
#include <stdlib.h>
#define MAXIMO(i,d) (((i)>(d))?(i):(d))

typedef struct _Nodo{
	char c;
	int f;
	struct _Nodo *left;
	struct _Nodo *right;
	struct _Nodo * next;
}Nodo;

Nodo * create (char c, int f){
	Nodo * newNode;
	newNode = (Nodo *) malloc(sizeof(Nodo));
	newNode->c = c;
	newNode->f = f;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->next = NULL;
	return newNode;
	
}

Nodo * insert(Nodo * tree, char c, int f){
	Nodo * origin;
	Nodo * newNode;
	
	newNode = create(c, f);
	
	if(tree==NULL){
		return newNode;
	}else{
		origin=tree;
		while(origin!=NULL){
			if(newNode->f > origin->f){
				if(origin->right==NULL){
				origin->right=newNode;
				return tree;	
				}else{
					origin=origin->right;	
				}
			}else{
				if(origin->left==NULL){
					origin->left=newNode;
					return tree;
				}else{
					origin=origin->left;
				}
				
			}
		}
	}
	
}


void preorder(Nodo * origin){
	if(origin!=NULL){
		printf("Character %d, Frequency: %i\n",origin->c, origin->f);
		preorder(origin->left);
		preorder(origin->right);
	}
}

void inorder(Nodo * origin){
	if(origin!=NULL){
		inorder(origin->left);
		printf("Character %d, Frequency: %i\n",origin->c, origin->f);
		inorder(origin->right);
	}
}

void posorder(Nodo * origin){
	if(origin!=NULL){
		posorder(origin->left);
		posorder(origin->right);
		printf("Character %d, Frequency: %i\n",origin->c, origin->f);
	}
}

void moveLeft(Nodo ** tree){
	Nodo * aux1;
	Nodo * aux2;
	
	aux2 = (*tree);
	aux1 = (*tree)->left;
	
	while(aux1->right!=NULL){
		aux2 = aux1;
		aux1 = aux1->right;
	}
	(*tree)->f = aux1->f;
	(*tree)->c = aux1->c;
	if(aux2 == (*tree))
		aux2->left = aux1->left;
	else
		aux2->right = aux1->left;
	
	(*tree)=aux1;
}

void delete(Nodo ** tree, int search){
	Nodo * aux;
	if(*(tree)==NULL){
		printf("\nNO EXISTE EL NODO A BORRAR");
	}else{
		if(search < (*tree)->f)
		delete(&(*tree)->left,search);
		else if(search > (*tree)->f)
		delete(&(*tree)->right,search);
		if(search == (*tree)->f){
			aux = (*tree);
			if(aux->left==NULL)
			(*tree)=aux->right;
			else if(aux->right==NULL)
			(*tree) = aux->left;
			else
			moveLeft(&aux);
			free(aux);
			
		}
	}
	
}

int height(Nodo *tree){
	if(tree==NULL)
	return 0;
	else 
	return MAXIMO(height(tree->left)+1,height(tree->right)+1);
	
}

void readFile(){

}

#endif