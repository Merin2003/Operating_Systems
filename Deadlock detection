#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void deadlockDetection(int processes, int resources, int alloc[MAX_PROCESSES][MAX_RESOURCES], 
                       int req[MAX_PROCESSES][MAX_RESOURCES], int avail[MAX_RESOURCES]) 
{
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    for (int i = 0; i < resources; i++) 
    {
        work[i] = avail[i];
    }

    while (1)
    {
        bool found = false;
        for (int i = 0; i < processes; i++) 
        {
            if (!finish[i])
            { 
              // Process not yet completed
                bool canExecute = true;
                for (int j = 0; j < resources; j++)
                {
                    if (req[i][j] > work[j]) 
                    { // Not enough resources
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute)
                {
                    // Release allocated resources
                    for (int j = 0; j < resources; j++)
                    {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true; // Mark process as finished
                    found = true;
                }
            }
        }
        if (!found) 
        {
            break; // No process can be executed further
        }
    }

    // Check for deadlock
    bool deadlock = false;
    for (int i = 0; i < processes; i++) 
    {
        if (!finish[i]) {
            deadlock = true;
            printf("Process %d is in deadlock.\n", i);
        }
    }

    if (!deadlock) 
    {
        printf("No deadlock detected.\n");
    }
}

int main() 
{
    int processes, resources;
    
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int req[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) 
    {
        for (int j = 0; j < resources; j++) 
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; i++) 
    {
        for (int j = 0; j < resources; j++) 
        {
            scanf("%d", &req[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < resources; i++)
    {
        scanf("%d", &avail[i]);
    }

    deadlockDetection(processes, resources, alloc, req, avail);

    return 0;
}
