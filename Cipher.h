//Parte del codigo es reciclado del curso de Estructura de Datos de UPIITA
//Part of this code was recycled of UPIITA's Estructura de Datos course.
#ifndef _Cipher_
#define _Cipher_
#include <wchar.h>
#include <stdlib.h>
#define MAXIMO(i,d) (((i)>(d))?(i):(d))

typedef struct _Node{
	char c;
	int f;
	struct _Node *left;
	struct _Node *right;
	struct _Node * next;
}Node;

Node * create (char c, int f){
	Node * newNode;
	newNode = (Node *) malloc(sizeof(Node));
	newNode->c = c;
	newNode->f = f;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->next = NULL;
	return newNode;
	
}

Node * insertLeaf(Node * tree, char c, int f){
	Node * origin;
	Node * newNode;
	
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


void preorder(Node * origin){
	if(origin!=NULL){
		printf("Character %d, Frequency: %i\n",origin->c, origin->f);
		preorder(origin->left);
		preorder(origin->right);
	}
}

void inorder(Node * origin){
	if(origin!=NULL){
		inorder(origin->left);
		printf("Character %d, Frequency: %i\n",origin->c, origin->f);
		inorder(origin->right);
	}
}

void posorder(Node * origin){
	if(origin!=NULL){
		posorder(origin->left);
		posorder(origin->right);
		printf("Character %d, Frequency: %i\n",origin->c, origin->f);
	}
}

void moveLeft(Node ** tree){
	Node * aux1;
	Node * aux2;
	
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

void deleteLeaf(Node ** tree, int search){
	Node * aux;
	if(*(tree)==NULL){
		printf("\nNO EXISTE EL Node A BORRAR");
	}else{
		if(search < (*tree)->f)
		deleteLeaf(&(*tree)->left,search);
		else if(search > (*tree)->f)
		deleteLeaf(&(*tree)->right,search);
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

int height(Node *tree){
	if(tree==NULL)
	return 0;
	else 
	return MAXIMO(height(tree->left)+1,height(tree->right)+1);
}

int size(Node * begin){

    int i = 0;

    if(begin == NULL){
        printf("\n La FILA esta vacia\n");
    }
    else{
        while(begin != NULL){
            i++;
            begin = begin->next;
        }

    }

    return i;

}

Node * push(Node * begin, char c, int f){
    Node * newNode;
    newNode = create(c, f);

    if(begin == NULL){
        begin = newNode;
    }
    else{
        Node * aux = begin;

        while(aux->next != NULL){

            aux = aux->next;
        }

        aux->next = newNode;
    }

    return begin;
}

Node * pushInit(Node * top, char c, int f){
    Node * newNode;
    newNode = create(c, f);
    
    if(top != NULL){
        newNode->next=top;
    }
        
    return newNode;
}

Node * pushIn(Node * begin, char c,int f, int pos){
    Node * newNode;
    Node* aux;
    int i = 0;
    int len = size(begin);

    newNode= create(c, f);

    if(pos >= 0 && pos < len){
        if(pos == 0){

            begin = pushInit(begin,c, f);
        }
        else{
            aux = begin;
            for( i = 0;i < pos-1; i++){
                aux = aux->next;
            }

            newNode ->next=aux->next;
            aux->next = newNode;

        }
    }
    else{
        printf("Invalid position");
    }

    return begin;
}

Node * deleteBegin(Node * begin){
    Node * aux;
    aux = begin;

    if(begin !=  NULL){
        begin=begin->next;
        free(aux);
    }

    return begin;
}

//Borrar en poscicion

Node * popListElement(Node * begin, int pos){

    Node * aux;
    Node * aux2;
    Node * toFree;
    int i = 0;
    int len = 0;
    len = size(begin);

    if(pos >= 0 && pos < len){

        if(pos == 1){
            begin = deleteBegin(begin);
        }
        else{
            aux = begin;

            for(i = 0; i<pos-1; i++){
                aux = aux->next;
            }
            
            aux2 = aux->next->next;
            toFree = aux->next;
            aux->next = aux2;
            free(toFree);
        }

    }
    else{
        printf("Invalid position");
    }

    return begin;    
}

Node * popList(Node * begin){

    Node * aux;
    Node * aux2;

    if(begin == NULL){
        printf("\nThe list is empty\n");
    }
    else{
        aux = begin;

        while(aux->next->next != NULL){
            aux = aux->next;
        }
        aux2 = aux->next;
        free(aux2);
        aux->next = NULL;
        
    }

    return begin;
}

/*
Node * changeIndexOfList(Node * begin, char c,int dato, int datoCambio){

    Node * aux;
    int existe = 0;

    if(begin == NULL){
        printf("\nLa lista esta vacia\n");
    }
    else{

        aux = begin;

        while(aux != NULL && existe == 0){

            if(aux->dato == dato){
                existe = 1;
                aux->dato = datoCambio;
            }
            else{
                aux = aux->next;
            }

        }

        if(existe == 0){
            printf("\nNo existe el dato a cambiar\n");
        }

    }

    return begin;

}
*/

void displayList(Node * begin){

    if(begin == NULL){
        printf("\n The list is empty\n");
    }
    else{
        while(begin != NULL){
            printf("\n Character %c\tFrequency: %i\n", begin->c, begin->f);

            begin= begin->next;
        }
    }
}

wchar_t * readFile(char * fileName){

	FILE * file = fopen(fileName, "r, ccs=UTF-8");
	wchar_t message[50];
	wchar_t * msg;
	int length = 0, i = 0;

	if(file == 	NULL){
		printf("\nThere was a problem reading your file\n");
		exit(1);
	}
	else{
		fgetws(message, 50, file);
		fflush(stdin);
		fclose(file);
		length = wcslen(message);
		msg = calloc(length,sizeof(wchar_t));

		for(i = 0; i < length; i++){
			msg[i] = message[i];
		}
	}	
	
	return msg;
}

#endif