// Round Robin Scheduling Algorithm for 6 processes
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n, i, j, k, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, at[10], bt[10], rt[10];
    cout << "Enter Total Process:" << endl;
    cin >> n;
    remain = n;
    for (i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time  Process Number " << i + 1 << endl;
         cout << "Burst Time for Process Process Number " << i+1 << endl;
        cin >> at[i];
        cin >> bt[i];
        rt[i] = bt[i];
    }
    cout << "Enter Time Quantum:" << endl;
    cin >> time_quantum;
    cout << "Process ID\t\tArrival Time\t Burst Time\t Turnaround Time\t Waiting Time" << endl;
    for (time = 0, i = 0; remain != 0;)
    {
        if (rt[i] <= time_quantum && rt[i] > 0)
        {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if (rt[i] > 0)
        {
            rt[i] -= time_quantum;
            time += time_quantum;
        }
        if (rt[i] == 0 && flag == 1)
        {
            remain--;
            cout << "Process[" << i + 1 << "]\t\t" << at[i] << "\t\t" << bt[i] << "\t\t " << time - at[i] << "\t\t\t " << time - at[i] - bt[i] << endl;
            wait_time += time - at[i] - bt[i];
            turnaround_time += time - at[i];
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (at[i + 1] <= time)
            i++;
        else
            i = 0;
    }
    cout << "Average Waiting Time= " << wait_time * 1.0 / n << endl;
    cout << "Avg Turnaround Time = " << turnaround_time * 1.0 / n << endl;
    return 0;
}
