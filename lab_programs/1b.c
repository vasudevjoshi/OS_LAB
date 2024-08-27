// #include <stdio.h>
// #include <limits.h>

// typedef struct
// {
//     int ID, AT, BT, CT, TT, RT, WT, remainingTime;
// } Process;

// int findMin(Process process[], int n, int currentTime)
// {
//     int min_index = -1;
//     int min_remainingTime = INT_MAX;

//     for (int i = 0; i < n; i++)
//     {
//         if (process[i].AT <= currentTime && process[i].remainingTime > 0)
//         {
//             if (process[i].remainingTime < min_remainingTime)
//             {
//                 min_remainingTime = process[i].remainingTime;
//                 min_index = i;
//             }
//         }
//     }
//     return min_index;
// }

// void sjf(Process process[], int n)
// {
//     int elapsed = 0;
//     int total_WT = 0;
//     int total_TT = 0;
//     int total_RT = 0;
//     int completed = 0;
//     int currentTime = 0;

//     // Initializing remaining time for each process
//     for (int i = 0; i < n; i++)
//     {
//         process[i].remainingTime = process[i].BT;
//     }

//     printf("GANTT CHART\n");

//     while (completed < n)
//     {
//         int min_index = findMin(process, n, currentTime);
//         if (min_index == -1)
//         {
//             printf("|IDLE(%d)", currentTime);
//             currentTime++;
//             continue;
//         }

//         // Process the selected process
//         if (process[min_index].remainingTime == process[min_index].BT)
//         {
//             process[min_index].RT = currentTime - process[min_index].AT;
//         }

//         process[min_index].remainingTime--;
//         currentTime++;

//         printf("|(%d) P-%d (%d)", currentTime - 1, process[min_index].ID, currentTime);

//         // If the process is completed
//         if (process[min_index].remainingTime == 0)
//         {
//             completed++;
//             process[min_index].CT = currentTime;
//             process[min_index].TT = process[min_index].CT - process[min_index].AT;
//             process[min_index].WT = process[min_index].TT - process[min_index].BT;

//             total_WT += process[min_index].WT;
//             total_RT += process[min_index].RT;
//             total_TT += process[min_index].TT;
//         }
//     }

//     printf("|\n");

//     printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", process[i].ID, process[i].AT, process[i].BT, process[i].CT, process[i].TT, process[i].WT, process[i].RT);
//     }

//     printf("AVG TT=%.2f\n", (float)total_TT / n);
//     printf("AVG WT=%.2f\n", (float)total_WT / n);
//     printf("AVG RT=%.2f\n", (float)total_RT / n);
// }

// int main()
// {
//     int n;

//     printf("ENTER THE NO OF PROCESS\n");
//     scanf("%d", &n);
//     Process process[n];
//     for (int i = 0; i < n; i++)
//     {
//         printf("Process-%d\n", i + 1);
//         printf("Enter the arrival time of process: ");
//         scanf("%d", &process[i].AT);
//         printf("Enter the burst time of process: ");
//         scanf("%d", &process[i].BT);
//         process[i].ID = i + 1;
//         printf("\n");
//     }
//     sjf(process, n);
//     return 0;
// }


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
    int id,at,bt,ct,tt,rt,wt,remainingtime;
}process;
int findMin(process p[],int n,int currenttime){
    int min_index = -1;
    int min_remainingtime = INT_MAX;
    for(int i =0;i<n;i++){
        if(p[i].at<=currenttime && p[i].remainingtime>0){
            if(p[i].remainingtime<min_remainingtime){
                min_index = i;
                min_remainingtime = p[i].remainingtime;
            }
        }
    }
    return min_index;
}
void sjfpremptive(process p[],int n){
    int elapsed  = 0,completed = 0,currenttime = 0,total_wt = 0,total_rt =0,total_tt = 0;
    for(int i = 0;i<n;i++){
        p[i].remainingtime = p[i].bt;
    }

    printf("GANTT CHART\n");
    while(completed<n){
        int mindex = findMin(p,n,currenttime);
        if(mindex == -1){
            printf("|IDLE (%d)",currenttime);
            currenttime++;
            continue;
        }
    if(p[mindex].remainingtime == p[mindex].bt){
        p[mindex].rt = currenttime - p[mindex].at;
    }
    p[mindex].remainingtime--;
    currenttime++;
    printf("|(%d) P-%d (%d)",currenttime -1,p[mindex].id,currenttime);
    if(p[mindex].remainingtime == 0){
            completed++;
            p[mindex].ct = currenttime;
            p[mindex].tt = p[mindex].ct - p[mindex].at;
            p[mindex].wt = p[mindex].tt - p[mindex].bt;
           
           total_rt+=p[mindex].rt;
           total_wt+=p[mindex].wt;
           total_tt+=p[mindex].tt;
    }
    }
    printf("|\n");
     printf("ID\tAT\tBT\tCT\tTT\tWT\tRT\n");
     for(int i = 0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt,p[i].rt);
     }
     printf("Average Turn around time is: %0.2f\n",(float)total_tt/n);
     printf("Average waiting time is: %0.2f\n",(float)total_wt/n);
     printf("Average Respone  time is: %0.2f\n",(float)total_rt/n);
}

int main(){
    int n;
    printf("Enter the number of processes:\n");
    scanf("%d",&n);
    process p[n];
    for(int i = 0;i<n;i++){
        printf("For Process: %d\n\n",i+1);
        printf("Enter the Arrival time: ");
        scanf("%d",&p[i].at);
        printf("Enter the Burst time: ");
        scanf("%d",&p[i].bt);
        p[i].id = i + 1;
    }
    sjfpremptive(p,n);
    
}