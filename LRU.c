#include<stdio.h>

void pageReplacementLRU(int n, int pages[], int capacity) {
    int frames[capacity];
    int recent[capacity];
    int pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            int leastRecent = recent[0];

            for (int j = 1; j < capacity; j++) {
                if (recent[j] < leastRecent) {
                    leastRecent = recent[j];
                    lruIndex = j;
                }
            }

            frames[lruIndex] = page;
            recent[lruIndex] = i;
            pageFaults++;

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

    pageReplacementLRU(n, pages, capacity);

    return 0;
}
