#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "lib/str_lib.h"
#include "lib/my_bclib.h"
#include "lib/my_bc_alg.h"

int main(int ARGC, char** ARGV){
    int result = 0;
    if(ARGC < 2){
        printf("Please provide a math problem for my_bc to solve.\n");
        return 1;
    }

    char* problem = malloc(sizeof(char)*(my_strlen(ARGV[1])+1));
    my_strcpy(problem, ARGV[1]);

    //take out any pesky spaces
    clean_input(problem);

    if(validate_input(problem)){

        //if there is no math, it's just a number
        int symbols = number_of_symbols(problem);
        if(symbols <= 1){
            if(*problem == '-' || symbols == 0){
                result = my_atoi(problem);
                printf("Result: %d\n", result);
                free(problem);
                return result;
            }
        }

        //convert to tokens
        queue* tokenlist = tokenize_problem(problem);

        //shunting yard into RPN
        queue* problem_rpn = convert_rpn(tokenlist);

        //do the math
        result = do_math(problem_rpn);

        printf("Result: %d\n", result);

        free_queue(problem_rpn);
    }

    free(problem);
    return result;
}