#include "../Interp/Stack/stack.h"
#include <math.h>
#define MAXINPUT 100

void assert_output(stack* s, FILE* fp);
int main(int argc, const char* argv[])
{
    FILE* fp;
    char input[MAXINPUT];
    stack* s;
    double d, opd1, opd2;
    s = stack_init();

    if(argc != 2){
        fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fp = nfopen((char*)argv[1], "r");

    while(fgets(input, MAXINPUT, fp) != NULL) {
        /* Use '=' to represent the action of "input terminate" in the sample file */
        if(input[0] == '='){
            assert_output(s,fp);
            s = stack_init();
        }
        /* If variable or number, push */
        else if(sscanf(input, "%lf", &d) == 1) {
            stack_push(s, d);
        }
        else{
            /* Probably an operator ? pop top 2 operands and compute */
            assert(stack_pop(s, &opd2));
            assert(stack_pop(s, &opd1));
            switch (input[0]) {
                case '+' :
                    d = opd1 + opd2;
                    break;
                case '-' :
                    d = opd1 - opd2;
                    break;
                case '*' :
                    d = opd1 * opd2;
                    break;
                case '/' :
                    d = opd1 / opd2;
                    break;
                default:
                    fprintf(stderr, "Can’t understand ? %d\n", input[0]);
                    exit(EXIT_FAILURE);
            }
            /* push the result of operation */
            stack_push(s, d);
        }
    }
    if(stack_peek(s, &d) == true){
        fprintf(stderr, "Stack still had items on it ?\n");
        exit(EXIT_FAILURE);
    }
    stack_free(s);

    return 0;
}

void assert_output(stack* s, FILE* fp)
{
    char output[MAXINPUT];
    double d,res;

    /* Compare the stack result with the sample output*/
    assert(stack_pop(s, &d));
    /* get the output from sample */
    if(fgets(output, MAXINPUT,fp) != NULL){
        if(sscanf(output, "%lf", &res) == 1){
            assert(fabs(d - res) < 1e-15);
        }
    }

    /* Skip an empty line, move to the start of next sample */
    if(fgetc(fp) == 1){
        /* Clear the stack */
        stack_free(s);
    }
}
