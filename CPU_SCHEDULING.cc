#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
#include <stdio.h>
#include <queue>
#include <string>
#include <cmath>
#define BUFFERSIZE 1000
struct process {
	float noOfProcess;
	char* processList;
  float* tatMean;
  float* normMean;
	float* serviceTime;
  float* remainingTime;
	float* arrivalTime;
	float* waitingTime;
	float* completionTime;
	float* turnAroundTime;
  float * normTurn;
  int * preempt;
  int * priority;
  int *currentPriority;
  int* time;
	
	process(int processCount){
		//Setting total no of process
		noOfProcess = processCount;
    	// Dynamically allocate memory 
    	processList =  new char [processCount];
    	serviceTime = new float [processCount];
      remainingTime = new float [processCount];
    	arrivalTime = new float [processCount];
    	waitingTime = new float [processCount];
    	turnAroundTime = new float [processCount];
    	completionTime = new float [processCount];
      normTurn = new float [processCount];
      tatMean=new float[1];
      normMean= new float[1];
      time =new int[1];
      preempt=new int[processCount];
      priority=new int[processCount];
      currentPriority=new int[processCount];
     

	}
};
//---------------------------FCFS-----------------------------
void fcfs(process p,int m){
  float sum1=0;
  float sum2=0;
  int number= (int)p.noOfProcess;
  char trace[number][21];
    for(int i=0; i<number;i++){
    for(int j=0;j<20 ;j++){
     trace[i][j]=' ';
    }
  }
  // calculating completion time

     p.completionTime[0] = p.serviceTime[0];
    for(int i = 1; i < p.noOfProcess; i++){
    	p.completionTime[i] = p.completionTime[i - 1] + p.serviceTime[i];
     
    }
    //calculating turnaroundtime
    for (int i = 0; i < p.noOfProcess; i++) {
  
		p.turnAroundTime[i] = p.completionTime[i]-p.arrivalTime[i];
    sum1=sum1+p.turnAroundTime[i];
    p.tatMean[0]=sum1/p.noOfProcess;
    }
    //calculating waiting time
    p.waitingTime[0] = 0; 
	for (int i = 1; i < p.noOfProcess; i++ ) {
		p.waitingTime[i] = p.turnAroundTime[i]-p.serviceTime[i];
	}
  //calculating normalized turnaround time
  for (int i = 0; i < p.noOfProcess; i++ ) {
		p.normTurn[i] = p.turnAroundTime[i]/p.serviceTime[i];
     sum2=sum2+p.normTurn[i];
    p.normMean[0]=sum2/p.noOfProcess;
	}
  //  cerr << fixed << setprecision(2)<< p.normMean << "\n";
  //  cerr << fixed << setprecision(2) << p.tatMean << "\n";
      for(int i=0; i<number;i++){
    for(int j=p.arrivalTime[i]+p.waitingTime[i];j<p.completionTime[i] ;j++){
      trace[i][j]='*';
    
    
    }
    for(int j=p.arrivalTime[i];j<p.arrivalTime[i]+p.waitingTime[i] ;j++){
      trace[i][j]='.';
    
    
    }
  }
  //if mode is trace
  if(m==1){
      cout << "FCFS  ";
  for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  
  }

 
}
//---------------------------RR-----------------------------
void RR (process p, int quantum,int m){
  queue<int> q;
  float sum1=0;
  float sum2=0;
  int pturn=-1;
  int temp;
  int number= (int)p.noOfProcess;
  int currentQ=quantum;
  char trace[number][p.time[0]+1];
  for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }

  
  for ( int i=0; i <p.time[0]+1 ;i++){
    for (int j= 0; j< p.noOfProcess;j++){
      if(p.arrivalTime[j]==i){
        q.push(j);
        trace[j][i]='.';
      }
      }
      
        if(i==0){
         pturn=q.front();
         q.pop();}
           for (int l = 0; l < q.size(); l++)
          {
            temp=q.front();
            trace[temp][i]='.';
            q.pop();
            q.push(temp);
          }
      
       if((p.remainingTime[pturn]==0)|| (currentQ==0)){
        if(p.remainingTime[pturn]==0){
          p.completionTime[pturn]=i;
          p.turnAroundTime[pturn]=p.completionTime[pturn]-p.arrivalTime[pturn];
          p.normTurn[pturn]=p.turnAroundTime[pturn]/p.serviceTime[pturn];
            // cerr << "this is sum2:" << sum2<< "\n";
          sum1=sum1+p.turnAroundTime[pturn];
          sum2=sum2+p.normTurn[pturn];
          p.tatMean[0]=sum1/p.noOfProcess;
          p.normMean[0]=sum2/p.noOfProcess;
          pturn=q.front();
          q.pop();
          currentQ=quantum;

        }
        else{
          if(q.size()==0 && p.remainingTime[0]>0){
            currentQ=quantum;
          }
          else{
            q.push(pturn);
            trace[pturn][i]='.';
            pturn=q.front();
            q.pop();
            currentQ=quantum;
          }
  
          
        }
      }
      //  cout << "This is time : " << i << "pturn is: " << pturn << endl;
      trace[pturn][i]='*';
      p.remainingTime[pturn]=p.remainingTime[pturn]-1;
      currentQ=currentQ-1;
  }
  //if mode is trace
  if(m==1){
  cout << "RR-" << quantum <<"  ";
  for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  }

}
//---------------------------SPN-----------------------------
void SPN(process p, int m){
  queue<int> q;
  float sum1,sum2;
  int pturn=-1;
  int min;
  int number= (int)p.noOfProcess;
  char trace[number][p.time[0]+1];
    for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }
  
  for (int i=0; i<p.time[0]+1;i++){
     min=100;
    for(int j=0;j<p.noOfProcess;j++){
        if (p.arrivalTime[j]==i){
          q.push(j);
        }
    }
    if(i==0){
        pturn=q.front();
        q.pop();
        


    }

    else if(p.remainingTime[pturn]==0){

      p.completionTime[pturn]=i;
      p.turnAroundTime[pturn] = p.completionTime[pturn]-p.arrivalTime[pturn];
      p.normTurn[pturn]=p.turnAroundTime[pturn]/p.serviceTime[pturn];
      sum1=sum1+p.turnAroundTime[pturn];
      sum2=sum2+p.normTurn[pturn];
      p.tatMean[0]=sum1/p.noOfProcess;
      p.normMean[0]=sum2/p.noOfProcess;
      //cerr << p.completionTime[pturn] << "\n";
       if(q.size()==1){
        pturn=q.front();
        q.pop();
       }
       else{
       for(int n=0; n<q.size();n++){
              int temp=p.serviceTime[q.front()];
              //cerr << "popped process: " << q.front() << "\n";
              int popped = q.front();
              q.pop();
              if(temp<min){
                min=temp;
                //cerr << "min: " << min << "\n";
              }
              q.push(popped);
              //cerr << "pushed process: " << popped << "\n";

            }
            // cerr << "min: " << min << "\n";
             for(int n=0; n<q.size();n++){
              //cerr << "process in queue: " << q.front() << "\n";
              int front = q.front();
              int temp=p.serviceTime[q.front()];
              q.pop();
              if(temp==min){
                pturn=front;
                
              }
              else{
              q.push(front);
              //cerr << "pushed after min popped:" << front << "\n";
              }
              
            }
            min=100;
            }

    }
    p.remainingTime[pturn]--;
    for(int n=0; n<q.size();n++){
              int popped = q.front();
              q.pop();
              trace[popped][i]='.';
              q.push(popped);
              //cerr << "pushed process: " << popped << "\n";

            }
    //cerr << pturn << "\n";
    if(i<p.time[0]){
    trace[pturn][i]='*';
    }
  
  }
   if(m==1){
  cout << "SPN" << "   ";
   for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  }
}
//---------------------------SRT-----------------------------
void SRT(process p, int m){
  queue<int> q;
  float sum1,sum2;
  int pturn=-1;
  int min;
  int number= (int)p.noOfProcess;
  char trace[number][p.time[0]+1];
    for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }
  
  for (int i=0; i<p.time[0]+1;i++){
     min=100;
    for(int j=0;j<p.noOfProcess;j++){
        if (p.arrivalTime[j]==i){
          q.push(j);
        }
    }
    if(i==0){
        pturn=q.front();
        // q.pop();
        // q.push(pturn);


    }

    else if(p.remainingTime[pturn]==0){
        for(int n=0; n<q.size();n++){
              //cerr << "process in queue: " << q.front() << "\n";
              int front = q.front();
              q.pop();
              if(front!=pturn){
              q.push(front);
              //cerr << "pushed after min popped:" << front << "\n";
              }
              
            }
      p.completionTime[pturn]=i;
      p.turnAroundTime[pturn] = p.completionTime[pturn]-p.arrivalTime[pturn];
      p.normTurn[pturn]=p.turnAroundTime[pturn]/p.serviceTime[pturn];
      sum1=sum1+p.turnAroundTime[pturn];
      sum2=sum2+p.normTurn[pturn];
      p.tatMean[0]=sum1/p.noOfProcess;
      p.normMean[0]=sum2/p.noOfProcess;
      //cerr << p.completionTime[pturn] << "\n";
    }
       if(q.size()==1){
        pturn=q.front();
        //q.pop();
       }
       else{
       for(int n=0; n<q.size();n++){
              int temp=p.remainingTime[q.front()];
              //cerr << "popped process: " << q.front() << "\n";
              int popped = q.front();
              q.pop();
              if(temp<min){
                min=temp;
                pturn = popped;
                //cerr << "min: " << min << "\n";
              }
              else if(temp==min && popped<pturn){

                
                  pturn = popped;
                

              }
              q.push(popped);
              //cerr << "pushed process: " << popped << "\n";

            }
     
            min=100;
            }

    
    p.remainingTime[pturn]--;
    for(int n=0; n<q.size();n++){
              int popped = q.front();
              q.pop();
              trace[popped][i]='.';
              q.push(popped);
              //cerr << "pushed process: " << popped << "\n";

            }
    //cerr << pturn << "\n";
    if(i<p.time[0]){
    trace[pturn][i]='*';
    }
  
  }
   if(m==1){
  cout << "SRT" << "   ";
  for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  }
}
//---------------------------HRRN-----------------------------
void HRRN(process p, int m){
  queue<int> q;
  float sum1,sum2;
  int pturn=-1;
  int max;
  int number= (int)p.noOfProcess;
  char trace[number][p.time[0]+1];
    for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }
  
  for (int i=0; i<p.time[0]+1;i++){
     max=-1;
    for(int j=0;j<p.noOfProcess;j++){
        if (p.arrivalTime[j]==i){
          q.push(j);
        }
    }
    if(i==0){
        pturn=q.front();
        q.pop();
        


    }

    else if(p.remainingTime[pturn]==0){

      p.completionTime[pturn]=i;
      p.turnAroundTime[pturn] = p.completionTime[pturn]-p.arrivalTime[pturn];
      p.normTurn[pturn]=p.turnAroundTime[pturn]/p.serviceTime[pturn];
      sum1=sum1+p.turnAroundTime[pturn];
      sum2=sum2+p.normTurn[pturn];
      p.tatMean[0]=sum1/p.noOfProcess;
      p.normMean[0]=sum2/p.noOfProcess;
      //cerr << p.completionTime[pturn] << "\n";
       if(q.size()==1){
        pturn=q.front();
        q.pop();
       }
       else{
       for(int n=0; n<q.size();n++){
              int ratio=((i-p.arrivalTime[q.front()])+p.serviceTime[q.front()])/p.serviceTime[q.front()];
              //cerr << "popped process: " << q.front() << "\n";
              int popped = q.front();
              q.pop();
              if(ratio>max){
                max=ratio;
                //cerr << "min: " << min << "\n";
              }
              q.push(popped);
              //cerr << "pushed process: " << popped << "\n";

            }
            // cerr << "min: " << min << "\n";
             for(int n=0; n<q.size();n++){
              //cerr << "process in queue: " << q.front() << "\n";
              int front = q.front();
              int ratio=((i-p.arrivalTime[q.front()])+p.serviceTime[q.front()])/p.serviceTime[q.front()];
              q.pop();
              if(ratio==max){
                pturn=front;
                
              }
              else{
              q.push(front);
              //cerr << "pushed after min popped:" << front << "\n";
              }
              
            }
            max=-1;
            }

    }
    p.remainingTime[pturn]--;
    for(int n=0; n<q.size();n++){
              int popped = q.front();
              q.pop();
              trace[popped][i]='.';
              q.push(popped);
              //cerr << "pushed process: " << popped << "\n";

            }
    //cerr << pturn << "\n";
    if(i<20){
    trace[pturn][i]='*';
    }
  
  }
   if(m==1){
  cout << "HRRN" << "  ";
   for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  }
}
//---------------------------FF-1-----------------------------
void FF1 (process p,int m){
  float sum1=0;
  float sum2=0;
  int pturn=-1;
  int currentp=0;
  int temp;
  int number= (int)p.noOfProcess;
  int currentQ=1;
  queue <int> working_queue;
  vector<queue<int>> vec;
  vec.push_back(queue<int>());
  char trace[number][p.time[0]+1];
  for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }

  
  for ( int i=0; i <p.time[0]+1 ;i++){
    for (int j= 0; j< p.noOfProcess;j++){
      if(p.arrivalTime[j]==i){
        vec[0].push(j);
        trace[j][i]='.';
      }
      }
        if(i==0){
         pturn=vec[0].front();
         vec[0].pop();}
           for (int l = 0; l < vec.size(); l++)
          {  working_queue=vec[l];
            for( int x=0;x< vec[l].size();x++){
            temp=working_queue.front();
            trace[temp][i]='.';
            working_queue.pop();
            working_queue.push(temp);
          }
          
          }
      
       if((p.remainingTime[pturn]==0)|| (currentQ==0)){
        if(p.remainingTime[pturn]==0){
          p.completionTime[pturn]=i;
          p.turnAroundTime[pturn]=p.completionTime[pturn]-p.arrivalTime[pturn];
          p.normTurn[pturn]=p.turnAroundTime[pturn]/p.serviceTime[pturn];
            // cerr << "this is sum2:" << sum2<< "\n";
          sum1=sum1+p.turnAroundTime[pturn];
          sum2=sum2+p.normTurn[pturn];
          p.tatMean[0]=sum1/p.noOfProcess;
          p.normMean[0]=sum2/p.noOfProcess;
              for (int z=0 ; z< vec.size();z++){
              if(vec[z].size()!=0){
                   pturn=vec[z].front();
                   vec[z].pop();
                  currentQ=1;
                  break;
              }
            }

        }
        else{
          if(vec[currentp].size()==0 && p.remainingTime[0]>0){
            currentQ=1;
          }
          else{
            p.preempt[pturn]=p.preempt[pturn]+1;
            currentp=p.preempt[pturn];
            vec.push_back(queue<int>());
            vec[currentp].push(pturn);
            trace[pturn][i]='.';
            for (int z=0 ; z< vec.size();z++){
              if(vec[z].size()!=0){
                   pturn=vec[z].front();
                   vec[z].pop();
                  currentQ=1;
                  break;
              }
            }
         
          }
  
          
        }
      }
      //  cout << "This is time : " << i << "pturn is: " << pturn << endl;
      trace[pturn][i]='*';
      p.remainingTime[pturn]=p.remainingTime[pturn]-1;
      currentQ=currentQ-1;
  }
  //if mode is trace
  if(m==1){
  cout << "FB-1" <<"  ";
  for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  }

}
//---------------------------FF-2i-----------------------------
void FF2 (process p,int m){
  float sum1=0;
  float sum2=0;
  int pturn=-1;
  int currentp=0;
  int temp;
  int number= (int)p.noOfProcess;
  int currentQ=1;
  queue <int> working_queue;
  vector<queue<int>> vec;
  vec.push_back(queue<int>());
  char trace[number][p.time[0]+1];
  for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }

  
  for ( int i=0; i <p.time[0]+1 ;i++){
    for (int j= 0; j< p.noOfProcess;j++){
      if(p.arrivalTime[j]==i){
        vec[0].push(j);
        trace[j][i]='.';
      }
      }
        if(i==0){
         pturn=vec[0].front();
         vec[0].pop();}
           for (int l = 0; l < vec.size(); l++)
          {  working_queue=vec[l];
            for( int x=0;x< vec[l].size();x++){
            temp=working_queue.front();
            trace[temp][i]='.';
            working_queue.pop();
            working_queue.push(temp);
          }
          
          }
      
       if((p.remainingTime[pturn]==0)|| (currentQ==0)){
        if(p.remainingTime[pturn]==0){
          p.completionTime[pturn]=i;
          p.turnAroundTime[pturn]=p.completionTime[pturn]-p.arrivalTime[pturn];
          p.normTurn[pturn]=p.turnAroundTime[pturn]/p.serviceTime[pturn];
            // cerr << "this is sum2:" << sum2<< "\n";
          sum1=sum1+p.turnAroundTime[pturn];
          sum2=sum2+p.normTurn[pturn];
          p.tatMean[0]=sum1/p.noOfProcess;
          p.normMean[0]=sum2/p.noOfProcess;
              for (int z=0 ; z< vec.size();z++){
              if(vec[z].size()!=0){
                   pturn=vec[z].front();
                   vec[z].pop();
                  currentQ=pow(2,p.preempt[pturn]);
                  break;
              }
            }

        }
        else{
          if(vec[currentp].size()==0 && p.remainingTime[0]>0){
            currentQ=pow(2,p.preempt[pturn]);
          }
          else{
            p.preempt[pturn]=p.preempt[pturn]+1;
            currentp=p.preempt[pturn];
            vec.push_back(queue<int>());
            vec[currentp].push(pturn);
            trace[pturn][i]='.';
            for (int z=0 ; z< vec.size();z++){
              if(vec[z].size()!=0){
                   pturn=vec[z].front();
                   vec[z].pop();
                  currentQ=pow(2,p.preempt[pturn]);
                  break;
              }
            }
         
          }
  
          
        }
      }
      //  cout << "This is time : " << i << "pturn is: " << pturn << endl;
      trace[pturn][i]='*';
      p.remainingTime[pturn]=p.remainingTime[pturn]-1;
      currentQ=currentQ-1;
  }
  //if mode is trace
  if(m==1){
  cout << "FB-2i" <<" ";
  for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------"<< "\n\n";
  }

}
//---------------------------AGING-----------------------------
void aging (process p, int quantum){
  vector <int> ready;
  vector <int> currentp;
  int pturn=-1;
  int temp;
  int number= (int)p.noOfProcess;
  int currentQ=quantum;
  int max;
  int maxindex;
  char trace[number][p.time[0]+1];
  for(int i=0; i<number;i++){
    for(int j=0;j<p.time[0] ;j++){
     trace[i][j]=' ';
    }
  }

  
  for ( int i=0; i <p.time[0]+1 ;i++){
    max=0;
    for (int j= 0; j< p.noOfProcess;j++){
      if(p.arrivalTime[j]==i){
        ready.push_back(j);
        currentp.push_back(p.priority[j]+1);
        
      }
      } 
         
   //cerr << " time : " << i << "\n";
   //cerr << "priorties";
          for(int k =0;k < ready.size() ;k++){
             
            currentp.at(k)=currentp.at(k);
            p.waitingTime[k]=p.waitingTime[k];
       //     cerr << currentp.at(k) << " ";
        }
     //   cerr  << " \n";
             if(i==0){
        pturn=ready.at(0);

      } 
    
 
       if(currentQ==0){
        
        
          if(ready.size()==1 ){
           currentp.at(0)=p.priority[0];
            currentQ=quantum;
            
          
          }
          else{
             trace[pturn][i]='.';  
             
            
            maxindex =distance(begin(currentp),max_element(begin(currentp),end(currentp)));
            max=*max_element(begin(currentp),end(currentp));
          for (int l = 0; l < ready.size(); l++)
          {
            if(max==currentp.at(l)){
              if(p.waitingTime[l]>p.waitingTime[maxindex]){
                maxindex=ready.at(l);
              }
            }
          
          }
           
            
            pturn=maxindex;
            currentQ=quantum;
                    for(int k =0;k < ready.size() ;k++){
             if(ready.at(k)!=pturn){
            currentp.at(k)=currentp.at(k)+1;
            p.waitingTime[k]=p.waitingTime[k]+1;}
            else{
              p.waitingTime[k]=0;
            }
            
        }
            
            
          }
          
        
      }
   //cout << "max priorty:" << max << "\n";
   //cout << " " << p.processList[maxindex] << "\n";
    trace[pturn][i]='*';
      currentQ=currentQ-1;
       currentp.at(pturn)=p.priority[pturn];
       p.waitingTime[pturn]=0;
           for (int l = 0; l < ready.size(); l++)
          {
            
            if(ready.at(l)!=pturn){
              trace[l][i]='.';
            }
            
            
          }
      
  }
  //if mode is trace
  
  cout << "Aging ";
  for(int t=0 ;t <=p.time[0];t++){
    cout<<t%10<<" ";
  }
  cout << "\n";
  cout << "------------------------------------------------"<< "\n";
  for(int i=0; i<number;i++){
    cout << p.processList[i]<<"     ";
    for(int j=0;j<p.time[0] ;j++){
      cout << "|" << trace[i][j];
    }
    cout << "| \n";
  }
  cout << "------------------------------------------------\n\n";
  

}

