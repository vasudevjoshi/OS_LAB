#include <stdio.h>
#include <limits.h>

typedef struct {
    int id,at,bt,ct,wt,tt,rt;
} process;

int findMin(process p[], int n, int currentTime) {
    int min_index = -1;
    int min_BT = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= currentTime && p[i].bt > 0) {
            if (p[i].bt < min_BT) {
                min_BT = p[i].bt;
                min_index = i;
            }
        }
    }
    return min_index;
}
void sjf(process p[],int n){
    int total_WT =0,total_TT = 0,total_RT =0,currenttime=0,completed = 0;
    printf("GANTT CHART\n");
    while(completed<n){
        int mindex = findMin(p,n,currenttime);
        if(mindex == -1){
            printf("|IDLE (%d)",currenttime);
            currenttime++;
            continue;
        }
        currenttime+=p[mindex].bt;
        printf("|(%d) P- %d (%d)",currenttime -p[mindex].bt,p[mindex].id,currenttime);
        completed++;
        p[mindex].ct = currenttime;
        p[mindex].tt = p[mindex].ct - p[mindex].at;
        p[mindex].wt = p[mindex].tt - p[mindex].bt;
        p[mindex].rt = currenttime - p[mindex].at;
        total_TT+= p[mindex].tt;
        total_WT+=p[mindex].wt;
        total_RT+=p[mindex].rt;
        p[mindex].bt = 0;
    }
      printf("|\n");

    printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt, p[i].rt);
    }

    printf("AVG TT=%.2f\n", (float) total_TT / n);
    printf("AVG WT=%.2f\n", (float) total_WT / n);
    printf("AVG RT=%.2f\n", (float) total_RT / n);
}
int main() {
    int n;

    printf("ENTER THE NO OF p\n");
    scanf("%d", &n);
    process p[n];
    for (int i = 0; i < n; i++) {
        printf("p-%d\n", i + 1);
        printf("Enter the arrival time of p: ");
        scanf("%d", &p[i].at);
        printf("Enter the burst time of p: ");
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
        printf("\n");
    }
    sjf(p, n);
    return 0;
}
