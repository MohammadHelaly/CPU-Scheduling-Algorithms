#include <iostream>
#include <queue>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct process
    {
        string procc_name;
        int arr_time;
        int serv_time;
        string answer="";
        int turn_time;
        float norm_time;
        int fin_time;
        int wait_time=0;
        float ratiow=0.0;
        int countfeed=0;
        int order;
        int feedquantum=1;
        int rrquantum;
        int priority;
};

struct compareremainingtime{
    bool operator()(process const& p1, process const& p2)
    {
        if (p1.serv_time!=p2.serv_time)
        return p1.serv_time > p2.serv_time;
        else
            return p1.order>p2.order;
    }
};

struct compareremainingtime2{
    bool operator()(process const& p1, process const& p2)
    {
        if (p1.serv_time!=p2.serv_time)
        return p1.serv_time < p2.serv_time;
        else
            return p1.order>p2.order;
    }
};

struct comparecountfeed{
    bool operator()(process const& p1, process const& p2)
    {
        if (p1.countfeed!=p2.countfeed)
        return p1.countfeed > p2.countfeed;
        else
            return p1.order>p2.order;
    }
};

struct compareratiow{
    bool operator()(process const& p1, process const& p2)
    {
        if(p1.ratiow!=p2.ratiow)
        return p1.ratiow > p2.ratiow;
        else
            return p1.order>p2.order;
    }
};

void trace(int length,vector <process> x,int n)
{//,string type){
    int counter=6;
    string ans;
    int i,j;
    for(i=0;i<=length;i++){
        cout<<i%10<<" ";
        counter++;
        counter++;
    }
    cout<<endl;
    for(i=0;i<counter;i++)
        cout<<"-";
        cout<<endl;
    for(i=0;i<n;i++){
            ans=x[i].answer;
        cout<<x[i].procc_name<<"     ";
        for(j=0;j<length;j++){
                cout<<"|"<<ans[j];
        }
        cout<<"| \n";
    }
        for(i=0;i<counter;i++)
        cout<<"-";
        cout<<endl<<endl;
}

void stats(int length,vector <process>x,int n,float mean_turn,float mean_norm_turn)
{
    cout<<"Process"<<"    |";

    for (int i=0; i<n; i++)
    {
        cout<<"  "<<x[i].procc_name<<"  ";
        printf("|");
    }
    cout<<endl;
    cout<<"Arrival"<<"    |";
       for (int i=0; i<n; i++)
    {
        if(x[i].arr_time<=9)
        {
            printf("  %d  ",x[i].arr_time);
            printf("|");
        }
        else if(x[i].arr_time>9)
        {
            printf(" %d  ",x[i].arr_time);
            printf("|");
        }
    }
    cout<<endl;
    cout<<"Service"<<"    |";
    for (int i=0; i<n; i++)
    {
        if(x[i].serv_time<=9)
        {
            printf("  %d  ",x[i].serv_time);
            printf("|");
        }
        else if(x[i].serv_time>9)
        {
            printf(" %d  ",x[i].serv_time);
            printf("|");
        }
    }
    cout<<" Mean|"<<endl;
    cout<<"Finish"<<"     |";
    for (int i=0; i<n; i++)
    {
        if(x[i].fin_time<=9)
        {
            printf("  %d  ",x[i].fin_time);
            printf("|");
        }
        else if(x[i].fin_time>9)
        {
            printf(" %d  ",x[i].fin_time);
            printf("|");
        }
    }
    cout<<"-----|"<<endl;
    cout<<"Turnaround"<<" |";
    for (int i=0; i<n; i++)
    {
        if(x[i].turn_time<=9)
        {
            printf("  %d  ",x[i].turn_time);
            printf("|");
        }
        else if(x[i].turn_time>9)
        {
            printf(" %d  ",x[i].turn_time);
            printf("|");
        }
    }
    if (mean_turn<10)
        printf(" %.2f",mean_turn);
    else if (mean_turn>=10)
        printf("%.2f",mean_turn);
    printf("|\n");
    cout<<"NormTurn"<<"   |";
        for (int i=0; i<n; i++)
    {
        if (x[i].norm_time<10)
        {
            printf(" %.2f",x[i].norm_time);
            printf("|");
        }
        else if(x[i].norm_time>=10)
        {
            printf("%.2f",x[i].norm_time);
            printf("|");
        }
        }
    if (mean_norm_turn<10)
        printf(" %.2f",mean_norm_turn);
    else if (mean_norm_turn>=10)
        printf("%.2f",mean_norm_turn);
    printf("|\n");
    cout<<endl;
}

