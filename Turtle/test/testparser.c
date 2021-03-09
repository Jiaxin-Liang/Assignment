#include "../Parser/parser.h"

/* File -> string */
int main(int argc, const char* argv[])
{
    Program* prog;
    test();
    prog = prog_init();
    if(argc != 2){
        fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    prog_add(argv[1],prog);
    Main(prog);
    prog_free(prog);
    return 0;
}
