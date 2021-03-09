#include "specific.h"
#include "../assoc.h"

/* Seed for BKDR Hash, can be 31 131 1313 13131 131313 etc.. */
#define SEED 131
#define LOAD_FACTOR 0.7
typedef enum bool{false,true} bool;

unsigned int Hash_BKDR(assoc* a, void* key);
unsigned int Rehash_linear(assoc* a, unsigned int index);
bool key_isSame(assoc* a, void* key, unsigned int index);
assoc* assoc_realloc(assoc* old);

assoc* assoc_init(int keysize)
{
    assoc* a;
    if(keysize<0){
        on_error("Invalid key size");
    }
    a = (assoc*) ncalloc(sizeof(assoc), 1);
    a->hashTable = (dataframe*) ncalloc(sizeof(dataframe), FIXEDSIZE);
    a->size = 0;
    a->capacity = FIXEDSIZE;
    a->keySize = keysize;
    return a;
}

void assoc_insert(assoc** a, void* key, void* data)
{
    unsigned int index;
    if(*a == NULL || key == NULL){
        return;
    }
    index = Hash_BKDR(*a,key);
    /* Check whether the cell is occupied */
    while((*a)->hashTable[index].key != NULL){
            /* Same key existed, update data only */
        if (key_isSame(*a, key, index)){
            (*a)->hashTable[index].data = data;
            return;
        }
        else{
            /* Collision, rehash it until an empty cell is found */
            index = Rehash_linear(*a,index);
        }
    }
    /* Empty cell is found, insert key/data pair */
    (*a)->hashTable[index].key = key;
    (*a)->hashTable[index].data = data;
    (*a)->size = (*a)->size + 1;
    /* realloc more space when hashTable is too small */
    if((*a)->size >= LOAD_FACTOR * (*a)->capacity){
        *a = assoc_realloc(*a);
    }
}

unsigned int assoc_count(assoc* a)
{
    if(a==NULL){
        return 0;
    }
    return a->size;
}

void* assoc_lookup(assoc* a, void* key)
{
    unsigned int index;
    if(key == NULL){
        printf("Invalid key\n");
        return NULL;
    }
    if(assoc_count(a)==0){
        printf("Empty dictionary\n");
        return NULL;
    }
    index = Hash_BKDR(a,key);
    while(a->hashTable[index].key != NULL){
        if(key_isSame(a, key, index)) {
            return a->hashTable[index].data;
        }else{
            index = Rehash_linear(a,index);
        }
    }
    return NULL;
}

void assoc_free(assoc* a)
{
    free(a->hashTable);
    free(a);
}

/*---------------Private Function---------------*/
unsigned int Hash_BKDR(assoc* a, void* key)
{
    unsigned int hash = 0;
    char* p=key;
    int i=0;
    while( i++ < a->keySize || (a->keySize==0 && *p!='\0')){
        hash = hash * SEED + (*p++);
    }
    return (hash % a->capacity);
}

unsigned int Rehash_linear(assoc* a, unsigned int index)
{
    index += 1;
    return index % a->capacity;
}

bool key_isSame(assoc* a, void* key, unsigned int index)
{
    if(a->keySize == 0){
        if(!strcmp(a->hashTable[index].key, key)){
            return true;
        }
    }
    else{
        if(!memcmp(a->hashTable[index].key, key, a->keySize)){
            return true;
        }
    }
    return false;
}

assoc* assoc_realloc(assoc* old)
{
    unsigned int i;
    assoc* new;
    /* Resize */
    new = (assoc*) ncalloc(sizeof(assoc), 1);
    new->hashTable = (dataframe*) ncalloc(sizeof(dataframe), old->capacity * SCALEFACTOR);
    new->size = 0;
    new->keySize = old->keySize;
    new->capacity = old->capacity * SCALEFACTOR;
    /* Rehash */
    for(i = 0; i < old->capacity; i++) {
        if (new->size < old->size) {
            assoc_insert(&new, old->hashTable[i].key, old->hashTable[i].data);
        }
    }
    assoc_free(old);
    return new;
}
