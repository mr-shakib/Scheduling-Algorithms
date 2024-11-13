#include<stdio.h>

struct  Process
{
    int id;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

void calculateTimes(struct Process processes[], int n){
    int currentTime = 0;
    int completed = 0;
    int minPriorityIndex;

    while (completed<n){
        minPriorityIndex = -1;

        for(int i = 0; i < n; i++){
            if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0){
                if(minPriorityIndex == -1 || processes[i].priority < processes[minPriorityIndex].priority){
                    minPriorityIndex = i;
                }
            }
        }

        if (minPriorityIndex != -1){
            currentTime += processes[minPriorityIndex].burstTime;
            processes[minPriorityIndex].completionTime = currentTime;
            processes[minPriorityIndex].turnaroundTime = currentTime - processes[minPriorityIndex].arrivalTime;
            processes[minPriorityIndex].waitingTime = processes[minPriorityIndex].turnaroundTime - processes[minPriorityIndex].burstTime;
            completed ++;
        }else{
            currentTime++;
        }
    }
}

void printProcessInfo(struct Process processes[],int n){
    printf("ID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i<n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].id,processes[i].arrivalTime,processes[i].burstTime,processes[i].priority,processes[i].waitingTime,processes[i].turnaroundTime);
    }
}



int main(){

    int n = 3;

    // Define the processes with given data
    struct Process processes[] = {
        {1, 10, 0, 2, 0, 0, 0},  // Process P1: arrivalTime=0, burstTime=10, priority=2
        {2, 5, 2, 1, 0, 0, 0},   // Process P2: arrivalTime=2, burstTime=5, priority=1
        {3, 8, 3, 3, 0, 0, 0}    // Process P3: arrivalTime=3, burstTime=8, priority=3
    };

    calculateTimes(processes,n);
    printProcessInfo(processes,n);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for(int i = 0; i<n ; i++){
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("Average Waiting Time = %.2f\n",totalWaitingTime/n);
    printf("Average Turnaround Time = %.2f\n",totalTurnaroundTime/n);


    
    return 0;
}