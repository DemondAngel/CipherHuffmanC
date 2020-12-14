//Parte del codigo es reciclado del curso de Estructura de Datos de UPIITA
//Part of this code was recycled of UPIITA's Estructura de Datos course.
#ifndef _Cipher_
#define _Cipher_
#include <wchar.h>
#include <stdlib.h>
#define MAXIMO(i,d) (((i)>(d))?(i):(d))

char * word;

typedef struct _Nodo{
	char c;
	int f;
    char * way;
	struct _Nodo *left;
	struct _Nodo *right;
	struct _Nodo * next;
} Nodo;

Nodo * createNodo (char c, int f){
    
	Nodo * newNode;
    
	newNode = (Nodo *) malloc(sizeof(Nodo));
    
    if(newNode == NULL){
        printf("Murio");
    }

	newNode->c = c;
	newNode->f = f;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->next = NULL;
    
	return newNode;
	
}

Nodo * insertLeaf(Nodo * tree, char c, int f){
	Nodo * origin;
	Nodo * newNode;
	
	newNode = createNodo(c, f);
	
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
		printf("Character %c, Frequency: %i\n",origin->c, origin->f);
		preorder(origin->left);
		preorder(origin->right);
	}
}

void inorder(Nodo * origin, char * d, char * pre){

	if(origin!=NULL){

        int lenPre = strlen(pre);
        origin->way = NULL;
        int i = 0;
        origin->way = (char *) calloc(lenPre + 1, sizeof(char));
        
        for(i = 0; i < lenPre; i++){
            origin->way[i] = pre[i];
        }
        
        strcat(origin->way, d);
        
		inorder(origin->left, "0", origin->way);
		printf("Character %c, Frequency: %i\n",origin->c, origin->f);
		inorder(origin->right,"1", origin->way);
	}
}

