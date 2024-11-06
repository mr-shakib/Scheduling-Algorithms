#include <stdio.h>

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], completion[n], waiting[n], turnaround[n];
    int total_waiting = 0, total_turnaround = 0;

    // Input arrival and burst times for each process
    for (int i = 0; i < n; i++) {
        printf("\nEnter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    // Calculate completion time, turnaround time, and waiting time
    completion[0] = arrival[0] + burst[0];
    turnaround[0] = completion[0] - arrival[0];
    waiting[0] = turnaround[0] - burst[0];
    total_waiting += waiting[0];
    total_turnaround += turnaround[0];

    for (int i = 1; i < n; i++) {
        completion[i] = completion[i - 1] + burst[i];
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
        total_waiting += waiting[i];
        total_turnaround += turnaround[i];
    }

    // Output the results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, arrival[i], burst[i], completion[i], waiting[i], turnaround[i]);
    }

    // Calculate and display average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);

    return 0;
}
