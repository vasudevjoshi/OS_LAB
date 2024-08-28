#include <stdio.h>
#include <limits.h>

typedef struct {
    int ID, AT, BT, CT, TT, RT, WT;
} Process;

int findMin(Process process[], int n, int currentTime) {
    int min_index = -1;
    int min_BT = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (process[i].AT <= currentTime && process[i].BT > 0) {
            if (process[i].BT < min_BT) {
                min_BT = process[i].BT;
                min_index = i;
            }
        }
    }
    return min_index;
}

void sjf(Process process[], int n) {

    int total_WT = 0;
    int total_TT = 0;
    int total_RT = 0;
    int completed = 0;
    int currentTime = 0;

    printf("GANTT CHART\n");

    while (completed < n) {
        int min_index = findMin(process, n, currentTime);
        if (min_index == -1) {
            printf("|IDLE(%d)", currentTime);
            currentTime++;
            continue;
        }

        // Non-preemptive: Once a process starts, it runs to completion
        currentTime += process[min_index].BT;

        printf("|(%d) P-%d (%d)", currentTime - process[min_index].BT, process[min_index].ID, currentTime);

        // If the process is completed
        completed++;
        process[min_index].CT = currentTime;
        process[min_index].TT = process[min_index].CT - process[min_index].AT;
        process[min_index].WT = process[min_index].TT - process[min_index].BT;
        process[min_index].RT = process[min_index].WT; // For non-preemptive SJF, RT is the same as WT

        total_WT += process[min_index].WT;
        total_RT += process[min_index].RT;
        total_TT += process[min_index].TT;

        // Mark the process as completed
        process[min_index].BT = 0;
    }

    printf("|\n");

    printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", process[i].ID, process[i].AT, process[i].BT, process[i].CT, process[i].TT, process[i].WT, process[i].RT);
    }

    printf("AVG TT=%.2f\n", (float) total_TT / n);
    printf("AVG WT=%.2f\n", (float) total_WT / n);
    printf("AVG RT=%.2f\n", (float) total_RT / n);
}

int main() {
    int n;

    printf("ENTER THE NO OF PROCESS\n");
    scanf("%d", &n);
    Process process[n];
    for (int i = 0; i < n; i++) {
        printf("Process-%d\n", i + 1);
        printf("Enter the arrival time of process: ");
        scanf("%d", &process[i].AT);
        printf("Enter the burst time of process: ");
        scanf("%d", &process[i].BT);
        process[i].ID = i + 1;
        printf("\n");
    }
    sjf(process, n);
    return 0;
}