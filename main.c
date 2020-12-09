#include <locale.h>
#include "Utils.h"
#include "Cipher.h"

int main(){
    setlocale(LC_CTYPE, "");
    char fileName[100];
    wchar_t * message;

    printf("Porfavor escriba el nombre de su archivo: \n");
    printf("Please write your file name: \n");

    gets(fileName);

    message = readFile(fileName);

    message = formatText(message);

    char * msg = wcstringToString(message);

    printf("\nLa palabra sin wide es: %s\n", msg);
    
    return 0;
}