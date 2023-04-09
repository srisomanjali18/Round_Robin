#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int nop, i, time , remain, flag = 0, qt;
    int wt = 0 , tt = 0 , at[10], bt[10], rt[10];
    cout<<"Enter the total no of processes:"<<endl;
    cin>>nop;
    remain = nop;
    for(i=0; i < nop; i++)
    {
        cout << "Enter Arrival Time for Process " << i+1 << ":" <<endl;
        cin >> at[i];
        cout << "Enter Burst Time for Process " << i+1 << ":" <<endl;
        cin >> bt[i];
        rt[i] = bt[i];
    }
    cout << "Enter the Quantum Time :"<<endl;
    cin >> qt;
    cout << "\nGantt Chart:" << endl;
    for(time = 0 ; remain != 0; )
    {
        if(rt[i] <= qt && rt[i] > 0)
        {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if(rt[i] > 0)
        {
            rt[i] -= qt;
            time += qt;
        }
        if(rt[i] == 0 && flag == 1)
        {
            remain--;
            cout<<"| P[" << i + 1 << "] ";
            wt += time - at[i] - bt[i];
            tt += time - at[i];
            flag = 0;
        }
        if(i == nop - 1)
            i = 0;
        else if(at[i + 1] <= time)
            i++;
        else
            i = 0;
    }
    cout << "|\n\n";
    cout << "Process\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time" << endl;
    for(i=0; i<nop; i++)
    {
        cout<<"P["<<i+1<<"]\t"<<setw(8)<<at[i]<<setw(16)<<bt[i]<<setw(21)<<time-at[i]<<setw(20)<<time-at[i]-bt[i]<<endl;
    }
    cout << "Average Waiting Time= " << wt * 1.0 / nop << endl;
    cout << "Average Turnaround Time = " << tt * 1.0 / nop << endl;
    return 0;
}