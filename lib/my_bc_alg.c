#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "str_lib.h"
#include "my_bclib.h"
#include "my_bc_alg.h"


queue* tokenize_problem(char* input){
    queue* head = NULL;
    bool skip = false;
    int i = 0; 
    int numbufc = 0;
    char c, last;
    char num_buf[12];

    while(*(input+i) != '\0'){
        c = *(input+i);

        //is it a negative number or subtraction?
        if(c == '-'){
            if(last != ')'){
                if(i == 0 || !isnumber(last)){
                    num_buf[numbufc] = c;
                    numbufc++;
                    skip = true;
                }
            }
        }

        if(!skip){
            if(isnumber(c)){
                num_buf[numbufc] = c;
                numbufc++;
                skip = true;
            } else {
                if(numbufc>0){
                    num_buf[numbufc] = '\0';
                    queue* new = malloc(sizeof(queue));
                    new->is_number = true;
                    new->next = NULL;
                    new->num = my_atoi(num_buf);
                    head = add_queue_item(head, new);
                    numbufc = 0;
                    num_buf[numbufc] = '\0';
                }
                queue* new = malloc(sizeof(queue));
                new->is_number = false;
                new->next = NULL;
                new->token = c;
                head = add_queue_item(head, new);
            }
        }
        
        skip = false;
        last = *(input+i);
        i++;
    }
    //get the last number
    if(numbufc>0){
        num_buf[numbufc] = '\0';
        queue* new = malloc(sizeof(queue));
        new->is_number = true;
        new->next = NULL;
        new->num = my_atoi(num_buf);
        head = add_queue_item(head, new);
    }
    return head;
}

queue* convert_rpn(queue* input){ //shunting yard
    queue* out_head = NULL;
    stack* symbol_tail = NULL;
    
    //read input
    while(input != NULL){
        if(input->is_number){
            queue* new = input;
            input = input->next;
            new->next = NULL;
            out_head = add_queue_item(out_head, new);
        } else {
            char sym = input->token;
            stack* newstack = malloc(sizeof(stack));
            newstack->prev = NULL;
            newstack->token = sym;

            if (sym == '('){
                newstack->prev = symbol_tail;
                symbol_tail = newstack;
            } else if (sym == ')'){
                free(newstack);
                while(symbol_tail->token != '('){
                    symbol_tail = pop_and_queue(symbol_tail, out_head);
                }
                symbol_tail = pop_stack(symbol_tail);
            } else {
                if(symbol_tail == NULL){
                    symbol_tail = newstack;
                } else {
                    while(priority_check(sym, symbol_tail)){
                        //pop tail, add to queue
                        symbol_tail = pop_and_queue(symbol_tail, out_head);
                    }
                    //add to stack
                    newstack->prev = symbol_tail;
                    symbol_tail = newstack;
                }
            }
            queue* old = input;
            input = input->next;
            free(old);
        }
    }

    //empty stack
    while(symbol_tail != NULL){
        symbol_tail = pop_and_queue(symbol_tail, out_head);
    }

    return out_head;
}

int do_math(queue* problem){
    int result = 0;
    stack* tail = NULL;
    int left, right;

    while(problem != NULL){
        if(problem->is_number){
            tail = add_to_stack(tail, problem->num);
        } else {
            //pop two, first will be right hand, second will be left
            right = tail->num;
            tail = pop_stack(tail);
            left = tail->num;
            tail = pop_stack(tail);
            //check for devide by zero
            if(right == 0){
                if(problem->token == '/' || problem->token == '%'){
                    printf("Cannot divide by zero!\n");
                    return 0;
                }
            }
            //push result back to stack
            result = symbolmath(left, right, problem->token);
            tail = add_to_stack(tail, result);
        }

        problem = problem->next;
    }

    free(tail);

    return result;
}