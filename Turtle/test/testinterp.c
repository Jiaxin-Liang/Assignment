#include "../Interp/pars-interp.h"

int main(int argc, const char* argv[])
{
    Interp *t;
    t = interp_Init();
    test();
    if(argc != 2){
        fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    prog_add(argv[1],t->pg);
    Main(t);
    /* When pressed ESC or killed the SDL window - the only way of escape */
    while (!t->sw.finished) {
        Neill_SDL_Events(&t->sw);
    }
    interp_free(t);
    return 0;
}


