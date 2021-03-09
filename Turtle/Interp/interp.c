#include "interp.h"

Interp* interp_Init(void)
{
    Interp* t = (Interp*) ncalloc(1, sizeof(Interp));
    Neill_SDL_Init(&t->sw);
    t->pg = prog_init();
    t->pt = point_init();
    t->vp = varPool_init();
    t->s = stack_init();

    /* Set draw color to white */
    Neill_SDL_SetDrawColour(&t->sw, 255, 255, 255);
    return t;
}

void interp_free(Interp* t)
{
    stack_free(t->s);
    varPool_free(t->vp);
    free(t->pt);
    prog_free(t->pg);

    SDL_Quit();
    atexit(SDL_Quit);

    free(t);
}