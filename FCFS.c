#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of processes!\n");
        return 0;
    }

    int pid[MAX], at[MAX], bt[MAX];
    int wt[MAX], tat[MAX];

    // Input
    printf("Enter ProcessName ArrivalTime BurstTime\n");
    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &at[i], &bt[i]);

        // Convert P1 -> 1
        if (pname[0] == 'P' || pname[0] == 'p')
            pid[i] = atoi(&pname[1]);
        else
            pid[i] = atoi(pname);
    }

    // Sort by Arrival Time (FCFS rule)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {

                int temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // FCFS Calculation
    int current_time = 0;

    for (int i = 0; i < n; i++) {

        if (current_time < at[i])
            current_time = at[i];   // CPU idle case

        wt[i] = current_time - at[i];
        tat[i] = wt[i] + bt[i];

        current_time += bt[i];
    }

    // Calculate averages
    double avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    // Output
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);

    return 0;
}
