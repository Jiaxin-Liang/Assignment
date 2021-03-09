#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "data/neillsimplescreen.h"
#define WIDTH 80
#define HEIGHT 30
#define L (G*10)
#define G 250
#define prob_L (1/(double)L)
#define prob_G (1/(double)G)
#define GENERATIONS 1000
/* #define NDEBUG */
enum bool{false,true};
typedef enum bool bool;

void old2new(char oldcell[HEIGHT][WIDTH],char newcell[HEIGHT][WIDTH]);
char generate(char oldvalues,bool growFlag,bool fireFlag,bool ltnFlag);
void new2old(char oldcell[HEIGHT][WIDTH],char newcell[HEIGHT][WIDTH]);
bool growTrees(void);
bool isNearfire(int ROWS, int COlS, char cell[HEIGHT][WIDTH]);
bool inBoundary(int i,int j);
bool ltnStrike(void);
void display(char oldcell[HEIGHT][WIDTH]);
void test(void);


int main(void)
{
    char cell1[HEIGHT][WIDTH];
    char cell2[HEIGHT][WIDTH];
    int t,x,y;
    /* test(); */
    neillclrscrn();
    srand(time(NULL));/* Ensure the random sets are different everytime we run the program. */
    for (y = 0; y < HEIGHT; y++) {/* Start with all the grids being space. */
        for (x = 0; x < WIDTH; x++) {
            cell1[y][x] = ' ';
            cell2[y][x] = ' ';
        }
    }
    for(t = 0; t< GENERATIONS; t++) {
        neillcursorhome();
        printf("\n------------------------------");
        printf("The %4d generation",t+1);
        printf("-------------------------------\n");
        display(cell1);
        old2new(cell1,cell2);
        new2old(cell1,cell2);
    }
    return 0;
}

/* print out trees in green as @, fire in red as *, and use a black background*/
void display(char oldcell[HEIGHT][WIDTH])
{
    int x,y;
    neillbgcol(black);
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            switch (oldcell[y][x]) {
                case'@':
                    neillfgcol(green);
                    break;
                case'*':
                    neillfgcol(red);
                    break;
                default:
                    neillfgcol(white);
            }
            printf("%c",oldcell[y][x]);
        }
        printf("\n");
    }
    neillbusywait(0.1);
    neillfgcol(white);/* Return colours to normal */
}


/* Create new generations depending on oldvalues of each grid */
void old2new(char oldcell[HEIGHT][WIDTH],char newcell[HEIGHT][WIDTH])
{
    int x,y;
    bool growFlag,fireFlag,ltnFlag;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            growFlag = growTrees();
            fireFlag = isNearfire(y,x,oldcell);
            ltnFlag = ltnStrike();
            newcell[y][x]=generate(oldcell[y][x],growFlag,fireFlag,ltnFlag);
        }
    }
}


/* check the status of each grid, generate new values and store in the new array */
char generate(char oldvalues,bool growFlag,bool fireFlag,bool ltnFlag)
{
    if(oldvalues=='*'){
        return ' ';
    }
    else if(oldvalues==' '&&growFlag){
        return '@';
    }
    else if(oldvalues=='@'&&(fireFlag||ltnFlag)){
        return '*';
    }
    else{
        return oldvalues;
    }
}


/* store the values of new generation in oldcells, to get prepared for the next generation. */
void new2old(char oldcell[HEIGHT][WIDTH],char newcell[HEIGHT][WIDTH])
{
    int x,y;
    for (y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++){
            oldcell[y][x] = newcell[y][x];
        }
    }
}


/* It is from a lecture. */
bool growTrees(void)
{
    if (((double)rand()/(double)RAND_MAX)<prob_G){
        return true;
    }
    return false;
}


