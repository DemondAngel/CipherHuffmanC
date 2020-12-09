#include "Utils.h"
#include "Cipher.h"
int main(){
    char cadena[100];
    int i = 0;
    char * nuevaCadena;

    gets(cadena);
    
    nuevaCadena = pop(cadena, 3);

    printf("\nLa nueva Cadena es:%s\n", nuevaCadena);

    return 0;
}