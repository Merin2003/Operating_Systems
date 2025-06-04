#include <stdio.h>

int process[10], part[20], mem[10];
int p, pa;

// Global variables to track fragmentation
int extfrag_firstfit = 0, extfrag_bestfit = 0, extfrag_worstfit = 0;

void printAllocation(char method[]) 
{
    printf("\n%s Allocation:\n", method);
    printf("Process No.\tProcess Size\tAllocated Partition\n");
    for (int i = 0; i < p; i++) 
   {
        printf("%d\t\t%d\t\t", i + 1, process[i]);
        if (mem[i] != -1)
            printf("%d\n", mem[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void copyPartitions(int temp[])
{
    for (int i = 0; i < pa; i++)
    {
        temp[i] = part[i];
    }
}

void firstfit() 
{
    int intfrag = 0;
    int memo[pa];
    for (int i = 0; i < pa; i++) memo[i] = -1;

    int temp[20];
    copyPartitions(temp);

    for (int i = 0; i < p; i++) 
    {
        mem[i] = -1;
        for (int j = 0; j < pa; j++) 
        {
            if (process[i] <= temp[j] && memo[j] == -1) 
           {
                memo[j] = 0;
                mem[i] = j;
                intfrag += temp[j] - process[i];
                temp[j] -= process[i];
                break;
            }
        }
    }

    extfrag_firstfit = 0;
    for (int i = 0; i < pa; i++) 
    {
        if (memo[i] == -1)
       {
            extfrag_firstfit += temp[i];
        }
    }

    printAllocation("First Fit");
    printf("\nInternal Fragmentation: %d", intfrag);
    printf("\nExternal Fragmentation: %d\n", extfrag_firstfit);
}

void bestfit() 
{
    int intfrag = 0;
    int temp[20], memo[pa];
    copyPartitions(temp);
    for (int i = 0; i < pa; i++) memo[i] = -1;

    for (int i = 0; i < p; i++) 
    {
        mem[i] = -1;
        int bestIdx = -1;
        for (int j = 0; j < pa; j++) 
        {
            if (process[i] <= temp[j] && memo[j] == -1) 
             {
                if (bestIdx == -1 || temp[j] < temp[bestIdx]) 
                {
                    bestIdx = j;
                }
            }
        }

        memo[bestIdx] = 0;
        if (bestIdx != -1) 
        {
            mem[i] = bestIdx;
            intfrag += temp[bestIdx] - process[i];
            temp[bestIdx] -= process[i];
        }
    }

    extfrag_bestfit = 0;
    for (int i = 0; i < pa; i++) 
    {
        if (memo[i] == -1) 
        {
            extfrag_bestfit += temp[i];
        }
    }

    printAllocation("Best Fit");
    printf("\nInternal Fragmentation: %d", intfrag);
    printf("\nExternal Fragmentation: %d\n", extfrag_bestfit);
}

void worstfit() 
{
    int intfrag = 0;
    int temp[20], memo[pa];
    copyPartitions(temp);
    for (int i = 0; i < pa; i++) memo[i] = -1;

    for (int i = 0; i < p; i++) 
    {
        mem[i] = -1;
        int worstIdx = -1;
        for (int j = 0; j < pa; j++) 
        {
            if (process[i] <= temp[j] && memo[j] == -1) 
            {
                if (worstIdx == -1 || temp[j] > temp[worstIdx]) 
                {
                    worstIdx = j;
                }
            }
        }

        memo[worstIdx] = 0;
        if (worstIdx != -1) {
            mem[i] = worstIdx;
            intfrag += temp[worstIdx] - process[i];
            temp[worstIdx] -= process[i];
        }
    }

    extfrag_worstfit = 0;
    for (int i = 0; i < pa; i++)
    {
        if (memo[i] == -1)
        {
            extfrag_worstfit += temp[i];
        }
    }

    printAllocation("Worst Fit");
    printf("\nInternal Fragmentation: %d", intfrag);
    printf("\nExternal Fragmentation: %d\n", extfrag_worstfit);
}

// Function to rank the allocation algorithms
void rankAlgorithms() 
{
    int fragmentation[3] = {extfrag_firstfit, extfrag_bestfit, extfrag_worstfit};
    int index[3] = {0, 1, 2}; // 0 = First Fit, 1 = Best Fit, 2 = Worst Fit

    // Sorting based on external fragmentation (lower is better)
    for (int i = 0; i < 2; i++) 
     {
        for (int j = i + 1; j < 3; j++)
        {
            if (fragmentation[index[i]] > fragmentation[index[j]])
            {
                int temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
        }
    }

    printf("\nRanking of Allocation Strategies (Best to Worst based on external fragmentation):\n");
    char *names[] = {"First Fit", "Best Fit", "Worst Fit"};
    for (int i = 0; i < 3; i++)
     {
        printf("%d. %s - External Fragmentation: %d\n", i + 1, names[index[i]], fragmentation[index[i]]);
    }
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    printf("Enter the number of partitions: ");
    scanf("%d", &pa);

    printf("Enter the process sizes:\n");
    for (int i = 0; i < p; i++) 
    {
        scanf("%d", &process[i]);
    }

    printf("Enter the partition sizes:\n");
    for (int i = 0; i < pa; i++) 
    {
        scanf("%d", &part[i]);
    }

    firstfit();
    bestfit();
    worstfit();

    rankAlgorithms();

    return 0;
}
