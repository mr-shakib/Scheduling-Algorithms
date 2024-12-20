#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int front = 0;
    int count = 0;
    int pageFaults = 0;

    // Initialize all frame slots as empty
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
    }

    printf("\nPage Replacement Process:\n");
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

        // If the page is not found in frames, replace it
        if (!found) {
            frames[front] = page;
            front = (front + 1) % capacity;
            pageFaults++;

            printf("Step %d: Page %d caused a page fault. Frames: [", count + 1, page);
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
            count++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
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

    fifoPageReplacement(pages, n, capacity);

    return 0;
}
