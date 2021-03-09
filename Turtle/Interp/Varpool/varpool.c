#include "varpool.h"

varframe** varPool_init(void)
{
    int i;
    varframe** vp;
    vp = (varframe**) ncalloc(NUMALPHA, sizeof(varframe*));
    for(i = 0; i < NUMALPHA; i++){
        vp[i] = (varframe*) ncalloc(1, sizeof(varframe));
        /* Assume all vars are undefined initially, and using undef-var is illegal */
        vp[i]->state = undef;
    }
    return vp;
}

void varPool_free(varframe** vp)
{
    n2dfree((void**)vp, NUMALPHA);
}