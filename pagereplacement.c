#include <stdio.h>

void printFrames(int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

void FIFO(int pages[], int pageCount, int frameCount) {
    int frames[frameCount];
    int pageFaults = 0, currentFrame = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    printf("Page Reference String:\n");
    printFrames(frames, frameCount);

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            pageFaults++;
            frames[currentFrame] = page;
            currentFrame = (currentFrame + 1) % frameCount;
        }

        printFrames(frames, frameCount);
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int pageCount = sizeof(pages) / sizeof(pages[0]);
    int frameCount;

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    FIFO(pages, pageCount, frameCount);

    return 0;
}
