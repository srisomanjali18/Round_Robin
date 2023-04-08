#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>

using namespace std;

int main()
{
    int n, i, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, at[10], bt[10], rt[10];
    cout << "Enter Total Process:" << endl;
    cin >> n;
    remain = n;
    for (i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time  " << i + 1 << endl;
        cout << "Burst Time for Process " << i+1 << endl;
        cin >> at[i]; 
        cin >> bt[i];
        rt[i] = bt[i];
    }
    cout << "Enter Quantum Time:" << endl;
    cin >> time_quantum;

    queue<int> q;
    mutex q_mutex;

    for (i = 0; i < n; i++)
    {
        q_mutex.lock();
        q.push(i);
        q_mutex.unlock();
    }

    cout << "Process ID\t\tArrival Time\t Burst Time\t Turnaround Time\t Waiting Time" << endl;

    while (remain != 0)
    {
        q_mutex.lock();
        if (!q.empty())
        {
            i = q.front();
            q.pop();
            q_mutex.unlock();
            if (rt[i] <= time_quantum && rt[i] > 0)
            {
                this_thread::sleep_for(chrono::milliseconds(rt[i])); // simulate process execution
                time += rt[i];
                rt[i] = 0;
                flag = 1;
            }
            else if (rt[i] > 0)
            {
                this_thread::sleep_for(chrono::milliseconds(time_quantum)); // simulate process execution
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
            q_mutex.lock();
            q.push(i);
            q_mutex.unlock();
        }
        else
        {
            q_mutex.unlock();
        }
    }

    cout << "Average Waiting Time= " << wait_time * 1.0 / n << endl;
    cout << "Avg Turnaround Time = " << turnaround_time * 1.0 / n << endl;
    return 0;
}