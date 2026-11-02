
#include <stdio.h>

int n, m;
int alloc[10][10], max[10][10], need[10][10];
int avail[10];

void calculateNeed()
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

void displayNeed()
{
    int i, j;

    printf("\nNeed Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}


void bankerAlgorithm()
{
    int work[10], finish[10] = {0}, safe[10];
    int i, j, count = 0;

    for (i = 0; i < m; i++)
        work[i] = avail[i];

    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            printf("\nUnsafe state\n");
            return;
        }
    }

    printf("\nSafe Sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safe[i]);

    printf("\nSafe state\n");
}

int main()
{
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    if (n < 1 || n > 10 || m < 1 || m > 10)
    {
        printf("Invalid number of processes or resources.\n");
        return 1;
    }

    printf("\nEnter Allocation Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");

    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    calculateNeed();
    displayNeed();
    bankerAlgorithm();

    return 0;
}
