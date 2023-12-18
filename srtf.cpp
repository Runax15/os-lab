#include<iostream>
#include <iomanip>

using namespace std;

int main() 
{
    int a[10], b[10], x[10];
    int WT[10], TAT[10], CT[10];
    int P[10]; // To store the order of processes executed
    int i, j, min, count = 0, time, n;
    double avg = 0, tt = 0, end;

    cout << "\nEnter the number of Processes: "; // Input
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "\nEnter arrival time of process " << i + 1 << ": "; // Input
        cin >> a[i];
    }
    for (i = 0; i < n; i++) {
        cout << "\nEnter burst time of process " << i + 1 << ": "; // Input
        cin >> b[i];
    }
    for (i = 0; i < n; i++)
        x[i] = b[i];

    b[9] = 9999;
    time = 0; // Initialize time

    while (count != n) {
        min = 9;
        for (i = 0; i < n; i++) {
            if (a[i] <= time && b[i] < b[min] && b[i] > 0)
                min = i;
        }
        b[min]--;

        if (b[min] == 0) {
            count++;
            end = time + 1;
            CT[min] = end;
            WT[min] = end - a[min] - x[min];
            TAT[min] = end - a[min];
            P[count - 1] = min; // Store the executed process
        }
        time++;
    }

    cout << "\nProcess"
         << "\t"
         << "burst-time"
         << "\t"
         << "arrival-time"
         << "\t"
         << "waiting-time"
         << "\t"
         << "turnaround-time"
         << "\t"
         << "completion-time"
         << endl;
    for (i = 0; i < n; i++) {
        cout << "p" << P[i] + 1 << "\t\t" << x[P[i]] << "\t\t" << a[P[i]]
             << "\t\t" << WT[P[i]] << "\t\t" << TAT[P[i]] << "\t\t"
             << CT[P[i]] << endl;
        avg = avg + WT[P[i]];
        tt = tt + TAT[P[i]];
    }
    cout << "\n\nAverage waiting time =" << avg / n;
    cout << "  Average Turnaround time =" << tt / n << endl;

    return 0;
}