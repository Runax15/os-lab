#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>

using namespace std;

// Define a struct to represent a process
struct Process {
    int PID;     // Process identifier
    int BT;     // Burst Time
    int AT;     // Arrival Time
    int CT;     // Completion Time
    int TAT;    // Turnaround Time
    int WT;     // Waiting Time
};

// Function to compare processes based on arrival time and burst time
bool compareAT_BT(const Process& a, const Process& b) {
    // If arrival times are equal, compare based on burst time
    if (a.AT == b.AT) {
        return a.BT < b.BT;
    }
    // Otherwise, compare based on arrival time
    return a.AT < b.AT;
}

// Function to calculate completion time, turnaround time, and waiting time for each process
void calculateTimes(vector<Process>& processes) {
    // Calculate completion, turnaround, and waiting times for the first process
    processes[0].CT = processes[0].AT + processes[0].BT;
    processes[0].TAT = processes[0].CT - processes[0].AT;
    processes[0].WT = processes[0].TAT - processes[0].BT;

    // Calculate times for the remaining processes
    for (int i = 1; i < processes.size(); ++i) {
        // Calculate completion time for the current process
        processes[i].CT = max(processes[i - 1].CT, processes[i].AT) + processes[i].BT;

        // Calculate turnaround time for the current process
        processes[i].TAT = processes[i].CT - processes[i].AT;

        // Calculate waiting time for the current process
        processes[i].WT = processes[i].TAT - processes[i].BT;
    }
}

// Function to display the Gantt chart
void displayGanttChart(const vector<Process>& processes) {
    cout << "Gantt Chart:" << endl;

    // Display the horizontal lines for the Gantt chart
    for (const Process& p : processes) {
        cout << "+-----";
    }
    cout << "+" << endl;

    // Display the process labels in the Gantt chart
    for (const Process& p : processes) {
        cout << "| P" << p.PID << "  ";
    }
    cout << "|" << endl;

    // Display the horizontal lines for the Gantt chart
    for (const Process& p : processes) {
        cout << "+-----";
    }
    cout << "+" << endl;

    // Display the completion times in the Gantt chart with spacing
    for (const Process& p : processes) {
        cout << setw(5) << p.CT << setw(3) << " ";
    }
    cout << endl;
}

// Function to display the process table
void displayTable(const vector<Process>& processes) {
    cout << "\nProcess\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    // Display the details of each process in the table
    for (const Process& p : processes) {
        cout << p.PID << "\t" << p.BT << "\t\t" << p.AT << "\t\t"
            << p.CT << "\t\t" << p.TAT << "\t\t" << p.WT << endl;
    }
}

int main() {
    int n;
    // Get the number of processes from the user
    cout << "Enter the number of processes: ";
    cin >> n;

    // Create a vector to hold process details
    vector<Process> processes(n);

    // Get process details from the user
    cout << "Enter process details:" << endl;
    for (int i = 0; i < n; ++i) {
        processes[i].PID = i + 1;
        cout << "Process " << i + 1 << " - Arrival Time: ";
        cin >> processes[i].AT;
        cout << "Process " << i + 1 << " - Burst Time: ";
        cin >> processes[i].BT;
    }

    // Sort processes based on arrival time and burst time
    sort(processes.begin(), processes.end(), compareAT_BT);

    // Calculate completion time, turnaround time, and waiting time for each process
    calculateTimes(processes);

    // Display the Gantt chart
    displayGanttChart(processes);

    // Display the process table
    displayTable(processes);

    // Calculate and display average turnaround time and average waiting time
    double avgTAT = 0, avgWT = 0;
    for (const Process& p : processes) {
        avgTAT += p.TAT;
        avgWT += p.WT;
    }

    avgTAT /= n;
    avgWT /= n;

    // Set precision for displaying average times
    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << avgTAT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
