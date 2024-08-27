#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
    int id,at,bt,ct,tt,rt,wt;
}process;
int findMin(process p[],int n,int currenttime){
    int min_index = -1;
    int min_bt = INT_MAX;
    for(int i =0;i<n;i++){
        if(p[i].at<=currenttime && p[i].bt>0){
            if(p[i].bt<min_bt){
                min_index = i;
                min_bt = p[i].bt;
            }
        }
    }
    return min_index;
}
void sjfnonpreemptive(process p[],int n){
    int completed = 0,currenttime = 0,total_wt = 0,total_rt =0,total_tt = 0;
    printf("GANTT CHART\n");
    while(completed < n){
        int mindex = findMin(p,n,currenttime);
        if(mindex == -1){
            printf("|IDLE (%d)",currenttime);
            currenttime++;
            continue;
        }
        currenttime+=p[mindex].bt;
        printf("|(%d) P-%d (%d)",currenttime-p[mindex].bt,p[mindex].id,currenttime);
        completed++;
        p[mindex].ct = currenttime;
        p[mindex].tt = p[mindex].ct - p[mindex].at;
        p[mindex].wt = p[mindex].tt - p[mindex].bt;
        p[mindex].rt=p[mindex].wt;
        total_tt+=p[mindex].tt;
        total_wt+=p[mindex].wt;
        total_rt+=p[mindex].rt;
        p[mindex].bt = 0;
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
    printf("Enter the number of processes:");
    scanf("%d",&n);
    process p[n];
    for(int i = 0;i<n;i++){
        printf("For the Process: %d\n",i+1);
        printf("Enter the Arrival time:");
        scanf("%d",&p[i].at);
        printf("Enter Burst time: ");
        scanf("%d",&p[i].bt);
        p[i].id = i + 1;
    }
    sjfnonpreemptive(p,n);
    return 0;
}
