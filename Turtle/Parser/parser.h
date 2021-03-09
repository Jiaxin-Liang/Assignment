#include "../General/general.h"
#include "../Realloc/realloc.h"

typedef enum bool{false,true} bool;

#define strsame(A,B) (strcmp(A, B)==0)
#define ERROR(PHRASE) {fprintf(stderr,\
"Fatal Error %s occured in %s, line %d\n",\
PHRASE, __FILE__, __LINE__); exit(2); }

void Main(Program* p);
void Instrctlst(Program* p);
void Instruction(Program* p);
void Fd(Program* p);
void Rt(Program* p);
void Lt(Program* p);
void Varnum(Program* p);
void Var(Program* p);
void Do(Program* p);
void Set(Program* p);
void Polish(Program* p);
void Op(Program* p);

bool isNum(char* str);
bool isVar(char* str);
bool isOp(char* str);

void test_isOp(void);
void test_isNum(void);
void test_isVar(void);
void test(void);