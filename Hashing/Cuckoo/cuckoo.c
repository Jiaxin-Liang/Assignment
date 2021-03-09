#include "specific.h"
#include "../assoc.h"
#include <math.h>
/* Seed for BKDR Hash, can be 31 131 1313 13131 131313 etc.. */
#define SEED 131
typedef enum bool{false,true} bool;

unsigned int Hash1(assoc* a, void* key);
unsigned int Hash2(assoc* a, void* key);
assoc* assoc_realloc(assoc* old);
int getPrime(assoc* a);
bool isPrime(int n);
bool key_isSame(assoc* a,void* key,unsigned int label,unsigned int index);

assoc* assoc_init(int keysize)
{
    assoc* a;
    if(keysize<0){
        on_error("Invalid key size");
    }
    a = (assoc*) ncalloc(sizeof(assoc), 1);
    a->hashTable[0] = (dataframe*) ncalloc(sizeof(dataframe), FIXEDSIZE);
    a->hashTable[1] = (dataframe*) ncalloc(sizeof(dataframe), FIXEDSIZE);
    a->size[0] = a->size[1] = 0;
    a->capacity = FIXEDSIZE;
    a->keySize = keysize;
    return a;
}

void assoc_insert(assoc** a, void* key, void* data)
{
    unsigned int index, threshold, cntColl, label, i;
    void *oldKey, *oldData, *k, *d;
    k = key, d = data;
    cntColl = 0, label = 0;
    threshold = (unsigned int) log((*a)->capacity)/log(2);

    if(*a == NULL || key == NULL){
        return;
    }
    index = Hash1(*a, key);
    /* Cell of t0 is empty, do the insertion */
    if((*a)->hashTable[label][index].key == NULL) {
        (*a)->hashTable[label][index].key = key;
        (*a)->hashTable[label][index].data = data;
        (*a)->size[label] = (*a)->size[label] + 1;
    }
    else{
    /* Cell of t0 is occupied */
        while ((*a)->hashTable[label][index].key != NULL)
        {   /* Same key existed, update data only */
            if (key_isSame(*a, k, label, index)) {
                (*a)->hashTable[label][index].data = d;
                return;
            }
            /* Collision, kick off the existed key */
            else {
                cntColl++;
                oldKey = (*a)->hashTable[label][index].key;
                oldData = (*a)->hashTable[label][index].data;
                (*a)->hashTable[label][index].key = k;
                (*a)->hashTable[label][index].data = d;
                /* Kicked keys will bounce between hashTable t0 and t1 */
                label = cntColl % NUM_HASHTABLE;
                /* When collision times reaches the threshold, realloc more space */
                for(i = 0; i < NUM_HASHTABLE; i++){
                    if (cntColl >= threshold || (*a)->size[i] >= (*a)->capacity) {
                        *a = assoc_realloc(*a);
                        cntColl = 0;
                    }
                }
                /* Rehash the kicked key */
                k = oldKey;
                d = oldData;
                index = (!label) ? Hash1(*a, k) : Hash2(*a, k);
            }
        }
        /*  Empty cell is found by the latest kicked key */
        (*a)->hashTable[label][index].key = k;
        (*a)->hashTable[label][index].data = d;
        (*a)->size[label] = (*a)->size[label] + 1;
    }
}

unsigned int assoc_count(assoc* a)
{
    unsigned int i, s;
    s = 0;
    if(a == NULL){
        return 0;
    }
    for(i = 0; i < NUM_HASHTABLE; i++){
        s += a->size[i];
    }
    return s;
}

void* assoc_lookup(assoc* a, void* key)
{
    unsigned int index, i;
    if(key == NULL){
        printf("Invalid key\n");
        return NULL;
    }
    if(assoc_count(a) == 0){
        printf("Empty dictionary\n");
        return NULL;
    }
    for(i = 0; i < NUM_HASHTABLE; i++) {
        index = (!i) ? Hash1(a,key) : Hash2(a,key);
        if(a->hashTable[i][index].key != NULL) {
            if (key_isSame(a, key, i, index)) {
                return a->hashTable[i][index].data;
            }
        }
    }
    return NULL;
}

void assoc_free(assoc* a)
{
    int i;
    for(i = 0; i < NUM_HASHTABLE; i++) {
        free(a->hashTable[i]);
    }
    free(a);
}

/*---------------Private Function---------------*/
/* BKDR Hash function */
unsigned int Hash1(assoc* a, void* key)
{
    unsigned int hash = 0;
    char* p=key;
    int i=0;
    while( i++ < a->keySize || (a->keySize==0 && *p!='\0')){
        hash = hash * SEED + (*p++);
    }
    return (hash % a->capacity);
}

/* AP Hash function  */
unsigned int Hash2(assoc* a, void* key)
{
    unsigned int hash = 0;
    char* p=key;
    int i=0;
    while( i++ < a->keySize || (a->keySize==0 && *p!='\0')){
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*p++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*p++) ^ (hash >> 5)));
        }
    }
    return (hash % a->capacity);
}

assoc* assoc_realloc(assoc* old)
{
    unsigned int i,j;
    assoc* new;
    unsigned int newCAP = getPrime(old);
    new = (assoc*) ncalloc(sizeof(assoc), 1);
    new->hashTable[0]= (dataframe*) ncalloc(sizeof(dataframe), newCAP);
    new->hashTable[1]= (dataframe*) ncalloc(sizeof(dataframe), newCAP);
    new->size[0] = new->size[1] = 0;
    new->keySize = old->keySize;
    new->capacity = newCAP;
    /* Rehash */
    for (j = 0; j < NUM_HASHTABLE; j++) {
        for(i = 0; i < old->capacity; i++) {
            if (assoc_count(new) < assoc_count(old)) {
                assoc_insert(&new, old->hashTable[j][i].key, old->hashTable[j][i].data);
            }
        }
    }
    assoc_free(old);
    return new;
}

bool key_isSame(assoc* a, void* key, unsigned int label, unsigned int index)
{
    if(a->keySize == 0){
        if(!strcmp(a->hashTable[label][index].key, key)){
            return true;
        }
    }else{
        if(!memcmp(a->hashTable[label][index].key, key, a->keySize)){
            return true;
        }
    }
    return false;
}

bool isPrime(int n)
{
    int i;
    if(n == 2){
        return true;
    }
    if(n < 2 || n % 2 == 0){
        return false;
    }
    for (i = 3; i * i <= n; i+=2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int getPrime(assoc* a)
{
    int num;
    num = a->capacity * SCALEFACTOR;
    while(!isPrime(num)){
        num++;
    }
    return num;
}
