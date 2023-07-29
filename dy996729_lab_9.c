#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};//end RecordType

// Fill out this structure
struct HashType
{
    struct RecordType* ptr;
};//end HashType

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize;
}//end hash

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;

    *ppData = NULL;
    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }//end if

        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);
            pRecord->next = NULL;
        }//end for

        fclose(inFile);
    }//end if
    return dataSz;
}//end parseData

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords: \n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\n%d %c %d", pData[i].id, pData[i].name, pData[i].order);
    }
    printf(" \n");
}//end printRecords

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....

void insertRecord(struct HashType hashTable[], struct RecordType record, int tableSize)
{
    // call the hash function to get the index
    int index = hash(record.id, tableSize);

    // if the RecordType at that index is NULL
    if (hashTable[index].ptr == NULL)
    {
        // set 'record' equal to the HashType pointer in the table at index
        hashTable[index].ptr = &record;
    }//end if
    else
    {
        // else traverse to the end of the linkedlist and add 'record' to the end of it
        struct RecordType* curr = hashTable[index].ptr;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }//end while
        curr->next = &record;
    }//end else
}//end insertRecord

void displayRecordsInHash(struct HashType hashTable[], int tableSize)
{
    for (int i = 0; i < tableSize; ++i)
    {
        // if index is occupied with any records, print all
        if (hashTable[i].ptr != NULL)
        {
            printf("Index %d -> ", i);
            struct RecordType* curr = hashTable[i].ptr;
            while (curr != NULL)
            {
                printf("%d %c %d -> ", curr->id, curr->name, curr->order);
                curr = curr->next;
            }//end while
            printf("NULL\n");
        }//end if
    }//end for
}//end displayRecordsInHash

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation
    // Initialize the hash table
    int hashTableSize = 10;
    struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));// Insert records into the hash table
    for (int i = 0; i < recordSz; ++i){
    insertRecord(hashTable, *(pRecords + i), hashTableSize);
    }//end for
    
    // Display records in the hash table
    displayRecordsInHash(hashTable, hashTableSize);
    
    // Free memory
    free(pRecords);
    free(hashTable);
    return 0;
}//end main