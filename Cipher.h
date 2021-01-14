//Parte del codigo es reciclado del curso de Estructura de Datos de UPIITA
//Part of this code was recycled of UPIITA's Estructura de Datos course.
#ifndef _Cipher_
#define _Cipher_
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXIMO(i,d) (((i)>(d))?(i):(d))

char * word;

char formatChar(wchar_t wc){
    char newChar;

    if(wc == ' '){
        newChar = '_';
    }
    else{
        int charCode = toascii(wc);
        if(isascii(wc) == 0){
            
            if(wc == L'á' ||wc == L'ä' || wc == L'Á' ||wc == L'Ä'){
                charCode = 97;
            }
            else if(wc == L'é' ||wc == L'ë' || wc == L'É' || wc == L'Ë'){
                charCode = 101;
            }
            else if(wc == L'ï' || wc == L'í'  || wc == L'Í' || wc == L'Ï'){

                charCode = 105;
            }
            else if(wc == L'ó' ||wc == L'ö' || wc == L'Ö' || wc == L'Ó'){
                charCode = 111;
            }
            else if(wc == L'ú' ||wc == L'ü' || wc == L'Ú' || wc == L'Ü'){
                charCode = 117;
            }
            
        }

        newChar = tolower(charCode);
    }
    
    return newChar;
}

int fromBinToNumber(char * bin){

    int len = strlen(bin), i = 0, number = 0, j = 0;

    for(i = len-1; i > -1; i--, j++){

        if(bin[i] == '1'){
            number += pow(2,j);
        }
        
    }

    return number;

}

typedef struct _Nodo{
	char c;
	int f;
    char * way;
	struct _Nodo *left;
	struct _Nodo *right;
	struct _Nodo * next;
    struct _Nodo * back;
} Nodo;

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

Nodo * createNodo (char c, int f, char * way){
    
	Nodo * newNode;
    
	newNode = (Nodo *) malloc(sizeof(Nodo));

	newNode->c = c;
	newNode->f = f;
    newNode->way = way;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->next = NULL;
    newNode->back = NULL;
	return newNode;
	
}

Nodo * insertLeaf(Nodo * tree, char c, int f){
	Nodo * origin;
	Nodo * newNode;
	
	newNode = createNodo(c, f, NULL);
	
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

        inorder(origin->right,"1", origin->way);


              
	}

}

void postorder(Nodo * origin, FILE * file){
	if(origin!=NULL){
		postorder(origin->left, file);
		postorder(origin->right, file);
		fprintf(file, "%c %i ",origin->c, origin->f);
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
        
    }
    else{
        while(begin != NULL){
            i++;
            begin = begin->next;
        }

    }

    return i;

}

Nodo * push(Nodo * begin, char c, int f, char * way){
    Nodo * newNode;
    
    newNode = createNodo(c, f, way);

    if(begin == NULL){
        begin = newNode;
    }
    else{
        Nodo * aux = begin;

        while(aux->next != NULL){

            aux = aux->next;
        }

        aux->next = newNode;
        newNode->back = aux;
    }

    return begin;
}

Nodo * pushInit(Nodo * top, char c, int f, char * way){
    Nodo * newNode;
    newNode = createNodo(c, f, way);
    
    if(top != NULL){
        newNode->next=top;
        top->back = newNode;
    }
        
    return newNode;
}

Nodo * pushIn(Nodo * begin, char c,int f, char * way,int pos){
    Nodo * newNode;
    Nodo* aux;
    int i = 0;
    int len = size(begin);

    newNode= createNodo(c, f, way);

    if(pos >= 0 && pos < len){
        if(pos == 0){

            begin = pushInit(begin,c, f, way);
        }
        else{
            aux = begin;
            for( i = 0;i < pos-1; i++){
                aux = aux->next;
            }

            newNode->next=aux->next;
            aux->next = newNode;
            newNode->back = aux;
            newNode->next->back = newNode;

        }
    }
    else{
        
    }

    return begin;
}

Nodo * deleteBegin(Nodo * begin){
    Nodo * aux;
    aux = begin;

    if(begin !=  NULL){
        begin=begin->next;
        begin->back = NULL;
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
            aux2->back =aux;
            free(toFree);
        }

    }
    else{
        
    }

    return begin;    
}

Nodo * popList(Nodo * begin){

    Nodo * aux;
    Nodo * aux2;

    if(begin == NULL){
        
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
        
    }
}

