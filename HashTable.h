#pragma once

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct HashTable
{
    int length;
    int allocated;
    int* lengths;
    int* allocateds;
    uint64_t* keys;
    void*** entities;
} HashTable;

HashTable HashTable_New(int length);
void HashTable_Expand(HashTable* hashTable, int length);
int HashTable_GetIndex(HashTable* hashTable, uint64_t cell);
void HashTable_Add(HashTable* hashTable, uint64_t cell, void* entity);
void HashTable_Clean(HashTable* hashTable);
uint64_t HashTable_SpatialCellKey(int sizeX, int sizeY, float X, float Y);
void HashTable_Free(HashTable* hashTable);