void statsFCFS(int length,vector <process>x,int n)  //length=total time, x=vector of processes, n=number of elements
{
    int i,j;
    process temp;
    int sum1=0;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(x[j].arr_time>x[j+1].arr_time)
            {
                temp=x[j];
                x[j]=x[j+1];
                x[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
       sum1=sum1+x[i].serv_time;
       x[i].fin_time = sum1;
       x[i].turn_time = x[i].fin_time-x[i].arr_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    cout<<"FCFS"<<endl;
   stats(length,x,n,mean_turn,mean_norm_turn);
}

void traceFCFS(int length,vector <process>x,int n)  //length=total time, x=vector of processes, n=number of elements
{
    int i,j,sum=0;
    process temp;
    string temp2;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(x[j].arr_time>x[j+1].arr_time)
            {
                temp=x[j];
                x[j]=x[j+1];
                x[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
       sum=sum+x[i].serv_time;
       x[i].fin_time = sum;
       x[i].turn_time = x[i].fin_time-x[i].arr_time;
       x[i].norm_time = x[i].turn_time/x[i].serv_time;
    }

    for(i=0;i<length;i++)
    {
        if(i>=x[0].arr_time && i<x[0].fin_time)
        {
            temp2="*";
            x[0].answer.append(temp2);
        }
        else if(i<x[0].arr_time || i>=x[0].fin_time)
        {
            temp2=" ";
            x[0].answer.append(temp2);
        }
    }
    for(j=1;j<n;j++)
    {
        for(i=0;i<length;i++)
        {
            if(i<x[j].arr_time || i>=x[j].fin_time)
            {
                temp2=" ";
                x[j].answer.append(temp2);
            }
            else if(i<x[j-1].fin_time)
            {
                temp2=".";
                x[j].answer.append(temp2);
            }
            else if(i>x[j].arr_time && i<x[j].fin_time && i>=x[j-1].fin_time)
            {
                temp2="*";
                x[j].answer.append(temp2);
            }
        }
    }
    cout<<"FCFS  ";
    trace(length,x,n);
}

void statsRR(int length,vector <process>x,int n,int quantum)  //length=total time, x=vector of processes, n=number of elements
{
    queue<process> q;
    string temp1,temp2,temp3;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    process currentprocess;
    currentprocess.rrquantum=0;
    int i,j=0,sum=0,m=0,flag=0,flag2;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
        x[i].rrquantum=quantum;
    }
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
    q.push(x[j]);
    j++;
    }
    if (flag==1){
            currentprocess.rrquantum=quantum;
            q.push(currentprocess);
            currentprocess=q.front();
            q.pop();
            flag=0;
    }
    else{
    if(!q.empty() && currentprocess.rrquantum==0 || (!q.empty() && currentprocess.serv_time<=0))
    {
        currentprocess=q.front();
        q.pop();
    }
    }
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    currentprocess.rrquantum--;
    if (currentprocess.serv_time>0 && currentprocess.rrquantum==0){
        if(q.empty() && x[j].arr_time!=(i+1)){
                currentprocess.rrquantum=quantum;
            //q.push(currentprocess);
                }
        else flag=1;
                }
    }
    for(j=0;j<n;j++)
    {
        int cnt=0;
        string comp=x[j].answer;
        temp1="*";
        temp3=".";
        for(i=0;i<length;i++)
        {
            if (comp[i]== '.' || comp[i]== '*')
            {
                cnt=cnt+1;
            }
        }
        x[j].turn_time=cnt;
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    for(i=0;i<n;i++)
    {
       x[i].fin_time = x[i].arr_time+x[i].turn_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    printf("RR-%d\n",quantum);
    stats(length,x,n,mean_turn,mean_norm_turn);
}

void traceRR(int length,vector <process>x,int n,int quantum)
{
    queue<process> q;
    string temp2;
    process currentprocess;
    currentprocess.rrquantum=0;
    int i,j=0,sum=0,m=0,flag=0,flag2;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
        x[i].rrquantum=quantum;
    }
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
    q.push(x[j]);
    j++;
    }
    if (flag==1){
            currentprocess.rrquantum=quantum;
            q.push(currentprocess);
            currentprocess=q.front();
            q.pop();
            flag=0;
    }
    else{
    if(!q.empty() && currentprocess.rrquantum==0 || (!q.empty() && currentprocess.serv_time<=0))
    {
        currentprocess=q.front();
        q.pop();
    }
    }
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    currentprocess.rrquantum--;
    if (currentprocess.serv_time>0 && currentprocess.rrquantum==0){
        if(q.empty() && x[j].arr_time!=(i+1)){
                currentprocess.rrquantum=quantum;
            //q.push(currentprocess);
                }
        else flag=1;
                }
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    printf("RR-%d  ",quantum);
    trace(length,x,n);
}

