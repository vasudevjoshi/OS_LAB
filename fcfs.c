#include<stdio.h>
typedef struct{
int ID,AT,BT,CT,TT,RT,WT;}Process;

void fcfs(Process process[],int n){
	//sorting the process based on the arrival time
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
			if(process[j].AT>process[j+1].AT){
				Process temp=process[j];
				process[j]=process[j+1];
				process[j+1]=temp;
			}
		}
	}
	int elapsed=0;
	int total_WT=0;
	int total_TT=0;
	int total_RT=0;
	printf("GANTT CHART\n");
	for(int i=0;i<n;i++){
		if(process[i].AT>elapsed){
			printf("|IDLE(%d)",process[i].AT);
			elapsed=process[i].AT;
		}
		int temp=elapsed;
		process[i].RT=elapsed-process[i].AT;
		elapsed+=process[i].BT;
		process[i].CT=elapsed;
		process[i].TT=process[i].CT-process[i].AT;
		process[i].WT=process[i].TT-process[i].BT;
		
		printf("|(%d) P-%d (%d)",temp,process[i].ID,elapsed);
		total_WT+=process[i].WT;
		total_RT+=process[i].RT;
		total_TT+=process[i].TT;
	}
	
	printf("|\n");
	
	printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
	for(int i=0;i<n;i++){
						  printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",process[i].ID,process[i].AT,process[i].BT,process[i].CT,process[i].TT,process[i].WT,process[i].RT);
	}
	
	printf("AVG TT=%.2f\n",(float)total_TT/n);
	printf("AVG WT=%.2f\n",(float)total_WT/n);	
	printf("AVG RT=%.2f\n",(float)total_RT/n);	
		
}



int main(){
	int n;
	

	printf("ENTER THE NO OF PROCESS\n");
	scanf("%d",&n);
	Process process[n];
	for(int i=0;i<n;i++){
		printf("Process-%d\n",i+1);
		printf("Enter the arrival time of process:");
		scanf("%d",&process[i].AT);
		printf("Enter the burst time of process:");
		scanf("%d",&process[i].BT);
		process[i].ID=i+1;
		printf("\n");
	}
	fcfs(process,n);
	return 0;
}