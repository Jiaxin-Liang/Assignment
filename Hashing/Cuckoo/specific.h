
#define HASHTYPE "Coukoo"
#define FIXEDSIZE 17
#define SCALEFACTOR 2
#define NUM_HASHTABLE 2

struct dataframe {
    void* key;
    void* data;
};
typedef struct dataframe dataframe;

struct assoc {
/* Underlying array */
    dataframe* hashTable[NUM_HASHTABLE];
    int keySize;
    unsigned int size[NUM_HASHTABLE];
    unsigned int capacity;
};
typedef struct assoc assoc;