void statsSPN(int length,vector <process>x,int n)
{

    string temp1,temp2,temp3;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    priority_queue<process,vector<process>,compareremainingtime>q;
    process currentprocess;
    int i,j=0,sum=0,m=0;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++)
    {
        while(x[j].arr_time==i)
        {
            q.push(x[j]);
            j++;
        }
        if (i>=sum)
        {
            sum+=q.top().serv_time;
            currentprocess=q.top();
            q.pop();
        }
        for(m=0;m<n;m++)
        {
        if (x[m].procc_name==currentprocess.procc_name)
        {
            x[m].serv_time--;
            temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0)
        {
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else
        {
            temp2=".";
            x[m].answer.append(temp2);
        }
    }
    }
    for(j=0;j<n;j++)
    {
        int cnt=0;
        string comp=x[j].answer;
        temp1="*";
        temp3=".";
        for(i=0;i<length;i++)
        {
            if (comp[i]== '.' || comp[i]== '*')
            {
                cnt=cnt+1;
            }
        }
        x[j].turn_time=cnt;
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    for(i=0;i<n;i++)
    {
       x[i].fin_time = x[i].arr_time+x[i].turn_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    cout<<"SPN"<<endl;
    stats(length,x,n,mean_turn,mean_norm_turn);
}

void traceSPN(int length,vector <process>x,int n)  //length=total time, x=vector of processes, n=number of elements
{

    priority_queue<process,vector<process>,compareremainingtime>q;
    string temp2;
    process currentprocess;
    int i,j=0,sum=0,m=0;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
    q.push(x[j]);
    j++;
    }
    if (i>=sum){
        sum+=q.top().serv_time;
        currentprocess=q.top();
        q.pop();
    }
    for(m=0;m<n;m++)
    {
        if (x[m].procc_name==currentprocess.procc_name)
        {
            x[m].serv_time--;
            temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0)
        {
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else
        {
            temp2=".";
            x[m].answer.append(temp2);
        }
    }
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    cout<<"SPN   ";
    trace(length,x,n);
}

void statsSRT(int length,vector <process>x,int n)
{
    priority_queue<process,vector<process>,compareremainingtime>q;
    string temp1,temp2,temp3;
    process currentprocess;
    process temp;
    int i,j=0,sum=0,m=0;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
    q.push(x[j]);
    j++;
    }
    if(!q.empty()){
        currentprocess=q.top();
        q.pop();
    }
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    if (currentprocess.serv_time>0)
        q.push(currentprocess);
    }
    for(j=0;j<n;j++)
    {
        int cnt=0;
        string comp=x[j].answer;
        temp1="*";
        temp3=".";
        for(i=0;i<length;i++)
        {
            if (comp[i]== '.' || comp[i]== '*')
            {
                cnt=cnt+1;
            }
        }
        x[j].turn_time=cnt;
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    for(i=0;i<n;i++)
    {
       x[i].fin_time = x[i].arr_time+x[i].turn_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    cout<<"SRT"<<endl;
    stats(length,x,n,mean_turn,mean_norm_turn);
}

void traceSRT(int length,vector <process>x,int n)  //length=total time, x=vector of processes, n=number of elements
{
    priority_queue<process,vector<process>,compareremainingtime>q;
    string temp2;
    process currentprocess;
    process temp;
    int i,j=0,sum=0,m=0;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
    q.push(x[j]);
    j++;
    }
    if(!q.empty()){
        currentprocess=q.top();
        q.pop();
    }
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    if (currentprocess.serv_time>0)
        q.push(currentprocess);
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    cout<<"SRT   ";
    trace(length,x,n);
}

void statsHRRN(int length,vector <process>x,int n)
{
    vector<process> v;
    string temp1,temp2,temp3;
    process currentprocess;//={"Dummy",-100,-100};
    currentprocess.arr_time=-100;
    int i,j=0,sum=0,m=0,y=0,k,index;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++)
    {
    while(x[j].arr_time==i)
    {
                v.push_back(x[j]);
                j++;
    }
    if(currentprocess.arr_time==-100 || currentprocess.serv_time==0){
        float mx = -1.0;
        for (k=0;k<v.size();k++)
            {
            float temp = v[k].ratiow;
            if (mx<temp){
                index=k;
                mx=temp;
            }
            }
            currentprocess=v[index];
            v[index].ratiow=-10.0;
            }
    //else{
        for (k=0;k<v.size();k++){
            if (v[k].ratiow==-10.0)
                continue;
            else{
                v[k].wait_time=v[k].wait_time+1;
                //cout<<"process name:   "<<v[k].procc_name<<"    with wait_time="<<v[k].wait_time<<endl;
                //cout<<"process name:   "<<x[k].procc_name<<"    with serv_time="<<x[k].serv_time<<endl;
                v[k].ratiow=(float)(v[k].wait_time+v[k].serv_time)/(float)v[k].serv_time;
             //   cout<<"process name:   "<<v[k].procc_name<<"    with value ratio="<<v[k].ratiow<<endl;
            }
        }
    //}
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
            //cout<<"decreasing process"<<"  "<<x[m].procc_name<<endl;
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    }
    for(j=0;j<n;j++)
    {
        int cnt=0;
        string comp=x[j].answer;
        temp1="*";
        temp3=".";
        for(i=0;i<length;i++)
        {
            if (comp[i]== '.' || comp[i]== '*')
            {
                cnt=cnt+1;
            }
        }
        x[j].turn_time=cnt;
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    for(i=0;i<n;i++)
    {
       x[i].fin_time = x[i].arr_time+x[i].turn_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    cout<<"HRRN"<<endl;
    stats(length,x,n,mean_turn,mean_norm_turn);
}

void traceHRRN(int length,vector <process>x,int n)  //length=total time, x=vector of processes, n=number of elements
{
    vector<process> v;
    string temp2;
    process currentprocess;//={"Dummy",-100,-100};
    currentprocess.arr_time=-100;
    int i,j=0,sum=0,m=0,y=0,k,index;
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
                v.push_back(x[j]);
                j++;
    }
    if(currentprocess.arr_time==-100 || currentprocess.serv_time==0){
        float mx = -1.0;
        for (k=0;k<v.size();k++)
            {
            float temp = v[k].ratiow;
            if (mx<temp){
                index=k;
                mx=temp;
            }
            }
            currentprocess=v[index];
            v[index].ratiow=-10.0;
            }
    //else{
        for (k=0;k<v.size();k++){
            if (v[k].ratiow==-10.0)
                continue;
            else{
                v[k].wait_time=v[k].wait_time+1;
                //cout<<"process name:   "<<v[k].procc_name<<"    with wait_time="<<v[k].wait_time<<endl;
                //cout<<"process name:   "<<x[k].procc_name<<"    with serv_time="<<x[k].serv_time<<endl;
                v[k].ratiow=(float)(v[k].wait_time+v[k].serv_time)/(float)v[k].serv_time;
           //     cout<<"process name:   "<<v[k].procc_name<<"    with value ratio="<<v[k].ratiow<<endl;
            }
        }
    //}
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
         //   cout<<"decreasing process"<<"  "<<x[m].procc_name<<endl;
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    }
    cout<<"HRRN  ";
    trace(length,x,n);
}

