#include <stdio.h>

// Global variables for hits and misses
int hit_fcfs = 0, miss_fcfs = 0;
int hit_lru = 0, miss_lru = 0;
int hit_lfu = 0, miss_lfu = 0;
int hit_optimal = 0, miss_optimal = 0;

void reset(int a[100], int x);
void display(int a[100], int x);
void fcfs(int a[100], int x, int b[100], int y);
void lru(int a[100], int x, int b[100], int y);
void lfu(int a[100], int x, int b[100], int y);
void optimal(int a[100], int x, int b[100], int y);
void rank_algorithms();

void reset(int a[100], int x)
{
    for (int i = 0; i < x; i++) 
{
        a[i] = -1;
    }
}

void display(int a[100], int x)
{
    for (int i = 0; i < x; i++) 
   {
        if (a[i] == -1) 
        {
            printf("-\t");
        } 
       else 
       {
            printf("%d\t", a[i]);
        }
    }
    printf("\n");
}

void fcfs(int a[100], int x, int b[100], int y)
{
    printf("\nFIRST IN FIRST OUT\n");
    int f = 0;
    
    for (int i = 0; i < x; i++) 
    {
        int found = 0;
        for (int j = 0; j < y; j++) 
         {
            if (b[j] == a[i]) 
            {
                hit_fcfs++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            miss_fcfs++;
            b[f] = a[i];
            f = (f + 1) % y;
            display(b, y);
        }
    }
}

void lru(int a[100], int x, int b[100], int y) 
{
    printf("\nLEAST RECENTLY USED\n");
    int time[100] = {0}, track[y], t = 0;

    for (int i = 0; i < y; i++) 
    {
        track[i] = -1;
    }

    for (int i = 0; i < x; i++) 
    {
        int found = 0;
        for (int j = 0; j < y; j++) 
        {
            if (b[j] == a[i]) 
            {
                hit_lru++;
                found = 1;
                time[a[i]] = ++t;
                break;
            }
        }
        if (!found) 
        {
            miss_lru++;
            if (i < y) 
            {
                b[i] = a[i];
                track[i] = a[i];
            }
          else
          {
                int min = 0;
                for (int j = 1; j < y; j++) 
                {
                    if (time[track[j]] < time[track[min]]) 
                     {
                        min = j;
                    }
                }
                b[min] = a[i];
                track[min] = a[i];
                time[a[i]] = ++t;
            }
            display(b, y);
        }
    }
}

void lfu(int a[100], int x, int b[100], int y) 
{
    printf("\nLEAST FREQUENTLY USED\n");
    int count[100] = {0}, track[y], time[100] = {0}, t = 0;

    for (int i = 0; i < y; i++) 
    {
        track[i] = -1;
    }

    for (int i = 0; i < x; i++) 
    {
        int found = 0;
        for (int j = 0; j < y; j++) 
        {
            if (b[j] == a[i]) 
            {
                hit_lfu++;
                found = 1;
                count[a[i]]++;
                break;
            }
        }
        if (!found)
        {
            miss_lfu++;
            if (i < y) 
            {
                b[i] = a[i];
                track[i] = a[i];
                count[a[i]] = 1;
                time[a[i]] = ++t;
            } 
            else 
            {
                int min = 0;
                for (int j = 1; j < y; j++) 
                {
                    if (count[track[j]] < count[track[min]] ||
                        (count[track[j]] == count[track[min]] && time[track[j]] < time[track[min]])) 
                    {
                        min = j;
                    }
                }
                b[min] = a[i];
                track[min] = a[i];
                count[a[i]] = 1;
                time[a[i]] = ++t;
            }
            display(b, y);
        }
    }
}

void optimal(int a[100], int x, int b[100], int y) 
{
    printf("\nOPTIMAL PAGE REPLACEMENT\n");

    for (int i = 0; i < x; i++) 
    {
        int found = 0;
        for (int j = 0; j < y; j++) 
        {
            if (b[j] == a[i]) 
            {
                hit_optimal++;
                found = 1;
                break;
            }
        }

        if (!found) 
        {
            miss_optimal++;

            if (i < y) 
            {
                b[i] = a[i];
            }
            else 
            {
                int farthest = -1, index = -1;
                for (int j = 0; j < y; j++) 
                {
                    int next = 9999;
                    for (int k = i + 1; k < x; k++)
                    {
                        if (b[j] == a[k]) 
                        {
                            next = k;
                            break;
                        }
                    }
                    if (next > farthest) 
                    {
                        farthest = next;
                        index = j;
                    }
                }
                b[index] = a[i];
            }
            display(b, y);
        }
    }
}

void rank_algorithms()
{
    int misses[4] = {miss_fcfs, miss_lru, miss_lfu, miss_optimal};
    int index[4] = {0, 1, 2, 3}; // 0 = FCFS, 1 = LRU, 2 = LFU, 3 = Optimal
    
    // Sorting based on misses (fewer misses = better rank)
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (misses[index[i]] > misses[index[j]]) {
                int temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
        }
    }

    printf("\nRanking of Algorithms (Best to Worst based on page faults):\n");
    char *names[] = {"FIFO", "LRU", "LFU", "Optimal"};
    for (int i = 0; i < 4; i++) {
        printf("%d. %s - %d page faults\n", i + 1, names[index[i]], misses[index[i]]);
    }
}

int main() 
{
    int n, m;
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);

    int ref[100];
    printf("Enter the number of frames: ");
    scanf("%d", &m);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
   {
        scanf("%d", &ref[i]);
    }

    int frame[m];

    reset(frame, m);
    fcfs(ref, n, frame, m);

    reset(frame, m);
    lru(ref, n, frame, m);

    reset(frame, m);
    lfu(ref, n, frame, m);

    reset(frame, m);
    optimal(ref, n, frame, m);

    rank_algorithms();

    return 0;
}
