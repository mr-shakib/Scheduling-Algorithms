#include <stdio.h>

struct Process {
    int id;          
    int arrivalTime; 
    int burstTime;   
    int remainingTime; 
    int waitingTime;
    int turnaroundTime;
};

void roundRobin(struct Process processes[], int n, int timeQuantum) {
    int time = 0; 
    int completed = 0; 

    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime > timeQuantum) {
                    time += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                } else {
                    time += processes[i].remainingTime;
                    processes[i].waitingTime = time - processes[i].arrivalTime - processes[i].burstTime;
                    processes[i].turnaroundTime = time - processes[i].arrivalTime;
                    processes[i].remainingTime = 0;
                    completed++;
                }
            }
        }
    }
}

void printProcessInfo(struct Process processes[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n = 3; 
    int timeQuantum = 3; 

    struct Process processes[] = {
        {1, 0, 10, 0, 0, 0}, 
        {2, 1, 4, 0, 0, 0},  
        {3, 2, 5, 0, 0, 0}   
    };

    roundRobin(processes, n, timeQuantum);

    printProcessInfo(processes, n);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}
