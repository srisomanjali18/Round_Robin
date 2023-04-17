#include <iostream>
#include <iomanip>
#include <random>
#include <thread>

using namespace std;

void schedulingAlgorithm(int nop, int qt, vector<int>& at, vector<int>& bt) {
    int i, time = 0, remain = nop, flag = 0;
    int wt = 0, tt = 0, rt[nop];
    for(i=0; i < nop; i++)
    {
        rt[i] = bt[i];
    }
    cout << "\nGantt Chart:" << endl;
    for(time = 0 ; remain != 0; )
    {
        for(i = 0; i < nop; i++)
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
        }
    }
    cout << "|\n\n";
    cout << "Process\tArrival Time\tBurst Time\tTurnaround Time\t\tWaiting Time" << endl;
    for(i=0; i<nop; i++)
    {
        cout<<"P["<<i+1<<"]"<<"\t\t"<<at[i]<<"\t\t"<<bt[i]<<"\t\t"<<time-at[i]<<"\t\t\t"<<time-at[i]-bt[i]<<endl;
    }
    cout << "Average Waiting Time= " << wt * 1.0 / nop << endl;
    cout << "Average Turnaround Time = " << tt * 1.0 / nop << endl;
}


int main()
{
    int nop, i, qt;
    int wt = 0 , tt = 0;
    cout<<"Enter the total no of processes:"<<endl;
    cin>>nop;

    // create a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> arrivalTimeDist(0, 10);
    uniform_int_distribution<> burstTimeDist(1, 5);

    vector<int> at(nop), bt(nop);
    for(i=0; i < nop; i++)
    {
        at[i] = arrivalTimeDist(gen); // generate random arrival time between 0 and 10
        bt[i] = burstTimeDist(gen);   // generate random CPU burst time between 1 and 5
    }
    cout << "Enter the Quantum Time :"<<endl;
    cin >> qt;

    // run the scheduling algorithm on a separate thread
    thread scheduler(schedulingAlgorithm, nop, qt, ref(at), ref(bt));

    scheduler.join(); // wait for the scheduling algorithm to finish

    return 0;
}