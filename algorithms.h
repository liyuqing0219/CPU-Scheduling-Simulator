#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//-----------DS---------------

int pro_count;
struct algorithm
{
    char *name;
    int ar;
};

typedef struct 
{
    char *name;
    int arrTime;
    int burst;
    int level;
}pro;
pro *pros=(pro*)malloc(pro_count*sizeof(pro));


typedef struct 
{
    int jobTh;
    int CPU_Uti;
    int avTurnaround;
    int avRespond;
    int avWaiting;
}metrics;

int timeS;
int* finish=(int *)malloc(pro_count*sizeof(int));
int* turnAround=(int *)malloc(pro_count*sizeof(int));
int* waiting=(int *)malloc(pro_count*sizeof(int));
int* respond=(int *)malloc(pro_count*sizeof(int));
//--------algorithm--------------
void swapP(int i,int j)
{
    char* tem=pros[i].name;
    pros[i].name=pros[j].name;
    pros[j].name=tem;

    int t=pros[i].arrTime;
    pros[i].arrTime=pros[j].arrTime;
    pros[j].arrTime=t;

    t=pros[i].burst;
    pros[i].burst=pros[j].burst;
    pros[j].burst=t;
}
void sortByArr()//Maybe not optimative
{
    for(int i=0;i<pro_count-1;i++)
    {
        for(int j=i+1;j>0;j--)
        {
            if(pros[j].arrTime<pros[j-1].arrTime)
            {
                swapP(j,j-1);
            }
        }
    }
}
void sortByBurstOrLevel()
{
    for(int i=0;i<pro_count-1;i++)
    {
        for(int j=i+1;j>0;j--)
        {
            if(pros[j].burst<pros[j-1].burst)
            {
                swapP(j,j-1);
            }
        }
    }
}
int getBurstSum()
{
   double burstS=0;
    for(int i=0;i<pro_count;i++)
    {
        burstS+=pros[i].burst;
    } 
}
int getTurnSum()
{
    double turnS=0;
     for(int i=0;i<pro_count;i++)
    {
        turnS+=turnAround[i];
    }
}
int getResSum()
{
    double s=0;
    for(int i=0;i<pro_count;i++)
    {
        s+=respond[i];
    }
}
double cal_JobTh()
{
    return ((double)pro_count/(double)timeS);
}
double cal_CPUuti()
{
    double burstS=getBurstSum();
    double turnS=getTurnSum();
    return burstS/turnS;
}
double cal_avTurn()
{
    return getTurnSum()/pro_count;
}
double cal_avRes()
{
    return getResSum()/pro_count;
}
double cal_avWait()
{
    return (getTurnSum()-getBurstSum())/pro_count;
}
void setMetric()
{
    
}
void printMetric()
{

}
void FCFS()
{
    int time=pros[0].arrTime;
    for(int i=0;i<pro_count;i++)
    {
        int arr=pros[i].arrTime;
        int burst=pros[i].burst;
        int waitingTime=time-arr;
        int turnAroundTime=waitingTime+burst;
        finish[i]=time+burst;
        turnAround[i]=turnAroundTime;
        waiting[i]=waitingTime;
        respond[i]=waitingTime;
        time+=burst;
    }
}

void SRTF()
{
    //init
    int time=pros[0].arrTime;
    int* surplus=(int*)malloc(pro_count*sizeof(int));
    int sumSur=0;
    for(int i=0;i<pro_count;i++)
    {
        surplus[i]=pros[i].burst;
        sumSur+=surplus[i];

    }
    int cuBest=0;
    
    /*while(sumSur!=0){

        for(int j=0;pros[j].arrTime<=time;j++){
            if(cuBest==j)continue;
            if(pros[j].burst<pros[cuBest].burst&&surplus[j]>0)
            {
                cuBest=j;
            }
        }
        int idealFin=time+surplus[cuBest];
        int insertBest=cuBest+1;
        int valid=0;
        for(int j=cuBest+1;pros[j].arrTime<idealFin;j++){  
            if(pros[j].arrTime<=pros[cuBest].arrTime)  continue;
            valid++;
              if(pros[j].burst<pros[insertBest].burst&&surplus[j]>0)
            {
                
                insertBest=j;
            
            }
        }
        if(valid>0)
        {
            time+=pros[insertBest].arrTime-time;
            if(surplus[cuBest]==pros[cuBest].burst){
                respond[cuBest]=time-pros[cuBest].arrTime;
            }
            surplus[cuBest]-=pros[insertBest].arrTime-time;
            if(surplus[cuBest]<=0)
            {
                finish[cuBest]=time;
            }

        }
        else{
            
            if(surplus[cuBest]==pros[cuBest].burst){
                respond[cuBest]=time-pros[cuBest].arrTime;
            }
            time+=pros[cuBest].burst;
            finish[cuBest]=time;
            surplus[cuBest]=0;

        }



    }*/
    //
    while(sumSur!=0){
        cuBest=0;
        int valid=0;

        for(int j=0;pros[j].arrTime<=time;j++){
            if(surplus[j]<surplus[cuBest]&&surplus[j]>0)
            {
                cuBest=j;
                valid++;
            }
        }
        if(valid==0)
        {
            time++;
        }
        else
        {
            if(surplus[cuBest]==pros[cuBest].burst)
        {
            respond[cuBest]=time;
        }
        surplus[cuBest]--;
        time++;
        if(surplus[cuBest]==0)
        {
            finish[cuBest]=time;
        }
        
        }
        
        
        
        



    }
        
    
}
void SJF()
{
    int time=pros[0].arrTime;
    int *mark=(int*)malloc(pro_count*sizeof(int));
    for(int i=0;i<pro_count;i++)
    {
        mark[i]=1;
    }
    for(int t=0;t<pro_count;t++)
    {
        int best=0;
        while(mark[best]==0)
        {
            best++;
        }
        if (pros[best].arrTime > time) {
        time = pros[best].arrTime; 
    }
        for(int i=1;i<pro_count;i++)
    {
        
        if(mark[i]==0)continue;
        if(pros[i].burst<pros[best].burst)
        {
            best=i;
        }

    }
    
    respond[best]=time-pros[best].arrTime;
    time+=pros[best].burst;
    finish[best]=time;
    mark[best]=0;
    }
    
}
void RR()
{

}
void prioritySch()
{

}

