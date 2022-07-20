#ifndef LIB_BC_ALG_H
#define LIB_BC_ALG_H

    queue* tokenize_problem(char* input);
    queue* convert_rpn(queue* input);
    int do_math(queue* problem);

#endif