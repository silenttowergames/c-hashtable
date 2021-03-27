#include "HashTable.h"

#define EntityCount 8
#define CellSize 400

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
        
        // NOTE: This method of assignment is overly basic!
        // It assigns an entity to a cell based on its top-left position
        // It may be physically present in other cells, though this code will not place it in those cells
        HashTable_Add(hashTable, HashTable_SpatialCellKey(CellSize, CellSize, list[i].Left, list[i].Top), &list[i]);
    }
}

int main()
{
    HashTable hashTable = HashTable_New(1);
    
    Entity list[EntityCount];
    
    test(&hashTable, list);
    
    uint64_t cell = HashTable_SpatialCellKey(CellSize, CellSize, list[2].Left, list[2].Top);
    int cellIndex = HashTable_GetIndex(&hashTable, cell);
    int entityIndex = HashTable_Cell_GetIndex(&hashTable, cellIndex, &list[2]);
    
    printf("Index of %u (cell %" PRIu64 "): %d\n", &list[2], cell, entityIndex);
    
    for(int i = 0; i < hashTable.length; i++)
    {
        printf("Cell %" PRIu64 "\n", hashTable.keys[i]);
        for(int j = 0; j < hashTable.lengths[i]; j++)
        {
            Entity* entity = (Entity*)hashTable.entities[i][j];
            
            printf("%u: %fx%f\n", entity, entity->Left, entity->Top);
        }
    }
    
    HashTable_Free(&hashTable);
    
    return 0;
}
