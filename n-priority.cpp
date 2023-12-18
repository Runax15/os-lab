#include<iostream>

using namespace std;

int main() {
    int AT[10], BT[10], x[10], pr[10] = {0};
    int WT[10], TAT[10], CT[10];
    int P[10]; // To store the order of processes executed
    int i, j, min, count = 0, time, n;
    double avg = 0, tt = 0, end;

    cout << "\nEnter the number of Processes: ";
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "\nEnter arrival time of process " << i + 1 << ": ";
        cin >> AT[i];
    }
    for (i = 0; i < n; i++) {
        cout << "\nEnter burst time of process " << i + 1 << ": ";
        cin >> BT[i];
    }
    for (i = 0; i < n; i++) {
        cout << "\nEnter priority of process " << i + 1 << ": ";
        cin >> pr[i];
    }
    for (i = 0; i < n; i++)
        x[i] = BT[i];

    pr[9] = -1;
    time = 0; // Initialize time

    while (count != n) {
        min = 9;
        for (i = 0; i < n; i++) {
            if (AT[i] <= time && pr[i] > pr[min] && BT[i] > 0)
                min = i;
        }
        time += BT[min] - 1;
        BT[min] = -1;
        count++;
        end = time + 1;
        CT[min] = end;
        WT[min] = end - AT[min] - x[min];
        TAT[min] = end - AT[min];
        P[count - 1] = min; // Store the executed process
    }

    //gantt chart
    cout << "\nGantt Chart:" << endl;
    for (i = 0; i < n; i++) {
        cout << "+-----";
    }
    cout << "+" << endl;

    for (i = 0; i < n; i++) {
        cout << "| P" << P[i] << "  ";
    }
    cout << "|" << endl;

    for (i = 0; i < n; i++) {
        cout << "+-----";
    }
    cout << "+" << endl;

    for (i = 0; i < n; i++) {
        cout << "      " << CT[i];
    }
    cout << endl;

    // Display process details
    cout << "\nProcess"
         << "\t"
         << "BT"
         << "\t"
         << "AT"
         << "\t"
         << "WT"
         << "\t"
         << "TT"
         << "\t"
         << "CT"
         << "\t"
         << "Priority"
         << endl;
    for (i = 0; i < n; i++) {
        cout << "P" << P[i] + 1 << "\t\t" << x[P[i]] << "\t\t" << AT[P[i]]
             << "\t\t" << WT[P[i]] << "\t\t" << TAT[P[i]] << "\t\t"
             << CT[P[i]] << "\t\t" << pr[P[i]] << endl;
        avg = avg + WT[P[i]];
        tt = tt + TAT[P[i]];
    }
    cout << "\n\nAverage Waiting Time = " << avg / n;
    cout << "\nAverage Turnaround Time = " << tt / n << endl;

    return 0;
}