void statsfeedback(int length,vector <process>x,int n)
{
    priority_queue<process,vector<process>,comparecountfeed>q;
    process currentprocess;
    string temp1,temp2,temp3;
    int i,j=0,k,m,entered;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
             //cout<<"ITERATION   "<<i<<endl;
            entered=0;
        while(x[j].arr_time==i){
            entered=1;
        q.push(x[j]);
        //cout<<"pushed  "<<x[j].procc_name<<endl;
        j++;
        }
    if(!q.empty()){
        currentprocess=q.top();
       // cout<<"current process:  "<<currentprocess.procc_name<<"    with countfeed="<<currentprocess.countfeed<<endl;
        q.pop();
       // cout<<"popped  "<<currentprocess.procc_name<<endl;
    }
        //if(!q.empty()&& entered==1){
         //   currentprocess.countfeed++;
          //  q.push(currentprocess);
           // currentprocess=q.top();
          //  cout<<"AFTER IF current process:  "<<currentprocess.procc_name<<"    with countfeed="<<currentprocess.countfeed<<endl;
          //  q.pop();
        //}
    //}
        for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    if (currentprocess.serv_time>0){
            if (x[j].arr_time==i+1)
            currentprocess.countfeed++;
        else if(!q.empty())
        currentprocess.countfeed++;
        q.push(currentprocess);
         //   cout<<"reentering process:  "<<currentprocess.procc_name<<"   with countfeed="<<currentprocess.countfeed<<endl;
    }
    }
    for(j=0;j<n;j++)
    {
        int cnt=0;
        string comp=x[j].answer;
        temp1="*";
        temp3=".";
        for(i=0;i<length;i++)
        {
            if (comp[i]== '.' || comp[i]== '*')
            {
                cnt=cnt+1;
            }
        }
        x[j].turn_time=cnt;
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    for(i=0;i<n;i++)
    {
       x[i].fin_time = x[i].arr_time+x[i].turn_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    cout<<"FB-1"<<endl;
    stats(length,x,n,mean_turn,mean_norm_turn);
}

void tracefeedback(int length,vector <process>x,int n){
    priority_queue<process,vector<process>,comparecountfeed>q;
    process currentprocess;
    string temp2;
    int i,j=0,k,m,entered;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
             //cout<<"ITERATION   "<<i<<endl;
            entered=0;
        while(x[j].arr_time==i){
            entered=1;
        q.push(x[j]);
        //cout<<"pushed  "<<x[j].procc_name<<endl;
        j++;
        }
    if(!q.empty()){
        currentprocess=q.top();
       // cout<<"current process:  "<<currentprocess.procc_name<<"    with countfeed="<<currentprocess.countfeed<<endl;
        q.pop();
       // cout<<"popped  "<<currentprocess.procc_name<<endl;
    }
        //if(!q.empty()&& entered==1){
         //   currentprocess.countfeed++;
          //  q.push(currentprocess);
           // currentprocess=q.top();
          //  cout<<"AFTER IF current process:  "<<currentprocess.procc_name<<"    with countfeed="<<currentprocess.countfeed<<endl;
          //  q.pop();
        //}
    //}
        for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    if (currentprocess.serv_time>0){
            if (x[j].arr_time==i+1)
            currentprocess.countfeed++;
        else if(!q.empty())
        currentprocess.countfeed++;
        q.push(currentprocess);
         //   cout<<"reentering process:  "<<currentprocess.procc_name<<"   with countfeed="<<currentprocess.countfeed<<endl;
    }
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    cout<<"FB-1  ";
        trace(length,x,n);

}

void statsfeedback2i(int length,vector <process>x,int n){
    priority_queue<process,vector<process>,comparecountfeed>q;
    process currentprocess;
    int first=1;
    float sum2=0,sum3=0;
    float mean_turn,mean_norm_turn;
    string temp1,temp2,temp3;
    int i,j=0,k,m,entered;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
            //entered=0;
        while(x[j].arr_time==i){
           // entered=1;
        q.push(x[j]);
        j++;
        }
    if(!q.empty()){
            if(first==1){
                currentprocess=q.top();
                q.pop();
                first=0;
            }
            if(currentprocess.serv_time<=0){
                currentprocess=q.top();
                q.pop();
            }
        else if(currentprocess.feedquantum<=0){
            currentprocess.feedquantum=currentprocess.countfeed*2;
            process last=currentprocess;
            q.push(currentprocess);
            currentprocess=q.top();
            q.pop();
            if(last.procc_name==currentprocess.procc_name){
                  // queue<process>hold;
                   // while(last.procc_name==currentprocess.procc_name){
                    //                        hold.push(last);
                     //                       currentprocess=q.top();
                      //                      q.pop();
                    //}
                currentprocess=q.top();
                q.pop();
                q.push(last);
            }
        }
    }
        for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    if(!q.empty() || x[j].arr_time==i+1)
    currentprocess.feedquantum--;
    if (currentprocess.serv_time>0){
            if (x[j].arr_time==i+1 && currentprocess.feedquantum<=0){
            currentprocess.countfeed++;
            }
        else if(!q.empty()&&currentprocess.feedquantum<=0){
        currentprocess.countfeed++;
        //q.push(currentprocess);
        }
    }
    }
     for(j=0;j<n;j++)
    {
        int cnt=0;
        string comp=x[j].answer;
        temp1="*";
        temp3=".";
        for(i=0;i<length;i++)
        {
            if (comp[i]== '.' || comp[i]== '*')
            {
                cnt=cnt+1;
            }
        }
        x[j].turn_time=cnt;
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    for(i=0;i<n;i++)
    {
       x[i].fin_time = x[i].arr_time+x[i].turn_time;
       x[i].norm_time = (float)x[i].turn_time/(float)x[i].serv_time;
    }
    for(i=0;i<n;i++)
    {
       sum2=sum2+x[i].turn_time;
       mean_turn=(float)sum2/(float)n;
       sum3=sum3+(float)x[i].norm_time;
       mean_norm_turn=(float)sum3/(float)n;
    }
    cout<<"FB-2i"<<endl;
    stats(length,x,n,mean_turn,mean_norm_turn);
}

void tracefeedback2i(int length,vector <process>x,int n){
    priority_queue<process,vector<process>,comparecountfeed>q;
    process currentprocess;
    int first=1;
    string temp2;
    int i,j=0,k,m,entered;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
    }
    for(i=0;i<length;i++){
            //entered=0;
        while(x[j].arr_time==i){
           // entered=1;
        q.push(x[j]);
        j++;
        }
    if(!q.empty()){
            if(first==1){
                currentprocess=q.top();
                q.pop();
                first=0;
            }
            if(currentprocess.serv_time<=0){
                currentprocess=q.top();
                q.pop();
            }
        else if(currentprocess.feedquantum<=0){
            currentprocess.feedquantum=currentprocess.countfeed*2;
            process last=currentprocess;
            q.push(currentprocess);
            currentprocess=q.top();
            q.pop();
            if(last.procc_name==currentprocess.procc_name){
                  // queue<process>hold;
                   // while(last.procc_name==currentprocess.procc_name){
                    //                        hold.push(last);
                     //                       currentprocess=q.top();
                      //                      q.pop();
                    //}
                currentprocess=q.top();
                q.pop();
                q.push(last);
            }
        }
    }
        for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                x[m].serv_time--;
                currentprocess.serv_time--;
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i || x[m].serv_time<=0){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
    if(!q.empty() || x[j].arr_time==i+1)
    currentprocess.feedquantum--;
    if (currentprocess.serv_time>0){
            if (x[j].arr_time==i+1 && currentprocess.feedquantum<=0){
            currentprocess.countfeed++;
            }
        else if(!q.empty()&&currentprocess.feedquantum<=0){
        currentprocess.countfeed++;
        //q.push(currentprocess);
        }
    }
    }
    for(i=0;i<n;i++)
    {
        x[i].serv_time=talfee2[i];
    }
    cout<<"FB-2i ";
    trace(length,x,n);
}