//printing stastics 
void stats(process p){
  
  float sum2=0;
  float sum1=0;
  for (int k = 0; k < p.noOfProcess; k++ ) {
    sum1=sum1+p.normTurn[k];
    p.normMean[0]=sum1/p.noOfProcess;
     sum2=sum2+p.turnAroundTime[k];
    p.tatMean[0]=sum2/p.noOfProcess;
          
   }
  

 cout << "Process  ";
   for (int i = 0; i < p.noOfProcess; i++ ) {
    cout << "  |  " << p.processList[i];
    
   }
   cout << "  |\n";
   cout << "Arrival  ";
   for (int i = 0; i < p.noOfProcess; i++ ) {
    if(p.arrivalTime[i]>9){
     cout << "  | " << int(p.arrivalTime[i]); 
    }
    else cout << "  |  " << int(p.arrivalTime[i]);
    
   }
   cout << "  |\n";
   cout << "Service  ";
   for (int i = 0; i < p.noOfProcess; i++ ) {
    if(p.serviceTime[i]>10){
     cout << "  | " << int(p.serviceTime[i]); 
    }
    else cout << "  |  " << int(p.serviceTime[i]);
    
   }
   cout << "  | Mean|\n";
   cout << "Finish   ";
   for (int i = 0; i < p.noOfProcess; i++ ) {
    if(p.completionTime[i]>9){
     cout << "  | " <<int(p.completionTime[i]); 
    }
    else cout << "  |  " << int(p.completionTime[i]);
    
   }
   cout << "  |-----|\n";
   cout << "Turnaround" << " |  ";
   for (int i = 0; i < p.noOfProcess; i++ ) {
    if(p.turnAroundTime[i+1]>9){
     cout << int(p.turnAroundTime[i]) << "  | ";  
    }
    
    else {
       if(i==p.noOfProcess-1 && p.tatMean[0]>9.99){
      cout << int(p.turnAroundTime[i] )<< "  |";
    }
    else{
      cout << int(p.turnAroundTime[i]) << "  | ";} 
    if(i<p.noOfProcess-1){
      cout << " ";
    }}
    
   }
   cout << fixed << setprecision(2) << p.tatMean[0] << "|\n";
   cout << "NormTurn   ";
   for (int i = 0; i < p.noOfProcess; i++ ) {

    cout << "| " << fixed << setprecision(2) <<  p.normTurn[i];
    
   }
   cout << "| " << fixed << setprecision(2) << p.normMean[0] << "|\n\n";
}
void parsing(){
  
    vector <string> inputarr;
    char buffer[BUFFERSIZE];
    while( fgets(buffer, BUFFERSIZE , stdin)){
    inputarr.push_back(buffer);
     
   
    }
    string type =inputarr.at(0).substr(0,5);
    string technique=inputarr.at(1);
    int policy=stoi(inputarr.at(1));
    int NoOfTechniques=technique.length();  
    int  NoOfprocesses =stoi(inputarr.at(3));
  
    process p(NoOfprocesses);
    p.time[0]=stoi(inputarr.at(2));
   // cerr << p.time[0] << "\n";
    p.noOfProcess=NoOfprocesses;
    for(int j =0 ; j< NoOfprocesses ; j++){
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
     
      
      
    }
    for(int x=0;x<NoOfTechniques-1;x=x+2){
      int q;
      int y;   
       y = int(technique[x])-48 ;
      //  cout << "This is y: "<<y<<endl;
       if(y==2 || y==8){
        x=x+2;
        q=int(technique[x]-48);
       }

    switch (y)
    {
    case 1:
    for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.turnAroundTime[j]=0;
      p.normMean[0]=0;
      p.tatMean[0]=0; 
      
    }
      if(type.compare("stats")==0){
        fcfs(p,0);
        cout << "FCFS\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        fcfs(p,1);
      }

      break;
    case 2:
    for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.turnAroundTime[j]=0;   
    }     
      if(type.compare("stats")==0){
            RR(p,q,0);
        cout << "RR-"<< q <<"\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        RR(p,q,1);
      }
      break;
    case 3:
    for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.turnAroundTime[j]=0;
       
     
    }
     if(type.compare("stats")==0){
            SPN(p,0);
        cout << "SPN"<<"\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        SPN(p,1);
      }
      break;
    case 4:
    for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.turnAroundTime[j]=0;  
     
    }
     if(type.compare("stats")==0){
            SRT(p,0);
        cout << "SRT"<<"\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        SRT(p,1);
      }
      break;
    case 5:
    for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.turnAroundTime[j]=0;  
    }    
      if(type.compare("stats")==0){
        HRRN(p,0);
        cout << "HRRN"<<"\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        HRRN(p,1);
      }
      break;
    case 6:
        for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.preempt[j]=0;
      p.turnAroundTime[j]=0;  
    }  
      if(type.compare("stats")==0){
        FF1(p,0);
        cout << "FB-1"<<"\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        FF1(p,1);
      }
      break;
    case 7:
      for(int j =0 ; j< NoOfprocesses ; j++){ 
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.serviceTime[j]=int(processDetail[4])-48;
      p.remainingTime[j]=int(processDetail[4])-48;
      p.normTurn[j]=0;
      p.turnAroundTime[j]=0;
      p.preempt[j]=0;  
    }  
      if(type.compare("stats")==0){
        FF2(p,0);
        cout << "FB-2i"<<"\n";
        stats(p);
      }
      else if(type.compare("trace")==0){
        FF2(p,1);
      }
      break;
   case 8:
   
      for(int j =0 ; j< NoOfprocesses ; j++){
      string processDetail =inputarr.at(4+j);
      p.processList[j]= processDetail[0];
      p.arrivalTime[j]=int(processDetail[2])-48;
      p.priority[j]=int(processDetail[4])-48;
      p.currentPriority[j]=int(processDetail[4])-48;
     
      
      
    }
    aging(p,q);
      break;
    
    default:
      break;
    }
    }

}
int main (int argc, char *argv[])
{   

    parsing();
}

