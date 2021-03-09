#include "../../Parser/parser.h"
#include "minunit.h"
/* PS: It cannot run for now :-( */
static char * test_main();
int main(int argc, const char* argv[])
{
   int tests_run = 0;
    Program *p;
    FILE* fp;
    test();

    fp = nfopen((char*)filename, "r");
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(fp){
        while(fscanf(fp, "%s", p->wds[p->numTk++])==1){
            if(p->numTk >= p->maxnumTk){
                p->wds = (char**) n2drecalloc((void**)p->wds, p->maxnumTk, SCALEFACTOR * p->maxnumTk,
                                              FIXEDTOKENSIZE, FIXEDTOKENSIZE, sizeof(char));
                p->maxnumTk = p->maxnumTk * SCALEFACTOR;
            }
        }
    }
    fclose(fp);


    Main(prog);
    /* Skip an empty line, move to the start of next sample */
    if(fgetc(fp) == 1){
        /* Clear the prog table */
        prog_free(prog);
    }


    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);


    return result != 0;
}


static char * test_main() {
    mu_assert("error, Expecting a { ? ", p->wds[0] == "{");
    return 0;
}

static char * all_tests() {
    mu_run_test(test_main);
    return 0;
}