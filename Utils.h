#ifndef _Utils_
#define  _Utils_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char * formatText(char * word){

    int lenWord = strlen(word), i = 0;
    char vocasl[11] = "AEIOUaeiou";

    for(i = 0; i < lenWord; i++){

        if(word[i] == ' '){
            word[i] = '_';
        }
        else{
            
            if(isascii(word[i]) == 0){
                int charCode = toascii(word[i]);
                
                if(strchr(word, charCode) == NULL){
                    
                    if(charCode == 100 || charCode == 68){
                        charCode = 97;
                    }
                    else if(charCode == 107 || charCode == 75){
                        charCode = 101;
                    }
                    else if(charCode == 111 || charCode == 79){
                        charCode = 105;
                    }
                    else if(charCode == 118 || charCode == 86){
                        charCode = 111;
                    }
                    else if(charCode == 124|| charCode == 92){
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