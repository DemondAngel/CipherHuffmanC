#include <locale.h>
#include "Utils.h"
#include "Cipher.h"

int main(){
    setlocale(LC_CTYPE, "");
    char fileName[100];
    Nodo * arbolList = NULL;
    
    printf("Porfavor escriba el nombre de su archivo: \n");
    printf("Please write your file name: \n");

    gets(fileName);

    arbolList = readFile(fileName, arbolList);

    arbolList = mergeSort(arbolList);
    arbolList = createTree(arbolList);

    printf("\nArbol\n");
    inorder(arbolList);
    
    free(arbolList);

    return 0;
}