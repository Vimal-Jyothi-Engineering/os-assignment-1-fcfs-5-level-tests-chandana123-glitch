#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    int pid[100], at[100], bt[100];
    int wt[100], tat[100];

    // Input
    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &at[i], &bt[i]);
        pid[i] = atoi(pname + 1);   // Convert P1 -> 1
    }

    // Sort by arrival time (FCFS rule)
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

    // FCFS Waiting Time Calculation
    int current_time = 0;

    for (int i = 0; i < n; i++) {

        // If CPU is idle, jump to arrival time
        if (current_time < at[i])
            current_time = at[i];

        wt[i] = current_time - at[i];
        tat[i] = wt[i] + bt[i];

        current_time += bt[i];
    }

    // Average calculation
    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    // Output
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++)
        printf("P%d %d\n", pid[i], wt[i]);

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++)
        printf("P%d %d\n", pid[i], tat[i]);

    printf("Average Waiting Time: %.2f\n", avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);

    return 0;
}
