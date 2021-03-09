#include "../Realloc/realloc.h"
#include "Point/point.h"
#include "Varpool/varpool.h"
#include "Stack/stack.h"

typedef struct Interp{
    Program* pg;
    SDL_Simplewin sw;
    point* pt;
    varframe** vp;
    stack* s;
} Interp;

Interp* interp_Init(void);
void interp_free(Interp* i);
