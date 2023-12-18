#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3 // Adjust the number of frames as needed

// Function to check if a page is present in the frames
bool isPagePresent(int page, int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the page to be replaced
int findReplacementIndex(int pages[], int frames[], int frameCount, int currentIndex, int pageCount) {
    int farthestIndex = -1;
    int farthestDistance = -1;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex + 1; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthestDistance) {
                    farthestDistance = j;
                    farthestIndex = i;
                }
                break;
            }
        }

        if (j == pageCount) {
            return i; // If a page will not be used in the future, replace it
        }
    }

    return (farthestIndex == -1) ? 0 : farthestIndex;
}

// Function to simulate optimal page replacement
void optimalPageReplacement(int pages[], int pageCount) {
    int frames[MAX_FRAMES];
    int frameCount = 0;
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Initialize frames with -1 (indicating empty)
    }

    for (int i = 0; i < pageCount; i++) {
        if (!isPagePresent(pages[i], frames, frameCount)) {
            if (frameCount < MAX_FRAMES) {
                frames[frameCount++] = pages[i];
            } else {
                int replaceIndex = findReplacementIndex(pages, frames, frameCount, i, pageCount);
                frames[replaceIndex] = pages[i];
            }
            pageFaults++;
        }
    }

    printf("Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 2, 3, 4, 5, 1, 6, 7, 8, 9}; // Sample page reference string
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    optimalPageReplacement(pages, pageCount);

    return 0;
}
