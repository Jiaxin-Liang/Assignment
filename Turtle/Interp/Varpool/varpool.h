#include "../../General/general.h"
/* Use variables */

#define NUMALPHA 26
#define NUMSTATE 2
typedef enum defState{undef,def} defState;

typedef struct varframe{
    double data;
    defState state;
} varframe;

varframe** varPool_init(void);
void varPool_free(varframe** vp);

