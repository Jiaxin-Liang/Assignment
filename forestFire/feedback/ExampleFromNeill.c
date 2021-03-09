#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../data/neillsimplescreen.h"

#define G 250
#define L (G*10)
#define ROWS 30
#define COLS 80
#define GENERATIONS 1000
#define MARGIN4TEST 100
#define OUTPUTSPEED 0.04

enum state {empty, tree, fire};
typedef enum state state;
enum bool {false, true};
typedef enum bool bool;

/* Testing all other functions */
void test(void);
/* For testing printed arrays */
void stringify_test(state *grid, char *s, int rows, int cols);
/* Initialise the grid to empty */
void initialise(state grid[ROWS][COLS]);
/* Prints the grid in area 80 wide and 30 high */
void print_gen(state grid[ROWS][COLS]);
/* Converts states to chars for printing */
char stringify(state cell);
/* Colourise tree and fire output */
void colourise(char c);
/* Process next generation of grid */
void processgrid(state grid[ROWS][COLS], state nextgrid[ROWS][COLS]);
/* Process next generation of each cell */
state forestfire(state grid[ROWS][COLS], int x, int y);
/* Processes cells which are trees */
state rules4tree(state grid[ROWS][COLS], int y, int x);
/* Returns true if neighbouring cells are on fire */
bool isneighbour_onfire(state grid[ROWS][COLS], int y, int x);
/* Ensures array indexes are within bounds of the grid */
state safe(state grid[ROWS][COLS], int y, int x);
/* Returns a tree for 1 in G times */
state spontgrowth(void);
/* Returns true 1 time in L */
bool islightning(void);
/* Creates copy of existing grid, ready for next loop */
void copyarray(state copyfrom[ROWS][COLS], state copy2[ROWS][COLS]);


int main(void)
{
    int i;
    state grid[ROWS][COLS];
    state next_gen[ROWS][COLS];
    test();
    srand(time(NULL));
    neillclrscrn();
    initialise(grid);
    for(i=0; i<GENERATIONS; i++) {
        neillcursorhome();
        print_gen(grid);
        processgrid(grid, next_gen);
        copyarray(next_gen, grid);
        neillbusywait(OUTPUTSPEED);
    }
    neillfgcol(white);
    return 0;
}

void initialise(state grid[ROWS][COLS])
{
    int i, j;
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            grid[j][i] = empty;
        }
    }
}

void processgrid(state grid[ROWS][COLS], state nextgrid[ROWS][COLS])
{
    int i, j;
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            nextgrid[j][i] = forestfire(grid, j, i);
        }
    }
}

state forestfire(state grid[ROWS][COLS], int y, int x)
{
    switch(grid[y][x]) {
        case fire  :
            return empty;
        case tree  :
            return rules4tree(grid, y, x);
        case empty :
            return spontgrowth();
        default    :
            return empty;
    }
}

state rules4tree(state grid[ROWS][COLS], int y, int x)
{
    if(isneighbour_onfire(grid, y, x) == true) {
        return fire;
    }
    if(islightning() == true) {
        return fire;
    }
    return tree;
}

bool isneighbour_onfire(state grid[ROWS][COLS], int y, int x)
{
    state a;
    int i, j;
    /* Check 8-neighbourhood for fire */
    for(j=-1; j<=1; j++) {
        for(i=-1; i<=1; i++) {
            a = safe(grid, y+j, x+i);
            if(a == fire) {
                return true;
            }
        }
    }
    return false;
}

state safe(state grid[ROWS][COLS], int y, int x)
{
    /* when index out of bounds, return empty */
    if((y < 0) || (y >= ROWS) || (x < 0) || (x >= COLS)) {
        return empty;
    }
    return grid[y][x];
}

bool islightning(void)
{
    /* lightning strikes 1 time in L */
    if((rand() % L) == 1) {
        return true;
    }
    return false;
}

state spontgrowth(void)
{
    /* spontaneous growth 1 time in G */
    if((rand() % G) == 1) {
        return tree;
    }
    return empty;
}

void print_gen(state grid[ROWS][COLS])
{
    int i, j;
    char c;
    for(j=0; j<ROWS; j++) {
        if(j != 0) {
            printf("\n");
        }
        for(i=0; i<COLS; i++) {
            c = stringify(grid[j][i]);
            colourise(c);
            printf("%c", c);
        }
    }
}

char stringify(state cell)
{
    switch(cell) {
        case tree :
            return '@';
        case fire :
            return '*';
        case empty :
            return ' ';
        default :
            return ' ';
    }
}

void colourise(char c)
{
    if(c == '@') {
        neillfgcol(green);
    }
    if(c == '*') {
        neillfgcol(red);
    }
}

void copyarray(state copyfrom[ROWS][COLS], state copy2[ROWS][COLS])
{
    int j, i;
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            copy2[j][i] = copyfrom[j][i];
        }
    }
}

