#include "realloc.h"

Program* prog_init(void)
{
    Program* p = (Program*) ncalloc(1, sizeof(Program));
    p->wds = (char**) n2dcalloc(FIXEDNUMTOKENS, FIXEDTOKENSIZE, sizeof(char));
    p->cw = 0;
    p->numTk = 0;
    p->maxnumTk = FIXEDNUMTOKENS;
    return p;
}

void prog_add(const char* filename,Program* p)
{
    FILE* fp;
    fp = nfopen((char*)filename, "r");
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
}

void prog_free(Program* p)
{
    n2dfree((void**)p->wds,p->numTk);
    free(p);
}


