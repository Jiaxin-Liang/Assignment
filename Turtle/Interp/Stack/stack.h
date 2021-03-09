#include "../../General/general.h"
#define STACKTYPE "Linked"

/* Stack -> Implement Reverse Polish calculation */

typedef enum bool{false,true} bool;

typedef struct dataframe {
    double i;
    struct dataframe* next;
} dataframe;

typedef struct stack {
    dataframe* start;
    int size;
} stack;

/* Create an empty stack to  */
stack* stack_init(void);

/* Add element to top when encounter an operand, or
 * Add the result to top after an operation is done */
void stack_push(stack* s, double d);

/* Take two elements from top when encounter an operator */
bool stack_pop(stack* s, double* d);

/* Copy top element into d (but don’t pop it),
 * to check if the stack is empty after all operations are done */
bool stack_peek(stack*s, double* d);

/* Clear all space used */
bool stack_free(stack* s);

/* Make a string version for testing etc. */
void stack_tostring(stack*, char* str);