void statsaging(int length,vector <process>x,int n,int quantum){
}

void traceaging(int length,vector <process>x,int n,int quantum){
    priority_queue<process,vector<process>,compareremainingtime2>q;
    queue<process> updating;
    string temp2;
    process currentprocess;
    process updatepriority;
    currentprocess.rrquantum=0;
    currentprocess.procc_name="Dummy";
    int i,j=0,sum=0,m=0,flag=0,flag2,h=0;
    vector <int> talfee2(n);
    for(i=0;i<n;i++)
    {
        talfee2[i]=x[i].serv_time;
        x[i].rrquantum=quantum;
    }
    for(i=0;i<length;i++){
    while(x[j].arr_time==i){
      //      cout<<"pushing "<<x[j].procc_name<<endl;
    q.push(x[j]);
    j++;
    }
    //cout<<"iteration "<<i<<endl;
    if(i%quantum==0){
        //    cout<<"updating"<<endl;
    for(h=0;h<q.size();h++){
        updatepriority=q.top();
        q.pop();
        updatepriority.serv_time++;
        updating.push(updatepriority);
    }
    for(h=0;h<updating.size();h++){
        updatepriority=updating.front();
        updating.pop();
        q.push(updatepriority);
    }
    }
   // if (flag==1){
    //        currentprocess.rrquantum=quantum;
     //       q.push(currentprocess);
      //      currentprocess=q.top();
       //     for(h=0;h<n;h++){
        //    if (currentprocess.procc_name==x[h].procc_name)
         //       currentprocess.serv_time=talfee2[h];
          //  }
           // q.pop();
            //flag=0;
    //}
    //else{
    if(!q.empty() && currentprocess.rrquantum<=0)
    {
      //  cout<<"process priority= "<<currentprocess.serv_time<<endl;
        currentprocess.rrquantum=quantum;
        if(currentprocess.procc_name!="Dummy")
        q.push(currentprocess);
        currentprocess=q.top();
        q.pop();
        for(h=0;h<n;h++){
            if (currentprocess.procc_name==x[h].procc_name)
                currentprocess.serv_time=talfee2[h];
        }
    //    cout<<"current process= "<<currentprocess.procc_name<<endl;
    }
    for(m=0;m<n;m++){
        if (x[m].procc_name==currentprocess.procc_name){
                temp2="*";
            x[m].answer.append(temp2);
        }
        else if (x[m].arr_time>i){
            temp2=" ";
            x[m].answer.append(temp2);
        }
        else{
                temp2=".";
            x[m].answer.append(temp2);
        }
    }
  //  cout<<"BEFORE UPDATING QUANTUM= "<<currentprocess.rrquantum<<endl;
    currentprocess.rrquantum--;
  //  cout<<"AFTER UPDATING QUANTUM="<<currentprocess.rrquantum<<endl;
   // if (currentprocess.rrquantum==0){
    //    if(q.empty() && x[j].arr_time!=(i+1)){
     //           currentprocess.rrquantum=quantum;
            //q.push(currentprocess);
      //          }
       // else flag=1;
       //         }
    }
    //for(i=0;i<n;i++)
    //{
     //   x[i].serv_time=talfee2[i];
    //}
    cout<<"Aging ";
    trace(length,x,n);
}

