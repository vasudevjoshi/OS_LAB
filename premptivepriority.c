#include <stdio.h>
#include <limits.h>

typedef struct {
    int ID, AT, BT, CT, TT, RT, WT, priority, remainingTime;
} Process;

int findMin(Process process[], int n, int currentTime) {
    int min_index = -1;
    int min_Priority = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (process[i].AT <= currentTime && process[i].remainingTime > 0) {
            if (process[i].priority < min_Priority) {
                min_Priority = process[i].priority;
                min_index = i;
            }
        }
    }
    return min_index;
}

void priority(Process process[], int n) {
    int elapsed = 0;
    int total_WT = 0;
    int total_TT = 0;
    int total_RT = 0;
    int completed = 0;
    int currentTime = 0;

    // Initializing remaining time for each process
    for (int i = 0; i < n; i++) {
        process[i].remainingTime = process[i].BT;
    }

    printf("GANTT CHART\n");

    while (completed < n) {
        int min_index = findMin(process, n, currentTime);
        if (min_index == -1) {
            printf("|IDLE(%d)", currentTime);
            currentTime++;
            continue;
        }

        // Process the selected process
        if (process[min_index].remainingTime == process[min_index].BT) {
            process[min_index].RT = currentTime - process[min_index].AT;
        }

        process[min_index].remainingTime--;
        currentTime++;

        printf("|(%d) P-%d (%d)", currentTime - 1, process[min_index].ID, currentTime);

        // If the process is completed
        if (process[min_index].remainingTime == 0) {
            completed++;
            process[min_index].CT = currentTime;
            process[min_index].TT = process[min_index].CT - process[min_index].AT;
            process[min_index].WT = process[min_index].TT - process[min_index].BT;

            total_WT += process[min_index].WT;
            total_RT += process[min_index].RT;
            total_TT += process[min_index].TT;
        }
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
        printf("Enter the priority of process: ");
        scanf("%d", &process[i].priority);
        process[i].ID = i + 1;
        printf("\n");
    }
    priority(process, n);
    return 0;
}