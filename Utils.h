#ifndef _Utils_
#define  _Utils_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

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

    int len = strlen(bin), i = 0, number = 0;

    for(i = len-1; i > -1; i--){

        number += pow(bin[i]-48, i);
    }

    return number;

}

#endif