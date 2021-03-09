#include "pars-interp.h"

void Main(Interp* t)
{
    if(!strsame(t->pg->wds[t->pg->cw], "{")){
        ERROR("Expecting a { ? ")
    }
    t->pg->cw = t->pg->cw + 1;
    Instrctlst(t);
}

void Instrctlst(Interp* t)
{
    if(strsame(t->pg->wds[t->pg->cw], "}")){
        return;
    }
    Instruction(t);
    t->pg->cw = t->pg->cw + 1;
    Instrctlst(t);
}

void Instruction(Interp* t)
{
    if(strsame(t->pg->wds[t->pg->cw], "FD")){
        Fd(t);
    }
    else if(strsame(t->pg->wds[t->pg->cw], "LT")){
        Lt(t);
    }
    else if(strsame(t->pg->wds[t->pg->cw], "RT")){
        Rt(t);
    }
    else if(strsame(t->pg->wds[t->pg->cw], "DO")){
        Do(t);
    }
    else if(strsame(t->pg->wds[t->pg->cw], "SET")){
        Set(t);
    }
    else {
        ERROR("Couldn’t read your instruction ? ")
    }
}

void Fd(Interp* t)
{
    double fdLength;
    t->pg->cw = t->pg->cw + 1;
    fdLength = Varnum(t);
    if(!t->sw.finished){
        SDL_Delay(MILLISECONDDELAY);
        drawFD(t->sw.renderer, t->pt, fdLength);
        Neill_SDL_UpdateScreen(&t->sw);
        Neill_SDL_Events(&t->sw);
    }
}

void Lt(Interp* t)
{
    double da;
    t->pg->cw = t->pg->cw + 1;
    da = Varnum(t);
    turnLT(t->pt, da);
}

void Rt(Interp* t)
{
    double da;
    t->pg->cw = t->pg->cw + 1;
    da = Varnum(t);
    turnRT(t->pt, da);
}

double Varnum(Interp* t)
{
    varframe* v;
    if(isNum(t->pg->wds[t->pg->cw])){
        return atof(t->pg->wds[t->pg->cw]);
    }
    else if(isVar(t->pg->wds[t->pg->cw])){
        v = Var(t);
        if(v->state == undef){
            ERROR("Use undefined variable ? ")
        }
        return v->data;
    }
    else{
        ERROR("Expecting a number or variable ? ")
    }
}

/* Check if a Var is grammar-valid, then load the pointer to its data-state pair */
varframe* Var(Interp* t)
{
    char* alpha;
    alpha = t->pg->wds[t->pg->cw];
    if(!isVar(alpha)){
        ERROR("Expecting a variable ? ")
    }
    return t->vp[*alpha -'A'];
}

void Do(Interp* t)
{
    int rangeL, rangeR;
    varframe* v;

    /* Define a Variable */
    t->pg->cw = t->pg->cw + 1;
    v = Var(t);
    v->state = def;

    t->pg->cw = t->pg->cw + 1;
    if(!strsame(t->pg->wds[t->pg->cw], "FROM")){
        ERROR("No FROM statement ? ")
    }

    t->pg->cw = t->pg->cw + 1;
    rangeL = Varnum(t);

    t->pg->cw = t->pg->cw + 1;
    if(!strsame(t->pg->wds[t->pg->cw], "TO")){
        ERROR("No TO statement ? ")
    }

    t->pg->cw = t->pg->cw + 1;
    rangeR = Varnum(t);

    t->pg->cw = t->pg->cw + 1;
    if(!strsame(t->pg->wds[t->pg->cw], "{")){
        ERROR("Expecting a { ? ")
    }

    t->pg->cw = t->pg->cw + 1;
    loopDO(t, &v->data, t->pg->cw, rangeL, rangeR);
}

void Set(Interp* t)
{
    double d, p;
    varframe* v;
    t->pg->cw = t->pg->cw + 1;
    v = Var(t);
    v->state = def;

    t->pg->cw = t->pg->cw + 1;
    if(!strsame(t->pg->wds[t->pg->cw], ":=")){
        ERROR("Expecting a := ?")
    }

    t->pg->cw = t->pg->cw + 1;
    Polish(t);
    assert(stack_pop(t->s, &d));

    if(stack_peek(t->s, &p) == true){
        fprintf(stderr, "Stack still had items on it ?\n");
        exit(EXIT_FAILURE);
    }
    v->data = d;
}

void Polish(Interp* t)
{
    double d;
    if(strsame(t->pg->wds[t->pg->cw], ";")){
        return;
    }
    else if(isOp(t->pg->wds[t->pg->cw])){
        Op(t);
        t->pg->cw = t->pg->cw + 1;
        Polish(t);
    }
    else if(Varnum(t) != 0){
        d = Varnum(t);
        stack_push(t->s, d);

        t->pg->cw = t->pg->cw + 1;
        Polish(t);
    }
    else{
        ERROR("Expecting an operator or variable/number ? ")
    }
}

void Op(Interp* t)
{
    double d, opd1, opd2;
    char input;
    input = *t->pg->wds[t->pg->cw];
    assert(stack_pop(t->s, &opd2));
    assert(stack_pop(t->s, &opd1));
    switch(input) {
        case '+' :
            d = opd1 + opd2;
            break;
        case '-' :
            d = opd1 - opd2;
            break;
        case '*' :
            d = opd1 * opd2;
            break;
        case '/' :
            d = opd1 / opd2;
            break;
        default:
            fprintf(stderr, "Can’t understand ? %d\n", input);
            exit(EXIT_FAILURE);
    }
    stack_push(t->s, d);
}

void loopDO(Interp* t, double* loopVar, int loopStart, double rangeL, double rangeR)
{
    int i;
    if(rangeL <= rangeR){
        for(i = rangeL; i <= rangeR; i++){
            /* record the starting position of the loop */
            *loopVar = i;
            t->pg->cw = loopStart;
            Instrctlst(t);
        }
    }
    else{
        for(i = rangeL; i >= rangeR; i--){
            *loopVar = i;
            t->pg->cw = loopStart;
            Instrctlst(t);
        }
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

/* Assume only capital letter is valid variable representation */
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


