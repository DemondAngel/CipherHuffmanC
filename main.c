#include <locale.h>
#include "Utils.h"
#include "Cipher.h"

int main(){

    setlocale(LC_CTYPE, "");
    char fileName[100];
    Nodo * arbolList = NULL;
    Nodo * list = NULL;
    
    printf("Porfavor escriba el nombre de su archivo: \n");
    printf("Please write your file name: \n");

    gets(fileName);

    list = readFile(fileName, list);

    list = mergeSort(list);
    arbolList = createTree(list);

    printf("\nArbol\n");
    inorder(arbolList,"","");
    printf("\nLista\n");
    displayList(list);

    free(arbolList);

    return 0;
}