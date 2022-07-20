#include <stdio.h>

int my_strlen(char* _string){
    int i = 0;
    while(_string[i] != '\0'){
        i++;
    }
    return i;
}

char* my_strcpy(char *_to, const char* _from){
    char* ret = _to;
    int i = 0;
    while(_from[i] != '\0'){
        _to[i] = _from[i];
        i++;
    }
    _to[i] = '\0';
    return ret;
}

int my_atoi(const char* _name){ //with negative numbers
    int walk = 0;
    int out = 0;
    int negative = 0;
    while(*(_name+walk) != '\0'){
        if(*(_name+walk) >= '0' && *(_name+walk) <= '9'){
            out = (out*10)+(*(_name+walk) - '0');
        } else if(*(_name+walk) == '-'){
            negative = 1;
        }
        walk++;
    }
    if(negative){
        return 0-out;
    }
    return out;
}

int isnumber(char in){
    if(in >= '0' && in <= '9'){
        return 1;
    }
    return 0;
}