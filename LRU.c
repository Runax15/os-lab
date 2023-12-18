#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

typedef struct
{
    int pageNo;
    int lastUsed;
} Page;

void initializeMemory(Page *memory, int numFrames)
{
    for (int i = 0; i < numFrames; ++i)
    {
        memory[i].pageNo = -1; // -1 indicates an empty frame
        memory[i].lastUsed = 0;
    }
}

int findEmptyFrame(Page *memory, int numFrames)
{
    for (int i = 0; i < numFrames; ++i)
    {
        if (memory[i].pageNo == -1)
        {
            return i;
        }
    }
    return -1; // No empty frame found
}

int findLRUFrame(Page *memory, int numFrames)
{
    int lruIndex = 0;
    for (int i = 1; i < numFrames; ++i)
    {
        if (memory[i].lastUsed < memory[lruIndex].lastUsed)
        {
            lruIndex = i;
        }
    }
    return lruIndex;
}

void displayMemory(Page *memory, int numFrames)
{
    printf("Memory: ");
    for (int i = 0; i < numFrames; ++i)
    {
        if (memory[i].pageNo == -1)
        {
            printf("[ ] ");
        }
        else
        {
            printf("[%d] ", memory[i].pageNo);
        }
    }
    printf("\n");
}

void simulateLRU(Page *memory, int numFrames, int *pageRequests, int numRequests)
{
    for (int i = 0; i < numRequests; ++i)
    {
        int page = pageRequests[i];

        // Check if the page is already in memory
        int pageInMemory = 0;
        for (int j = 0; j < numFrames; ++j)
        {
            if (memory[j].pageNo == page)
            {
                memory[j].lastUsed = i; // Update last used time
                pageInMemory = 1;
                break;
            }
        }

        if (!pageInMemory)
        {
            int emptyFrameIndex = findEmptyFrame(memory, numFrames);

            if (emptyFrameIndex != -1)
            {
                // If there is an empty frame, use it
                memory[emptyFrameIndex].pageNo = page;
                memory[emptyFrameIndex].lastUsed = i;
            }
            else
            {
                // If there is no empty frame, replace the LRU page
                int lruIndex = findLRUFrame(memory, numFrames);
                memory[lruIndex].pageNo = page;
                memory[lruIndex].lastUsed = i;
            }
        }

        displayMemory(memory, numFrames);
    }
}

int main()
{
    int pageRequests[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numRequests = sizeof(pageRequests) / sizeof(pageRequests[0]);

    Page memory[MAX_FRAMES];
    initializeMemory(memory, MAX_FRAMES);

    printf("Initial State:\n");
    displayMemory(memory, MAX_FRAMES);

    printf("\nSimulating LRU Page Replacement:\n");
    simulateLRU(memory, MAX_FRAMES, pageRequests, numRequests);

    return 0;
}