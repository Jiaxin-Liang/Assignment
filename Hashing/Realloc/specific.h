
#define HASHTYPE "Realloc"
#define FIXEDSIZE 17
#define SCALEFACTOR 2

struct dataframe {
    void* key;
    void* data;
};
typedef struct dataframe dataframe;

struct assoc {
/* Underlying array */
    dataframe* hashTable;
    int keySize;
    unsigned int size;
    unsigned int capacity;
};
typedef struct assoc assoc;



