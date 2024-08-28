/*Round robin */
#include<stdio.h>
typedef struct{
	int ID,AT,BT,CT,TT,WT,RT,remT,flag;
}Process;

void roundR(Process process[],int n){
	int TWT=0,TTT=0,TRT=0,curTime=0,queue[100],front=-1,rear=-1,quantum;
	printf("Enter quantum\n");
	scanf("%d",&quantum);
	for(int i=0;i<n;i++){
		process[i].remT=process[i].BT;
		process[i].flag=0;
	}
	if(curTime<process[0].AT){
		curTime=process[0].AT;
	}
	queue[++rear]=0;
	process[0].flag=1;
	while(front<rear){
		int i=queue[++front];
		
		if(process[i].remT==process[i].BT){
			process[i].RT=curTime-process[i].AT;
		}
		if(process[i].remT>quantum){
			process[i].remT-=quantum;
			curTime+=quantum;
			printf("|P-%d (%d)",process[i].ID,curTime);
		}
		else{
			curTime+=process[i].remT;
			process[i].remT=0;
			printf("|P-%d (%d)",process[i].ID,curTime);
		}
		for(int i=1;i<n && process[i].AT<=curTime;i++){
			if(!process[i].flag){
				process[i].flag=1;
				queue[++rear]=i;
			}
		}
		if(process[i].remT==0){
			process[i].CT=curTime;
			process[i].TT=process[i].CT-process[i].AT;
			process[i].WT=process[i].TT-process[i].BT;
			TTT+=process[i].TT;
			TWT+=process[i].WT;
			TRT+=process[i].RT;
		}
		else{
			queue[++rear]=i;
		}
	}
	printf("|\n");
	printf("PID\t AT\t BT\t TT\t WT\t RT\n");
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",process[i].ID,process[i].AT,process[i].BT,process[i].TT,process[i].WT,process[i].RT);
	}
	printf("AVG TT=%0.2f",(float)TTT/n);
	printf("AVG WT=%0.2f",(float)TWT/n);
	printf("AVG RT=%0.2f",(float)TRT/n);
}
		
			



int main(){
	int n;
	printf("ENTER THE NUMBER OF PROCESS\n");
	scanf("%d",&n);
	Process process[n];
	printf("ENTER AT BT\n");
	for(int i=0;i<n;i++){
		process[i].ID=i+1;
		scanf("%d %d",&process[i].AT,&process[i].BT);
	}
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(process[j].AT>process[j+1].AT){
				Process temp=process[j];
				process[j]=process[j+1];
				process[j+1]=temp;
			}
		}
	}
	roundR(process,n);
	return 0;
}