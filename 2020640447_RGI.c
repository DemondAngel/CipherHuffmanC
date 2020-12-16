#include <locale.h>
#include "2020640447_RJI.h"

int main(){
    
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
    return 0;
}