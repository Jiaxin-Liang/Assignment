#include "interp.h"
/* Advanced Parser with Interpreter */

#define strsame(A,B) (strcmp(A, B)==0)
#define ERROR(PHRASE) {fprintf(stderr,\
"Fatal Error %s occured in %s, line %d\n",\
PHRASE, __FILE__, __LINE__); exit(2); }
#define MILLISECONDDELAY 10

void Main(Interp* t);
void Instrctlst(Interp* t);
void Instruction(Interp* t);
void Fd(Interp* t);
void Rt(Interp* t);
void Lt(Interp* t);

double Varnum(Interp* t);
varframe* Var(Interp* t);

void Do(Interp* t);
void loopDO(Interp* t, double* loopVar, int loopStart, double rangeL, double rangeR);

void Set(Interp* t);
void Polish(Interp* t);
void Op(Interp* t);

bool isNum(char* str);
bool isVar(char* str);
bool isOp(char* str);

void test_isOp(void);
void test_isNum(void);
void test_isVar(void);
void test(void);