Nodo * indexOfChar(Nodo * begin, char c){

    Nodo * aux = NULL;
    int existe = 0;

    if(begin == NULL){
        
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

Nodo * insertFrequency(Nodo * list, char c){

    int i = 0, j = 0;

    Nodo * aux;
    
        
    aux = indexOfChar(list, c);
    
    if(aux == NULL){
        list = push(list, c, 1, NULL);
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

            char c = formatChar(wc);
            
            if(word == NULL){
                length = 1;
                word = calloc(length, sizeof(char));
            }
            else{
                length++;
                word = realloc(word, sizeof(char)*length);
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
            sublist = push(sublist, aux->c, aux->f, NULL);
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
                newList = push(newList, list1->c, list1->f, NULL);
                list1 = list1->next;
            }
            else{
                newList = push(newList, list2->c, list2->f, NULL);
                list2 = list2->next;
            }
        }
        else{
            if(list1 == NULL){
                newList = push(newList, list2->c, list2->f, NULL);
                list2 = list2->next;
            }
            else{
                if(list2 == NULL){
                    newList = push(newList,list1->c, list1->f, NULL);
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

        Nodo * newNode = createNodo('*', node1->f+node2->f, NULL);
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

int convertBinToNumber(char * number){
 
    int len = strlen(number), num = 0, i = 0, j = 0; 
    for(i = len-1, j = 0; i > -1; i--, j++){

        if(number[i] == '1'){
            num += pow(2,j);
        }
    }

    return num;

}

int * interBinNumber(char * bin, int * numbers){

    if(numbers == NULL){
        numbers = calloc(2, sizeof(int));
        numbers[0] = 1;
    }
    else{
        numbers[0] += 1;
        numbers = (int * ) realloc(numbers, sizeof(int)*(numbers[0]+1));
    }

    int number = fromBinToNumber(bin);

    numbers[numbers[0]] = number;

    return numbers;
}

int * getBinary(Nodo * list){
    
    int * numbers = NULL;
    int i = 0, n = 0, j = 0, s = 0;
    int lenWord = strlen(word);
    Nodo * aux = NULL;
    char bin[8] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    for(i = 0; i< lenWord; i++){
        
        int lenBin = strlen(bin);
        
         Nodo * aux = indexOfChar(list, word[i]);

         if(aux != NULL){
             int lenWay = strlen(aux->way);
             
                if((lenBin + lenWay) < 7){
                    for(j = 0; j < lenWay; j++, n++){
                        bin[n] = aux->way[j];
                    }
                }
                else{
                    s = 0;
                    for(j = 0; j < 7-lenBin; j++, n++){
                        bin[n] = aux->way[j];
                        s++;
                    }

                }

                lenWay = strlen(aux->way);

                lenBin = strlen(bin);

                if(lenBin == 7){
                    numbers = interBinNumber(bin, numbers);
                    
                    n = 0;
                    for(j = 0; j < 7; j++){
                        bin[j] = '\0';
                    }
                    
                    for(j = s; j < lenWay; j++, n++){
                        bin[n] = aux->way[j];
                    }       
                    
                }       
                
         }
        
    }

    if(strlen(bin) < 7){
        int lenBin  =strlen(bin);
        for(j = lenBin; j < 7; j++){
            bin[j] = '0';
        }

        numbers = interBinNumber(bin, numbers);

    }

    return numbers;
}

void writeBinaryFile(int * numbers){

    FILE * file = fopen("codigo.bin", "wb");

    if(file == NULL){
        printf("\nHubo un error al abrir tu archivo\n");
        exit(1);
    }
    else{
        int largo = numbers[0];
        int i = 0;
        
        fwrite(numbers, largo+1, sizeof(int), file);
        
    }

    fclose(file);
}

void writeKeyFile(Nodo * arbol){

    FILE * file = fopen("llave.txt", "w");

    if(file == NULL){
        printf("\nHubo un error al abrir tu archivo\n");
        exit(1);
    }
    else{
        postorder(arbol, file);
    }

    fclose(file);
}

char * fromNumbersToBin(int * numbers, int len){
    
    char * textBin = calloc(0, sizeof(char));
    int i = 0;

    char numberBin[100];

    for(i = 0; i < len; i++){
        itoa(numbers[i],numberBin,2);

        int lenNumber = strlen(numberBin);
        char binAux[7];
        int z = 0;
        for(z = 0; z < 7; z++){
            binAux[z] = '\0';
        }

        if(lenNumber < 7){
            
            char zeroLeft[7-lenNumber+1];
            int j = 0;
            for(j = 0; j < 7-lenNumber+1; j++){
                zeroLeft[j] = '\0';
            }

            for(j = 0; j < 7-lenNumber; j++){
                zeroLeft[j] = '0';
            }
            strcat(binAux, zeroLeft);
        }
        
        strcat(binAux, numberBin);

        char textBinAux[strlen(textBin)+1];
        int sec = 0;

        strcpy(textBinAux, textBin);
        
        do{
            textBin = realloc(textBin,sizeof(char)*7*(i+1));
            if(textBin == NULL){
                printf("\nSi entra2\n");
                sec = 1;
            }
        }while(textBin == NULL);
        
        if(sec == 1){
            printf("\nSi entra2\n");
            strcpy(textBin, textBinAux);
        }
        
        strcat(textBin, binAux);
        
    }
    printf("\nFin\n");
    return textBin;

}
 
char * readBinaryFile(){
    int length = 0;
    FILE * file = fopen("codigo.bin", "rb");
    int * numbers = NULL;
    if(file == NULL){
        printf("\nHubo un problema al abrir su archivo\n");
        exit(1);
    }
    else{
        

        fread(&length, 1, sizeof(int), file);
        
        numbers = calloc(length, sizeof(int));
        
        fread(numbers, length, sizeof(int), file);
        
    }

    fclose(file);

    return fromNumbersToBin(numbers, length);
}

Nodo * readKeyAndBuildTree(Nodo * list){

    FILE * file = fopen("llave.txt", "rt");
    Nodo * raiz = NULL;
    Nodo * listAux = NULL;
    Nodo * aux = NULL;

    if(file == NULL){
        printf("\nHubo un problema al abrir su archivo llave\n");
        exit(0);
    }
    else{
        char letter = ' ';
        int frequency = 0;

        while(!feof(file)){
            
            fscanf(file, "%c %i ", &letter, &frequency);
            list = push(list, letter, frequency, NULL);
            
            
            if(letter == '*'){
                
                Nodo * u = list;

                while(u->next != NULL){
                    u = u->next;
                    
                }
                
                u ->left = u->back->back;
                u ->right = u->back;

                if(u->left->back == NULL){
                    u->back = NULL;
                    list = u;
                }
                else{
                    u->left->back->next = u;
                    u->back = u->left->back;
                }

                u->left->next = u->right;
                u->left->back = NULL;
                u->right->next = NULL;
                u->right->back = u->left;
                

                if(listAux == NULL){
                    
                    listAux = u->left;
                }
                else{
                    aux = listAux;
                    while(aux->next != NULL){
                        aux = aux->next;
                    }
                    
                    aux->next = u->left;
                    u->left->back = aux;
                }
               
                raiz = u;
            }
            
        }
    }

    fclose(file);
    
    if(listAux != NULL){

        raiz->next = listAux;
        raiz->back = NULL;
        listAux->back = raiz;
    }

    return raiz;
}

Nodo * searchLetter(Nodo * list, char c, int index){

    Nodo * sublist = NULL;
    Nodo * aux = list;
    //printf("\nEntra str: %s\n", str);
    while(aux != NULL){

        int wayLen = strlen(aux->way);
        
        if(index < wayLen){
            if(aux->way[index] == c){
                int lenWay = strlen(aux->way);
                char * way = calloc(lenWay, sizeof(char));
                strcpy(way, aux->way);
                sublist = push(sublist, aux->c, aux->f, way);
            }
        }

        aux = aux->next;
    }

    
    return sublist;

}

void printWord(char * textBin, Nodo * list){
    FILE * file = fopen("textDecoded.txt", "wt");
    int i = 0;
    int len = strlen(textBin);

    Nodo * sublist = list;
    int sublistLen = 0;
    int n = 0;
    for(i = 0; i < len; i++, n++){
        
        sublist = searchLetter(sublist, textBin[i], n);
        sublistLen = size(sublist);

        if(sublistLen == 1){
            fprintf(file, "%c", sublist->c);
            n = -1;
            free(sublist);
            sublist = list;

        }

    }

    fclose(file);

}

#endif