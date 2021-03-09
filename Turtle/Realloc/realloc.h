#include "../General/general.h"
#define COLLTYPE "Realloc"
#define FIXEDNUMTOKENS 100
#define FIXEDTOKENSIZE 7
#define SCALEFACTOR 2

struct prog{
    char** wds;
    int cw; /* current word */
    int numTk; /* number of Tokens */
    int maxnumTk;
};
typedef struct prog Program;

/* Create an associative array to store the words of a program */
Program* prog_init(void);

/* Read the program and store in a string array,
 * Realloc new space when the array is too small */
void prog_add(const char* filename, Program* p);

/* Free up the allocated memory */
void prog_free(Program* p);