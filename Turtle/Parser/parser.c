#include "parser.h"

void Main(Program* p)
{
    if(!strsame(p->wds[p->cw], "{")){
        ERROR("Expecting a { ? ")
    }
    p->cw = p->cw + 1;
    Instrctlst(p);
}

void Instrctlst(Program* p)
{
    if(strsame(p->wds[p->cw], "}")){
        return;
    }
    Instruction(p);
    p->cw = p->cw + 1;
    Instrctlst(p);
}

void Instruction(Program* p)
{
    if(strsame(p->wds[p->cw], "FD")){
        Fd(p);
    }
    else if(strsame(p->wds[p->cw], "LT")){
        Lt(p);
    }
    else if(strsame(p->wds[p->cw], "RT")){
        Rt(p);
    }
    else if(strsame(p->wds[p->cw], "DO")){
        Do(p);
    }
    else if(strsame(p->wds[p->cw], "SET")){
        Set(p);
    }
    else {
        ERROR("Couldn’t read your instruction ? ")
    }
}

void Fd(Program* p)
{
    p->cw = p->cw + 1;
    Varnum(p);
}

void Lt(Program* p)
{
    p->cw = p->cw + 1;
    Varnum(p);
}

void Rt(Program* p)
{
    p->cw = p->cw + 1;
    Varnum(p);
}

void Varnum(Program* p)
{
    if(isNum(p->wds[p->cw])){
        return;
    }
    else if(isVar(p->wds[p->cw])){
        return;
    }
    else{
        ERROR("Expecting a number or variable ? ")
    }
}

void Var(Program* p)
{
    if(!isVar(p->wds[p->cw])){
        ERROR("Expecting a variable ? ")
    }
}

void Do(Program* p)
{
    p->cw = p->cw + 1;
    Var(p);

    p->cw = p->cw + 1;
    if(!strsame(p->wds[p->cw], "FROM")){
        ERROR("No FROM statement ? ")
    }

    p->cw = p->cw + 1;
    Varnum(p);

    p->cw = p->cw + 1;
    if(!strsame(p->wds[p->cw], "TO")){
        ERROR("No TO statement ? ")
    }

    p->cw = p->cw + 1;
    Varnum(p);

    p->cw = p->cw + 1;
    if(!strsame(p->wds[p->cw], "{")){
        ERROR("Expecting a { ? ")
    }

    p->cw = p->cw + 1;
    Instrctlst(p);
}

void Set(Program* p)
{
    p->cw = p->cw + 1;
    Var(p);
    p->cw = p->cw + 1;
    if(!strsame(p->wds[p->cw], ":=")){
        ERROR("Expecting a := ?")
    }
    p->cw = p->cw + 1;
    Polish(p);
}

void Polish(Program* p)
{
    if(strsame(p->wds[p->cw], ";")){
        return;
    }
    else if(isOp(p->wds[p->cw])){
        Op(p);
        p->cw = p->cw + 1;
        Polish(p);
    }
    else if(isNum(p->wds[p->cw]) || isVar(p->wds[p->cw])){
        Varnum(p);
        p->cw = p->cw + 1;
        Polish(p);
    }
    else{
        ERROR("Expecting an operator or variable/number ? ")
    }
}

void Op(Program* p)
{
    if(!isOp(p->wds[p->cw])){
        ERROR("Expecting an operator ? ")
    }
}

/* Assume only positive integers & double floats are grammar-valid */
bool isNum(char* str)
{
    int i = 0;
    bool findPoint = false;

    while(str[i] != '\0') {
        if (isdigit(str[i])) {
            i++;
        }
            /* Check float */
        else if (!findPoint && str[i] == '.') {
            findPoint = true;
            i++;
        }
        else {
            return false;
        }
    }
    return true;
}

bool isOp(char* str)
{
    char c = str[0];
    if(str[1] == '\0'){
        if(c=='+'|| c=='-' || c=='*' || c=='/'){
            return true;
        }
    }
    return false;
}

/* Assume only capital letters are valid variables */
bool isVar(char* str)
{
    if(isupper(str[0]) && !str[1]){
        return true;
    }
    return false;
}

void test_isOp(void)
{
    assert(isOp("+"));
    assert(isOp("*"));
    assert(!isOp("++"));
    assert(!isOp("-*"));
    assert(!isOp("%"));
    assert(!isOp("&"));
    assert(!isOp("("));
    assert(!isOp("}"));
}

void test_isNum(void)
{
    assert(!isNum("a"));
    assert(!isNum("FD"));
    assert(!isNum("1b2"));
    assert(!isNum("}"));
    assert(!isNum("-12"));
    assert(!isNum("1.2.2"));
    assert(isNum("1.2"));
    assert(isNum("20"));
    assert(isNum("0"));
    assert(isNum("1000000"));

}

void test_isVar(void)
{
    assert(!isVar("a"));
    assert(!isVar("c"));
    assert(!isVar("AA"));
    assert(!isVar("ABC"));
    assert(!isVar("A2"));
    assert(!isVar("20"));
    assert(!isVar(";"));
    assert(isVar("A"));
    assert(isVar("M"));
    assert(isVar("Z"));
}

void test(void)
{
    test_isNum();
    test_isVar();
    test_isOp();
}

