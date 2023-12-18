#include <stdio.h>

void sort(int n, int AT[], int BT[], int P[])
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (AT[j] > AT[j + 1])
            {
                // Swap arrival time
                temp = AT[j];
                AT[j] = AT[j + 1];
                AT[j + 1] = temp;

                // Swap burst time
                temp = BT[j];
                BT[j] = BT[j + 1];
                BT[j + 1] = temp;

                // Swap process IDs
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int P[n], AT[n], BT[n], CT[n], TAT[n], WT[n], RT[n];

    printf("Enter the arrival time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Arrival time of P[%d]: ", i);
        scanf("%d", &AT[i]);
        P[i] = i; // Initialize process IDs
    }

    printf("Enter the burst time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Burst time of P[%d]: ", i);
        scanf("%d", &BT[i]);
    }

    // Sort processes based on arrival time
    sort(n, AT, BT, P);

    printf("The completion time is:\n");
    for (int i = 0; i < n; i++)
    {

        CT[i] = AT[i] + BT[i];
        printf("The completion time of P[%d] is %d\n", P[i], CT[i]);
    }

    printf("The turnaround time (TAT) of processes:\n");
    for (int i = 0; i < n; i++)
    {
        TAT[i] = CT[i] - AT[i];
        printf("The TAT of P[%d] is %d\n", P[i], TAT[i]);
    }

    printf("The waiting time (WT) of processes:\n");
    for (int i = 0; i < n; i++)
    {
        WT[i] = TAT[i] - BT[i];
        printf("The TAT of P[%d] is %d\n", P[i], WT[i]);
    }

    printf("The response time (RT) of processes:\n");
    for (int i = 0; i < n; i++)
    {
        RT[i] = WT[i];
        printf("The TAT of P[%d] is %d\n", P[i], RT[i]);
    }

    printf("\n------------------------------------------------------------------------------------------------------------------\n");
    printf("| Process  |  Arrival Time  |  Burst Time  |  Completion Time  | Turnaround Time  | Waiting Time | Response Time | \n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("|   P[%d]   |      %d     |    %d    |      %d      |      %d       |      %d      |      %d      |\n", P[i], AT[i], BT[i], CT[i], TAT[i], RT[i], WT[i]);
    }
    printf("------------------------------------------------------------------------------------------------------------------\n");

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d |", P[i]);
    }

    float avg = 0.0;
    for (int i = 0; i < n; i++)
    {
        avg += (float)TAT[i] / n;
    }
    printf("\n\nAverage TAT: %.2f", avg);

    float a = 0.0;
    for (int i = 0; i < n; i++)
    {
        a += (float)WT[i] / n;
    }
    printf("\nAverage WT: %.2f", a);

    float b = 0.0;
    for (int i = 0; i < n; i++)
    {
        b += (float)RT[i] / n;
    }
    printf("\nAverage RT: %.2f\n", b);

    return 0;
}