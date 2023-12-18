#include <stdio.h>

#define Max_Frame 3

int main()
{
    int pg[] = {0, 1, 2, 3, 4, 2, 1, 3, 5};
    int num_pg = sizeof(pg)/sizeof(pg[0]);
    int FR[Max_Frame];
    int FRcount = 0;

    printf("Pages: ");
    for(int i=0; i<num_pg; i++)
    {
        printf("%d ", pg[i]);
    }
    printf("\n\nFIFO Page Replacement:\n");

    for(int i=0; i < num_pg; i++)
    {
        int current_pg = pg[i];
        int pagehit = 0;

        for(int j=0; j<FRcount; j++)
        {
            if(FR[j] == current_pg)
            {
                pagehit = 1;
                break;
            }
        }
        
        if(!pagehit)
        {
            if(FRcount < Max_Frame)
            {
                FR[FRcount++] = current_pg;
            }
            else
            {
                for(int j=0; j<Max_Frame-1; j++)
                {
                    FR[j] = FR[j+1];
                }
                FR[Max_Frame-1] = current_pg;
            }
            printf("\nPage loaded in memory: %d", current_pg);
            for(int j=0; j<FRcount; j++)
            {
                printf("%d ", FR[j]);
            }
            printf("\n");
        }
        else
        {
            printf("\nPage %d already in memory.", current_pg);
        }
    }
    return 0;
}