void test(void)
{
    int i, j;
    int lightning_cnt, not_lightning;
    int spont_growth, not_growth;
    state new_state1, new_state2, new_state3;
    state s1[ROWS][COLS]; /* For testing empty cells */
    /* Non-empty grid to test initialisation */
    state s2[ROWS][COLS] = {{fire, fire, fire},\
                           {fire, fire, fire}};
    state s3[ROWS][COLS]; /* For testing trees */
    state s4[ROWS][COLS]; /* For testing tree neighbourhood rule */
    /* For testing forestfire */
    state s5[ROWS][COLS] = {{empty, fire, tree},\
                           {empty, fire, tree},\
                           {empty, tree, tree}};
    state s6[ROWS][COLS]; /* For testing fire */
    /* For testing printing */
    state s7[3][3] = {{fire, empty, tree},\
                     {fire, empty, tree},\
                     {fire, empty, tree}};
    /* For testing processgrid */
    state s8[ROWS][COLS];
    state s9[ROWS][COLS];
    state s10[ROWS][COLS];
    state s11[ROWS][COLS];
    state s12[ROWS][COLS];
    state s13[ROWS][COLS];
    /* For testing copyarray */
    state s14[ROWS][COLS];
    state s15[ROWS][COLS];
    state s16[ROWS][COLS];
    char ns1[10]; /* For testing stringify */
    char ns2[10]; /* For testing stringify */

    /* Test initialisiation */
    initialise(s1);
    initialise(s2);
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            assert(s1[j][i]==empty);
            assert(s2[j][i]==empty);
        }
    }
    /* Test safe method */
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            s3[j][i] = tree;
            /* index within array bounds and should return tree */
            assert(safe(s3, j,      i     )==tree);
            /* indexes out of bounds, should return empty */
            assert(safe(s3, j+ROWS, i+COLS)==empty);
        }
    }
    /* Test isneighbour_onfire */
    /* Creating a single fire sourrounded by trees */
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            s4[j][i] = tree;
        }
    }
    s4[1][1] = fire;
    assert(isneighbour_onfire(s4, 0, 0)==true);
    assert(isneighbour_onfire(s4, 0, 1)==true);
    assert(isneighbour_onfire(s4, 0, 2)==true);
    assert(isneighbour_onfire(s4, 1, 0)==true);
    assert(isneighbour_onfire(s4, 1, 2)==true);
    assert(isneighbour_onfire(s4, 2, 0)==true);
    assert(isneighbour_onfire(s4, 2, 1)==true);
    assert(isneighbour_onfire(s4, 2, 2)==true);
    assert(isneighbour_onfire(s4, 3, 0)==false);
    assert(isneighbour_onfire(s4, 1, 3)==false);
    assert(isneighbour_onfire(s4, 2, 3)==false);

    /* Test rules4tree method */
    /* Ensure trees turn to fire on next generation */
    assert(rules4tree(s4, 0, 0)==fire);
    assert(rules4tree(s4, 0, 1)==fire);
    assert(rules4tree(s4, 0, 2)==fire);
    assert(rules4tree(s4, 1, 0)==fire);
    assert(rules4tree(s4, 1, 2)==fire);
    assert(rules4tree(s4, 2, 0)==fire);
    assert(rules4tree(s4, 2, 1)==fire);
    assert(rules4tree(s4, 2, 2)==fire);
    s4[1][1] = tree;
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            new_state1 = rules4tree(s4, j, i);
            assert((new_state1==tree) || (new_state1==fire));
        }
    }
    /* Test lightning strike */
    lightning_cnt = 0; not_lightning = 0;
    for(i=0; i<L*MARGIN4TEST; i++) {
        if(islightning() == true) {
            lightning_cnt++;
        }
        else {
            not_lightning++;
        }
    }
    assert(lightning_cnt>0);
    assert(not_lightning>0); assert(not_lightning<(L*MARGIN4TEST));

    /* Test spontaneous growth */
    spont_growth = 0; not_growth = 0;
    for(i=0; i<G*MARGIN4TEST; i++) {
        if(spontgrowth()==tree) {
            spont_growth++;
        }
        else {
            not_growth++;
        }
    }
    assert(spont_growth>0);
    assert(not_growth>0); assert(not_growth<(G*MARGIN4TEST));

    /* Test forestfire */
    assert(forestfire(s5,0,2)==fire); /* tree -> fire (8-neighbourhood) */
    initialise(s1);
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            s6[j][i] = fire;
            /* fire -> empty */
            new_state1 = forestfire(s6,j,i);
            assert(new_state1==empty);
            /* Tree -> tree || fire */
            new_state2 = forestfire(s3,j,i);
            assert((new_state2==tree)  || (new_state2==fire));
            /* Empty -> tree || empty */
            new_state3 = forestfire(s1,j,i);
            assert((new_state3==empty) || (new_state3==tree));
        }
    }

    /* Test stringify */
    assert(stringify(empty)==' ');
    assert(stringify(fire)=='*');
    assert(stringify(tree)=='@');
    stringify_test(&s1[0][0], &ns1[0], 3, 3);
    stringify_test(&s7[0][0], &ns2[0], 3, 3);
    assert(strcmp(ns1, "         ")==0);
    assert(strcmp(ns2, "* @* @* @")==0);

    /* Test processgrid */
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            (s8 [j][i]=fire);
            (s9 [j][i]=empty);
            (s10[j][i]=tree);
        }
    }
    processgrid(s8, s11);
    processgrid(s9, s12);
    processgrid(s10,s13);
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            assert( s11[j][i]==empty);
            assert((s12[j][i]==empty) || (s12[j][i]==tree));
            assert((s13[j][i]==tree)  || (s13[j][i]==fire));
        }
    }
    /* Test copy array */
    copyarray(s8, s14);
    copyarray(s9, s15);
    copyarray(s10, s16);
    for(j=0; j<ROWS; j++) {
        for(i=0; i<COLS; i++) {
            assert(s14[j][i]==fire);
            assert(s15[j][i]==empty);
            assert(s16[j][i]==tree);
        }
    }
}

void stringify_test(state *grid, char *s, int rows, int cols)
{
    int i;
    for(i=0; i<rows*cols; i++) {
        s[i] = stringify(grid[i]);
    }
    s[i] = '\0';
}
