#ifndef _Utils_
#define  _Utils_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char * wcstringToString(wchar_t * wcs){

    int len = wcslen(wcs), i = 0;
    char * newString = calloc(len, sizeof(char));
    wprintf(L"%ls", wcs);
    sprintf(newString, "%ws", wcs);

    return newString;
}

wchar_t * formatText(wchar_t * word){

    int lenWord = wcslen(word), i = 0;
    char vocals[11] = "AEIOUaeiou";

    
    for(i = 0; i < lenWord; i++){

        if(word[i] == ' '){
            word[i] = '_';
        }
        else{
            
            if(isascii(word[i]) == 0){
                int charCode = toascii(word[i]);
                
                if(wcschr(word, charCode) == NULL){
                    
                    if(word[i] == L'á' ||word[i] == L'ä' || word[i] == L'Á' ||word[i] == L'Ä'){
                        charCode = 97;
                    }
                    else if(word[i] == L'é' ||word[i] == L'ë' || word[i] == L'É' || word[i] == L'Ë'){
                        charCode = 101;
                    }
                    else if(word[i] == L'í' || word[i] == L'ï' || word[i] == L'Í' || word[i] == L'Ï'){
                        charCode = 105;
                    }
                    else if(word[i] == L'ó' ||word[i] == L'ö' || word[i] == L'Ö' || word[i] == L'Ó'){
                        charCode = 111;
                    }
                    else if(word[i] == L'ú' ||word[i] == L'ü' || word[i] == L'Ú' || word[i] == L'Ü'){
                        charCode = 117;
                    }
                }
                word[i] = charCode;
            }
            word[i] = tolower(word[i]);
        }

    }
    
    return word;
}

char * popPosition(char * string, int position){
    
     char * newString;

     int len = strlen(string), i = 0;
     
     string[position] = '\0';

     for(i = position; i < len-1; i++){
         string[i] = string[i+1];
     }
     string[len-1] = '\0';
    
     len = strlen(string);

     newString = calloc(len, sizeof(char));

    for(i = 0;  i< len; i++){
        newString[i] = string[i];
    }

    return newString;

}

#endif