#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

/* The following functions are from Neill */
void on_error(const char* s);
void* ncalloc(int n, size_t size);
void** n2dcalloc(int h, int w, size_t size);
void** n2drecalloc(void** p, int oh, int nh, int ow, int nw, size_t szelem);
void n2dfree(void**p, int h);
void* nfopen(char* fname, char* mode);