bool isNearfire(int ROWS, int COlS, char cell[HEIGHT][WIDTH])
{
    int i,j,d;
    int directions[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    for(d=0;d<8;d++) {
        i = ROWS + directions[d][0];
        j = COlS + directions[d][1];
        if (inBoundary(i, j) && cell[i][j] == '*') {
            return true;
        }
    }
    return false;
}


bool inBoundary(int i,int j)
{
    if(i>=0 && i<HEIGHT && j>=0 && j<WIDTH){
        return true;
    }
    return  false;
}


/* It is from a lecture. */
bool ltnStrike(void)
{
    if (((double)rand()/(double)RAND_MAX)<prob_L){
        return true;
    }
    return false;
}


void test()
{
    /* Change the defined WIDTH and HEIGHT to small number i.e. 5*5 while testing */
    /* Initialize sample array grid1 with all trees */
    char grid1[HEIGHT][WIDTH];
    char grid2[HEIGHT][WIDTH];
    int i,j,k;
    int cnt_g=0,cnt_l=0;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            grid1[i][j]='@';
        }
    }
    grid1[2][2]='*';

    /* ------ test isNearfire ------ */
    assert(isNearfire(1,1,grid1));
    assert(isNearfire(1,2,grid1));
    assert(isNearfire(1,3,grid1));
    assert(isNearfire(2,1,grid1));
    assert(isNearfire(2,3,grid1));
    assert(isNearfire(3,1,grid1));
    assert(isNearfire(3,2,grid1));
    assert(isNearfire(3,3,grid1));
    assert(!isNearfire(0,2,grid1));
    assert(!isNearfire(0,3,grid1));
    assert(!isNearfire(0,4,grid1));
    assert(!isNearfire(1,0,grid1));
    assert(!isNearfire(1,4,grid1));
    assert(!isNearfire(3,0,grid1));
    assert(!isNearfire(3,4,grid1));
    assert(!isNearfire(4,0,grid1));
    assert(!isNearfire(4,1,grid1));
    assert(!isNearfire(4,2,grid1));


   /* ------ test inBoundary ------*/
    assert(inBoundary(0,1));
    assert(inBoundary(29,1));
    assert(inBoundary(15,40));
    assert(inBoundary(1,0));
    assert(inBoundary(1,79));
    assert(!inBoundary(-1,0));
    assert(!inBoundary(0,-1));
    assert(!inBoundary(30,0));
    assert(!inBoundary(0,80));


   /* ------ test growTrees ------ */
    for(k=0;k<100000;k++){
        if(growTrees()==true){
            cnt_g++;
        }
    }
    assert(fabs(((double)cnt_g/100000-prob_G))<1e-1);
    assert(fabs(((double)cnt_g/100000-prob_G))<1e-2);
    assert(fabs(((double)cnt_g/100000-prob_G))<1e-3);


   /* ------ test ltnStrike ------ */
    for(k=0;k<100000;k++){
        if(ltnStrike()==true){
            cnt_l++;
        }
    }
    assert(fabs(((double)cnt_g/100000-prob_G))<1e-1);
    assert(fabs(((double)cnt_g/100000-prob_G))<1e-2);
    assert(fabs(((double)cnt_g/100000-prob_G))<1e-3);


    /* ------ test generate ------ */
    assert(generate('*',false,false,false)==' ');
    assert(generate('*',false,false,true)==' ');
    assert(generate('*',false,true,false)==' ');
    assert(generate('*',false,true,true)==' ');
    assert(generate('*',true,false,false)==' ');
    assert(generate('*',true,false,true)==' ');
    assert(generate('*',true,true,false)==' ');
    assert(generate('*',true,true,true)==' ');
    assert(generate(' ',true,false,false)=='@');
    assert(generate(' ',true,true,false)=='@');
    assert(generate(' ',true,false,true)=='@');
    assert(generate(' ',true,true,true)=='@');
    assert(generate(' ',false,false,false)==' ');
    assert(generate(' ',false,false,true)==' ');
    assert(generate(' ',false,true,false)==' ');
    assert(generate(' ',false,true,true)==' ');
    assert(generate('@',false,false,false)=='@');
    assert(generate('@',false,false,true)=='*');
    assert(generate('@',false,true,false)=='*');
    assert(generate('@',false,true,true)=='*');
    assert(generate('@',true,false,false)=='@');
    assert(generate('@',true,false,true)=='*');
    assert(generate('@',true,true,false)=='*');
    assert(generate('@',true,true,true)=='*');


    /* ------ test old2new ------ */
    grid1[2][2]='*';
    old2new(grid1,grid2);
    /* If these inevitable changes are presented in grid2, the assignment from grid1 to grid2 is tested successful.*/
    assert(grid2[2][2]==' ');
    assert(grid2[1][1]=='*');
    assert(grid2[1][2]=='*');
    assert(grid2[1][3]=='*');
    assert(grid2[3][2]=='*');


    /* ------ test new2old ------ */
    new2old(grid1,grid2);
    assert(grid1[0][0]==grid2[0][0]);
    assert(grid1[0][1]==grid2[0][1]);
    assert(grid1[1][0]==grid2[1][0]);
    assert(grid1[1][1]==grid2[1][1]);
    assert(grid1[2][2]==grid2[2][2]);


    /* ------ test display ------ */
    /* If "@" is green, "*" is red, and background is black, aligned as 5*5, pasue with 0.1s, it's tested successful.*/
    display(grid1);
    display(grid2);


}
