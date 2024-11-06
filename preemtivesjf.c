#include <stdio.h>

#define MAX_PROCESSES 10

// Structure to hold process information
typedef struct {
    int id;           // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Total burst time
    int remaining_time; // Remaining burst time (for preemptive SJF)
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to find the process with the minimum remaining time
int findShortestJob(Process processes[], int n, int current_time) {
    int min_time = 9999;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_time) {
            min_time = processes[i].remaining_time;
            index = i;
        }
    }
    return index;
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("\nEnter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    int current_time = 0;
    int completed = 0;

    // Process scheduling
    while (completed < n) {
        int idx = findShortestJob(processes, n, current_time);

        if (idx != -1) {
            // Execute the process for one unit of time
            processes[idx].remaining_time--;
            current_time++;

            // If the process is completed
            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

                total_waiting_time += processes[idx].waiting_time;
                total_turnaround_time += processes[idx].turnaround_time;

                completed++;
            }
        } else {
            // If no process is ready to execute, increment time
            current_time++;
        }
    }

    // Display the results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate and display average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}
