#ifndef LIB_BC_H
#define LIB_BC_H

    #define SYMBOLS "*/%+-\0" //PEMDAS order
    #define SYM_LEN 5 //size of above symbols string

    typedef struct stack_s {
        char token;
        int num;
        bool is_number;
        struct stack_s* prev;
    } stack;

    typedef struct queue_s {
        char token;
        int num;
        bool is_number;
        struct queue_s* next;
    } queue;

    void clean_input(char* input);
    int number_of_symbols(char* input);
    int char_type (char in);
    bool validate_input(char* input);
    queue* add_queue_item(queue* head, queue* item);
    void print_queue(queue* head);
    bool priority_check(char sym, stack* against);
    stack* pop_stack(stack* item);
    void free_queue(queue* head);
    stack* pop_and_queue(stack* tail, queue* head);
    stack* add_to_stack(stack* tail, int num);
    int symbolmath(int a, int b, char sym);

#endif