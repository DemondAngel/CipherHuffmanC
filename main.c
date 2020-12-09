#include <locale.h>
#include <windows.h>
#include "Utils.h"
#include "Cipher.h"

int main(){

    setlocale(LC_ALL, "spanish"); 
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    /*
    char fileName[100];
    char * message;
    printf("Porfavor escriba el nombre de su archivo: \n");
    printf("Please write your file name: \n");

    gets(fileName);

    message = readFile(fileName);

    printf("\nYour message is:\n");
    puts(message);
    */
    char cadena[100];
    char * nuevaCadena;
    printf("\nPorfavor inserta una cadena con acentos\n");
    gets(cadena);

    nuevaCadena = formatText(cadena);

    printf("\nLa nueva cadena es: %s\n", nuevaCadena);

    return 0;
}