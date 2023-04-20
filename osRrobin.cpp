#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include <algorithm>
#include <vector>
using namespace std;

struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void schedulingAlgorithm(vector<process> &p, int quantum, vector<string> &gantt_chart)
{
    // sort the processes according to their arrival time
    sort(p.begin(), p.end(), [](process a, process b) {
        return a.arrival_time < b.arrival_time;
    });

    // calculate the completion time of each process
    int real_time = 0, total_time = 0;
    for (int i = 0; i < p.size(); i++)
    {
        total_time += p[i].burst_time;
    }

    // Scheduling Algorithm - Round Robin
    gantt_chart.push_back("| ");
    int j = 0;
    while (real_time < total_time  && j < p.size())
    {
        for (int i = 0; i < p.size(); i++)
        {
            if (p[i].arrival_time <= real_time)
            {
                if (p[i].burst_time > 0)
                {
                    if (p[i].burst_time > quantum)
                    {
                        real_time += quantum;
                        p[i].burst_time -= quantum;
                        for (int j = 0; j < quantum; j++)
                        {
                            gantt_chart.push_back("P" + to_string(p[i].id) + " | ");
                        }
                    }
                    else
                    {
                        real_time += p[i].burst_time;
                        for (int j = 0; j < p[i].burst_time; j++)
                        {
                            gantt_chart.push_back("P" + to_string(p[i].id) + " | ");
                        }
                        p[i].burst_time = 0;
                        p[i].completion_time = real_time;
                    }
                }
            }
        }
        j++;
    }

    // calculate the waiting time and turnaround time of each process
    for (int i = 0; i < p.size(); i++)
    {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
}

void printGanttChart(vector<string> gantt_chart)
{
    // print the gantt chart
    cout << endl << "Gantt Chart: " << endl;
    for (int i = 0; i < gantt_chart.size() * 5; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < gantt_chart.size(); i++)
    {
        cout << gantt_chart[i];
    }
    cout << endl;
    for (int i = 0; i < gantt_chart.size() * 5; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < gantt_chart.size(); i++)
    {
        if(i < 10)
            cout << i << "    ";
        else
            cout << i << "   ";
    }
    cout << endl << endl;
}

int main()
{
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;

    vector<process> p(n);
    vector<string> gantt_chart;

    // generate random arrival time and burst time for each process
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> arrivalTimeDist(0, 10);
    uniform_int_distribution<> burstTimeDist(1, 5);
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        p[i].arrival_time = arrivalTimeDist(gen);
        p[i].burst_time = burstTimeDist(gen);
    }

    // Enter the time quantum
    cout << "Enter the time quantum: ";
    int quantum;
    cin >> quantum;

    // print the table 
    cout << "Process\tArrival Time\tBurst Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].id << "\t" << p[i].arrival_time << "\t\t" << p[i].burst_time << endl;
    }

    // call the scheduling algorithm
    schedulingAlgorithm(p, quantum, gantt_chart);

    // sort the processes according to their id
    sort(p.begin(), p.end(), [](process a, process b) {
        return a.id < b.id;
    });

    // print the gantt chart
    printGanttChart(gantt_chart);

    // print the table
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].id << "\t" << p[i].arrival_time << "\t\t" << p[i].burst_time << "\t\t" << p[i].waiting_time << "\t\t" << p[i].turnaround_time << "\t\t" << p[i].completion_time << endl;
    }

    // calculate the average waiting time and average turnaround time
    double avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    cout << endl << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;



return 0;
}