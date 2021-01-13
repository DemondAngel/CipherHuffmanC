#include <locale.h>
#include "Cipher.h"

int cipher(){
    setlocale(LC_CTYPE, "");
    char fileName[100];
    Nodo * arbolList = NULL;
    Nodo * list = NULL;
    
    printf("Porfavor escriba el nombre de su archivo: \n");
    printf("Please write your file name: \n");

    gets(fileName);

    printf("\nLeyendo archivo y creando lista\n");
    list = readFile(fileName, list);

    printf("\nOrdenando lista\n");
    list = mergeSort(list);

    printf("\nCreando Arbol\n");
    arbolList = createTree(list);

    printf("\nHaciendo recorrido inorder del arbol\n");
    inorder(arbolList, "","");
    
    printf("\nCreando palabra cifrada\n");
    int * numbers = getBinary(list);
    
    printf("\nGenerando archivo binario\n");
    writeBinaryFile(numbers);

    printf("\nGenerando llave\n");
    writeKeyFile(arbolList);

    printf("\nCodificacion terminada\n");
    free(arbolList);
    free(numbers); 
}

void decipher(){

    Nodo * tree = NULL;
    char * textBin = readBinaryFile();
    tree = readKeyAndBuildTree(tree);
    inorder(tree, "", "");
    
    printWord(textBin, tree);
    printf("\nSe ha terminado de decifrar su texto\n");
    free(tree);
    free(textBin);
}

int main(){
    
    int opc = 0;

    printf("\nBienvenido a la codificacion Huffman, eliga una opcion: \n");
    printf("\n1. Cifrar\n");
    printf("\n2. Decifrar\n");

    scanf("%i", &opc);
    
    if(opc == 1){
        fflush(stdin);
        cipher();
        
    }
    else{
        decipher();
        fflush(stdin);
    }

    
    return 0;
}