int main()
{
    ifstream file;
    string tors,type1,typetemp,typeQ,length,number,input,type,quant="0";
    int i=0,j=0;
    //file>>input;
    //file.open("input");

        cin>>tors;
        cin>>type1;
        cin>>length;
        cin>>number;
        int nu=count(type1.begin(),type1.end(),',');
        nu=nu+1;
        //cout<<nu<<endl;
        vector<string> types(nu);
        int n = stoi(number);
        vector<process>x(n);
        int l=stoi(length);
        for (int i = 0; i < n; i++)
        {
            cin>>input;
            stringstream ss(input);
            string pn,art,srt;
            getline(ss,pn,',');
            getline(ss,art,',');
            getline(ss,srt,',');
            int Art=stoi(art);
            int Srt=stoi(srt);
            x[i].procc_name=pn;
            x[i].arr_time=Art;
            x[i].serv_time=Srt;
            x[i].priority=Srt;
            x[i].order=i;
        }
     //   cout<<"here";
        types[0]=type1;
        if(type1.find(','))
        {
        stringstream ss(type1);
        while (!ss.eof())
        {//    cout<<"here"<<endl;
            getline(ss,typetemp,',');
            types[i]=typetemp;
            i++;
        }
        }
            //types[0]=type1;
           //     cout<<"here"<<endl;
           // cout<<"here"<<endl;
        for(j=0;j<nu;j++)
        {
        //cout<<"herefor";
        typeQ=types[j];
        type=typeQ;
        if(typeQ.find('-'))
        {
            stringstream ss(typeQ);
            getline(ss,type,'-');
            getline(ss,quant);
        }
        int quantum=stoi(quant);
        if(tors=="trace" && type=="1")
        {
         //   cout<<"here"<<endl;
            //cout<<type<<endl;
            traceFCFS(l,x,n);
            //cout<<"ffffff";
            //return 0;
        }
        else if(tors=="stats" && type=="1")
        {
            statsFCFS(l,x,n);
            //return 0;
        }
        else if(tors=="trace" && type=="2")
        {
            traceRR(l,x,n,quantum);
            //return 0;
        }
        else if(tors=="stats" && type=="2")
        {
            statsRR(l,x,n,quantum);
           // cout<<x[0].serv_time<<endl;
           // cout<<x[0].priority<<endl;
            //return 0;
        }
        else if(tors=="trace" && type=="3")
        {
            traceSPN(l,x,n);
           // return 0;
        }
        else if(tors=="stats" && type=="3")
        {
            statsSPN(l,x,n);
            //return 0;
        }
        else if(tors=="trace" && type=="4")
        {
            traceSRT(l,x,n);
            //return 0;
        }
        else if(tors=="stats" && type=="4")
        {
            statsSRT(l,x,n);
            //return 0;
        }
        else if(tors=="trace" && type=="5")
        {
            traceHRRN(l,x,n);
            //return 0;
        }
        else if(tors=="stats" && type=="5")
        {
            statsHRRN(l,x,n);
            //return 0;
        }
        else if(tors=="trace" && type=="6")
        {
            tracefeedback(l,x,n);
            //return 0;
        }
        else if(tors=="stats" && type=="6")
        {
            statsfeedback(l,x,n);
            //return 0;
        }
        else if(tors=="trace" && type=="7")
        {
            tracefeedback2i(l,x,n);
            //return 0;
        }
        else if(tors=="stats" && type=="7")
        {
            statsfeedback2i(l,x,n);
            //return 0;
        }
        else if(tors=="trace" && type=="8")
        {
            traceaging(l,x,n,quantum);
            //return 0;
        }
      //  else if(tors=="stats" && type=="8")
       // {
       //     statsaging(l,x,n,quantum);
            //return 0;
       // }
       // }
        }
    //cout<<"here";
    return 0;
}


