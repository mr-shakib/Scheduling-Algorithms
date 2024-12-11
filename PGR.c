#include<stdio.h>

void pageReplacementFIFO(int n, int pages[], int capacity)
{
    int frames[capacity];
    int next = 0;
    int pageFaults = 0;

    for (int i = 0; i < capacity; i++){
        frames[i] = -1;
    }

    for (int i  = 0 ; i < n ; i++){
        int page = pages[i];
        int found = 0;

        for (int j = 0 ; j < capacity ; j++){
            if (frames[j] == page){
                found = 1;
                break;
            }
        }

        if(!found){
            frames[next] = page;
            next = (next + 1) % capacity;
            pageFaults++;
        }
    }

    printf("Total Page Faults : %d",pageFaults);
}

int main()
{
    int n, capacity;

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    int pages[n];
    printf("Enter the pages:");
    for (int i = 0 ; i < n; i++){
        scanf("%d",&pages[i]);
    }

    printf("Enter the capacity: ");
    scanf("%d",&capacity);

    pageReplacementFIFO(n,pages,capacity);

    return 0;
}
