#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int id,at,bt,ct,tt,wt,rt,remT,flag;
}process;

void roundrobin(process p[],int n){
    int total_TT,total_WT,total_RT,currenttime,quantam,front,rear,queue[100];
    front = rear = -1;
    printf("Enter the Quantam:");
    scanf("%d",&quantam);
    for(int i = 0;i<n;i++){
        p[i].remT = p[i].bt;
        p[i].flag = 0;
    }
    if(currenttime<p[0].at){
        currenttime =p[0].at;
    }
    queue[++rear] = 0;
    p[0].flag = 1;
    while(front <rear){
        int i = queue[++front];
        if(p[i].remT == p[i].bt){
            p[i].rt = currenttime - p[i].at;
        }
        if(p[i].remT > quantam){
            p[i].remT-=quantam;
            currenttime+=quantam;
            printf("| P-%d (%d)",p[i].id,currenttime);
        }
        else{
             p[i].remT=0;
            currenttime+=quantam;
            printf("| P-%d (%d)",p[i].id,currenttime);
        }
        for(int i = 0;i<n && p[i].at<=currenttime;i++){
            if(!p[i].flag){
                p[i].flag = 1;
                queue[++rear] = i;
            }
        }
        if(p[i].remT == 0){
            p[i].ct = currenttime;
            p[i].tt = p[i].ct - p[i].at;
            p[i].wt = p[i].tt - p[i].bt;
            total_RT+=p[i].rt;
            total_TT+=p[i].tt;
            total_WT+=p[i].wt;
        }
        else{
            queue[++rear] = i;
        }
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
int main(){
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
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n-1-i;j++){
            if(p[j].at > p[j+1].at){
                process temp = p[j];
                p[j]= p[j+1];
                p[j+1] = temp;
            }
        }
    }
    roundrobin(p,n);
}