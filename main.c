#include "HashTable.h"

#define EntityCount 8

typedef struct Entity
{
    float Left;
    float Right;
    float Top;
    float Bottom;
} Entity;

static void test(HashTable* hashTable, Entity* list)
{
    for(int i = 0; i < EntityCount; i++)
    {
        list[i].Left = rand() % 512;
        list[i].Top = rand() % 512;
        list[i].Right = list[i].Left + 1 + (rand() % 64);
        list[i].Bottom = list[i].Top + 1 + (rand() % 64);
        
        HashTable_Add(hashTable, HashTable_SpatialCellKey(32, 32, list[i].Left, list[i].Top), &list[i]);
    }
}

int main()
{
    HashTable hashTable = HashTable_New(1);
    
    Entity list[EntityCount];
    
    test(&hashTable, list);
    
    HashTable_Clean(&hashTable);
    
    test(&hashTable, list);
    
    HashTable_Clean(&hashTable);
    
    test(&hashTable, list);
    
    for(int i = 0; i < hashTable.length; i++)
    {
        printf("Cell %" PRIu64 "\n", hashTable.keys[i]);
        for(int j = 0; j < hashTable.lengths[i]; j++)
        {
            Entity* entity = (Entity*)hashTable.entities[i][j];
            
            printf("%fx%f\n", entity->Left, entity->Top);
        }
    }
    
    HashTable_Free(&hashTable);
    
    return 0;
}
