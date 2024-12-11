#include<stdio.h>

void pageReplacementOptimal(int n, int pages[], int capacity) {
    int frames[capacity];
    int pageFaults = 0;

    // Initialize all frame slots as empty
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, replace it
        if (!found) {
            int replaceIndex = -1, farthest = -1;

            // Find the optimal page to replace
            for (int j = 0; j < capacity; j++) {
                int nextUse = -1;

                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }

                if (nextUse == -1) {
                    replaceIndex = j;
                    break;
                } else if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }

            if (replaceIndex == -1) {
                replaceIndex = 0; // Default to the first frame
            }

            frames[replaceIndex] = page;
            pageFaults++;

            // Print step and frame status for a page fault
            printf("Step %d: Page %d caused a page fault. Frames: [", i + 1, page);
            for (int k = 0; k < capacity; k++) {
                if (frames[k] != -1) {
                    printf("%d", frames[k]);
                } else {
                    printf("-");
                }
                if (k < capacity - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        } else {
            // Print step if no page fault occurs
            printf("Step %d: Page %d is already in the frame. No page fault.\n", i + 1, page);
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    pageReplacementOptimal(n, pages, capacity);

    return 0;
}
