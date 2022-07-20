#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "str_lib.h"
#include "my_bclib.h"


void clean_input(char* input){
    char* working = malloc(sizeof(char)*(my_strlen(input)+5));
    int walk = 0;
    int work = 0;
    while(*(input+walk) != '\0'){
        if(*(input+walk) != ' '){
            *(working+work) = *(input+walk);
            work++;
        }
        walk++;
    }
    *(working+work) = '\0';
    my_strcpy(input, working);
    free(working);
}

int number_of_symbols(char* input){
    int walk = 0;
    int count = 0;
    while(*(input+walk) != '\0'){
        for(int i = 0; i < SYM_LEN; i++){
            if(*(input+walk) == SYMBOLS[i]){
                count++;
            }
        }
        walk++;
    }
    return count;
}

//used for quick proofreading
int char_type (char in){
    if(in == '('){
        return 2;
    }
    if(in == ')'){
        return 3;
    }
    if(in >= '0' && in <= '9'){
        return 0;
    }
    for(int i = 0; i < SYM_LEN; i++){
        if(in == SYMBOLS[i]){
            return 1;
        }
    }
    if(in == '\0'){
        return 10;
    }
    return -1;
}

bool validate_input(char* input){
    int walk = 0;
    int brackets = 0;
    int last = -10;
    while(*(input+walk) != '\0'){
        int sym = char_type(*(input+walk));
        if(sym == -1){
            printf("Invalid character found!\n");
            return false;
        }
        if(sym == 2){
            brackets++; 
        }
        if(sym == 3){
            brackets--;
        }
        if(brackets < 0){
            printf("Bracket error!\n");
            return false;
        }
        if(sym == 1 && last == 1 && *(input+walk) != '-'){ //two symbols next to each other
            printf("Invalid syntax!\n");
            return false;
        }
        if(sym == 3 && last == 2){ //empty brackets
            printf("Invalid syntax!\n");
            return false;
        }
        last = sym;
        walk++;
    }
    if(brackets != 0){
        printf("Bracket error!\n");
        return false;
    }
    return true;
}

queue* add_queue_item(queue* head, queue* item){
    queue* working = head;
    if(head==NULL){
        head = item;
    } else {
        while (working->next != NULL){
            working = working->next;
        }
        working->next = item;
    }
    return head;
}

void print_queue(queue* head){
    int i = 0;
    while (head != NULL){
        if(head->is_number){
            printf("%d ", head->num);
        } else {
            printf("%c ", head->token);
        }
        head = head->next;
        i++;
    }
    printf("\n");
}

int symcount(char sym){
    int i = 0;
    while(i < SYM_LEN){
        if(SYMBOLS[i] == sym){
            break;
        }
        i++;
    }
    return i;
}

bool priority_check(char sym, stack* against){
    if(against != NULL){
        if(symcount(against->token) <= symcount(sym)){
            return true;
        }
    }
    return false;
}

stack* pop_stack(stack* item){
    stack* out = item->prev;
    free(item);
    return out;
}

stack* pop_and_queue(stack* tail, queue* head){
    queue* new = malloc(sizeof(queue));
    char token = tail->token;
    new->is_number = false;
    new->token = token;
    new->next = NULL;
    add_queue_item(head, new);
    tail = pop_stack(tail);
    return tail;
}

void free_queue(queue* head){
    while(head != NULL){
        queue* hold = head;
        head = head->next;
        free(hold);
    }
}

stack* add_to_stack(stack* tail, int num){
    stack* newstack = malloc(sizeof(stack));
    newstack->prev = NULL;
    newstack->num = num;
    newstack->prev = tail;
    return newstack;
}

int symbolmath(int a, int b, char sym){
    //*/%+-
    switch(sym){
        case '*':
            return a*b;
        break;
        case '/':
            return a/b;
        break;
        case '%':
            return a%b;
        break;
        case '+':
            return a+b;
        break;
        case '-':
            return a-b;
        break;
    }
    return 0;
}