void posorder(Nodo * origin){
	if(origin!=NULL){
		posorder(origin->left);
		posorder(origin->right);
		printf("Character %c, Frequency: %i\n",origin->c, origin->f);
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

void deleteLeaf(Nodo ** tree, int search){
	Nodo * aux;
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

int height(Nodo *tree){
	if(tree==NULL)
	return 0;
	else 
	return MAXIMO(height(tree->left)+1,height(tree->right)+1);
}

int size(Nodo * begin){

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

Nodo * push(Nodo * begin, char c, int f){
    Nodo * newNode;
    
    newNode = createNodo(c, f);

    if(begin == NULL){
        begin = newNode;
    }
    else{
        Nodo * aux = begin;

        while(aux->next != NULL){

            aux = aux->next;
        }

        aux->next = newNode;
    }

    return begin;
}

Nodo * pushInit(Nodo * top, char c, int f){
    Nodo * newNode;
    newNode = createNodo(c, f);
    
    if(top != NULL){
        newNode->next=top;
    }
        
    return newNode;
}

Nodo * pushIn(Nodo * begin, char c,int f, int pos){
    Nodo * newNode;
    Nodo* aux;
    int i = 0;
    int len = size(begin);

    newNode= createNodo(c, f);

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

Nodo * deleteBegin(Nodo * begin){
    Nodo * aux;
    aux = begin;

    if(begin !=  NULL){
        begin=begin->next;
        free(aux);
    }

    return begin;
}

//Borrar en poscicion

Nodo * popListElement(Nodo * begin, int pos){

    Nodo * aux;
    Nodo * aux2;
    Nodo * toFree;
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

Nodo * popList(Nodo * begin){

    Nodo * aux;
    Nodo * aux2;

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

Nodo * changeIndexOfListFrequency(Nodo * begin, char c, int frequency){

    Nodo * aux;
    int existe = 0;

    if(begin == NULL){
        printf("\nLa lista esta vacia\n");
    }
    else{

        aux = begin;

        while(aux != NULL && existe == 0){

            if(aux->c == c){
                existe = 1;
                aux->f = frequency;
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

void changeIndexOfList(Nodo *begin, char c, int f, int posicion) {
    Nodo *aux = begin;
    int i = 0;
    int longitudLista = size(begin);

    if(posicion >= 0 && posicion < longitudLista){
            for(i = 0; i<posicion-1;i++){ //Verify
                aux = aux ->next;
            }

            aux ->c = c;
            aux -> f =f;
    }else{
        printf("Posicion no valida");
    }
}

Nodo * indexOfChar(Nodo * begin, char c){

    Nodo * aux = NULL;
    int existe = 0;

    if(begin == NULL){
        printf("\nLa lista esta vacia\n");
    }
    else{

        aux = begin;

        while(aux != NULL && existe == 0){

            if(aux->c == c){
                existe = 1;
                break;
            }
            else{
                aux = aux->next;
            }

        }

        if(existe == 0){
            printf("\nNo existe el dato a cambiar\n");
        }

    }

    return aux;

}

Nodo * elementList(Nodo * begin, int position){

    Nodo *aux = begin;
    int i = 0;
    int longitudLista = size(begin);

    if(position >= 0 && position < longitudLista){
            for(i = 0; i<position;i++){
                aux = aux ->next;
            }
    }else{
        aux = NULL;
        printf("Posicion no valida");
    }

    return aux;

}

Nodo * lastIndexOfFreq(Nodo * begin, int freq){
    //The list must be ordered
    Nodo * aux = begin;

    while(aux->next != NULL &&( aux->f <= freq && aux->next->f <=freq)){

        aux = aux->next;
        
    }

    return aux;

}

void displayList(Nodo * begin){

    if(begin == NULL){
        printf("\n The list is empty\n");
    }
    else{
        while(begin != NULL){
            printf("\n Character %c\tFrequency: %i\n", begin->c, begin->f);
            printf("\nWay: %s\n", begin->way);
            begin= begin->next;
        }
    }
}

Nodo * insertFrequency(Nodo * list, char c){

    int i = 0, j = 0;

    Nodo * aux;
    
        
    aux = indexOfChar(list, c);
    
    if(aux == NULL){
        list = push(list, c, 1);
    }
    else{
        list = changeIndexOfListFrequency(list, c, aux->f+1);
    }
    
    return list;
}

Nodo * readFile(char * fileName, Nodo * list){

	FILE * file = fopen(fileName, "r, ccs=UTF-8");
	wchar_t wc;
	int length = 0, i = 0;

	if(file == 	NULL){
		printf("\nThere was a problem reading your file\n");
		exit(1);
	}
	else{
        
        while((wc = fgetwc(file)) != WEOF){

            wprintf(L"%c", wc);

            char c = formatChar(wc);
            
            if(word == NULL){
                length = 1;
                word = calloc(length, sizeof(char));
            }
            else{
                length++;
                word = realloc(word, length);
            }

            word[i] = c;

            list = insertFrequency(list, c);
            i++;
        }

	}	
	fclose(file);
    
	return list;
}

Nodo * sublist(Nodo * list, int begin, int end){

    Nodo * sublist = NULL;
    Nodo * aux = list;
    int tamanio = size(list);
    int i = 1;
    for(i = 1; i <= tamanio; i++){

        if(begin <= i && i <= end){
            sublist = push(sublist, aux->c, aux->f);
        }
        
        aux = aux->next;
    }

    return sublist;

}

Nodo * sortList(Nodo * list){
    Nodo * aux = list;
    int i = 0;
    
    if(size(list) != 1){
        
        if(aux->f >= aux->next->f){
            char c = aux->c;
            char f = aux->f;

            changeIndexOfList(list, aux->next->c, aux->next->f, 0);
            changeIndexOfList(list, c, f, 1);

        }
         

    }
    
    return list;
}

Nodo * interSort(Nodo * list1, Nodo * list2){

    Nodo * newList = NULL;

    while(list1 != NULL || list2 != NULL){
        
        if(list1 != NULL && list2 != NULL){
            if(list2->f >= list1->f){
                newList = push(newList, list1->c, list1->f);
                list1 = list1->next;
            }
            else{
                newList = push(newList, list2->c, list2->f);
                list2 = list2->next;
            }
        }
        else{
            if(list1 == NULL){
                newList = push(newList, list2->c, list2->f);
                list2 = list2->next;
            }
            else{
                if(list2 == NULL){
                    newList = push(newList,list1->c, list1->f);
                    list1 = list1->next;
                }
            }
        }
        
    }

    return newList;

}

 Nodo * mergeSort(Nodo * list){

     Nodo * mitad1 = NULL;
     Nodo * mitad2 = NULL;
     Nodo * nuevaLista = NULL;

    int mitad = 0, largo = 0;
    largo = size(list);

    if(largo <= 1){
        nuevaLista = list;
    }
    else{
        mitad = largo/2;
        
        mitad1 = sublist(list, 1, mitad);
        mitad2 = sublist(list, mitad+1, largo);

        if(size(mitad1) <= 2){   
            mitad1 = sortList(mitad1);
        }
        else{
            mitad1 = mergeSort(mitad1);
        }
        
        if(size(mitad2) <= 2){
            mitad2 = sortList(mitad2);
        }
        else{
            mitad2 = mergeSort(mitad2);
        }


        nuevaLista = interSort(mitad1, mitad2);

    }

    free(mitad1);
    free(mitad2);

    return nuevaLista;
 }

 Nodo * createTree(Nodo * list){

    Nodo * aux = list;
    
    while(aux->next != NULL){
        
        Nodo * node1 = aux;
        Nodo * node2 = aux->next;

        Nodo * newNode = createNodo('*', node1->f+node2->f);
        newNode->left = node1;
        newNode->right = node2;
        
        Nodo * lastEqFreq = lastIndexOfFreq(list, node1->f+node2->f);
        
        if(lastEqFreq->next != NULL){
            newNode->next = lastEqFreq->next;
        }
        
        lastEqFreq->next = newNode;
        
        aux = aux->next->next;
    }

    return aux;

}

void writeFileBin(Nodo * list){


    int len = strlen(word), i = 0;
    char * cipherWord = malloc(sizeof(char));
    
    for( i = 0; i < len; i++){
        printf("\nLetra: %c\n", word[i]);

        Nodo * letter = indexOfChar(list, word[i]);

        if(letter != NULL){
            strcat(cipherWord, letter->way);
        }
        
    }

    printf("\nCipher Word: %s\n", cipherWord);
    /*
    FILE * file = fopen("WordCompress.bin","wb");

    if(file == NULL){
        printf("\nThere was an error open the file\n");
        printf("\nHubo un error al abrir el archivo\n");
        exit(1);
    }
    else{

        


    }

    fclose(file);
    */

}
 
#endif