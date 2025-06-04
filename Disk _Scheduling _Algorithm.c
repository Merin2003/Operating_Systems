#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 100

// Sorting function for SCAN, CSCAN, LOOK, CLOOK
void sort(int a[MAX_TRACKS], int x) {
    for (int i = 0; i < x - 1; i++) {
        for (int j = 0; j < x - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// *FCFS Algorithm*
void fcfs(int p, int a[MAX_TRACKS], int x) {
    int sum = 0;
    printf("\nFIRST COME FIRST SERVE\n%d\t", p);
    for (int i = 0; i < x; i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");

    sum += abs(p - a[0]);
    for (int i = 0; i < x - 1; i++) {
        sum += abs(a[i + 1] - a[i]);
    }
    printf("The total seek time is %d\n", sum);
}

// *SSTF Algorithm*
void sstf(int p, int a[MAX_TRACKS], int x) {
    int sum = 0, completed[MAX_TRACKS] = {0};
    printf("\nSHORTEST SEEK TIME FIRST\n%d\t", p);

    for (int i = 0; i < x; i++) {
        int min_distance = 9999, index = -1;
        for (int j = 0; j < x; j++) {
            if (!completed[j] && abs(a[j] - p) < min_distance) {
                min_distance = abs(a[j] - p);
                index = j;
            }
        }
        printf("%d\t", a[index]);
        sum += abs(p - a[index]);
        p = a[index];
        completed[index] = 1;
    }
    printf("\nThe total seek time is %d\n", sum);
}

// *SCAN Algorithm*
void scan(int p, int a[MAX_TRACKS], int x, int y) {
    printf("\nSCAN\n");
    int temp1[MAX_TRACKS], temp2[MAX_TRACKS], j = 0, k = 0, sum = 0;

    for (int i = 0; i < x; i++) {
        if (a[i] > p)
            temp1[j++] = a[i];
        else
            temp2[k++] = a[i];
    }

    sort(temp1, j);
    sort(temp2, k);

    printf("%d\t", p);
    for (int i = 0; i < j; i++)
        printf("%d\t", temp1[i]);
    printf("%d\t", y);
    for (int i = k - 1; i >= 0; i--)
        printf("%d\t", temp2[i]);
    
    sum = (y - p) + (y - temp2[0]);
    printf("\nThe total seek time is %d\n", sum);
}

// *CSCAN Algorithm*
void cscan(int p, int a[MAX_TRACKS], int x, int y) {
    printf("\nCSCAN\n");
    int temp1[MAX_TRACKS], temp2[MAX_TRACKS], j = 0, k = 0, sum = 0;

    temp1[j++] = y;
    temp2[k++] = 0;

    for (int i = 0; i < x; i++) {
        if (a[i] > p)
            temp1[j++] = a[i];
        else
            temp2[k++] = a[i];
    }

    sort(temp1, j);
    sort(temp2, k);

    printf("%d\t", p);
    for (int i = 0; i < j; i++)
        printf("%d\t", temp1[i]);
    for (int i = 0; i < k; i++)
        printf("%d\t", temp2[i]);

    sum = (y - p) + (y - 0) + (temp2[k - 1] - 0);
    printf("\nThe total seek time is %d\n", sum);
}

// *LOOK Algorithm*
void look(int p, int a[MAX_TRACKS], int x) {
    printf("\nLOOK\n");
    int temp1[MAX_TRACKS], temp2[MAX_TRACKS], j = 0, k = 0, sum = 0;

    for (int i = 0; i < x; i++) {
        if (a[i] > p)
            temp1[j++] = a[i];
        else
            temp2[k++] = a[i];
    }

    sort(temp1, j);
    sort(temp2, k);

    printf("%d\t", p);
    for (int i = 0; i < j; i++)
        printf("%d\t", temp1[i]);
    for (int i = k - 1; i >= 0; i--)
        printf("%d\t", temp2[i]);

    sum = (temp1[j - 1] - p) + (temp1[j - 1] - temp2[0]);
    printf("\nThe total seek time is %d\n", sum);
}

// *CLOOK Algorithm*
void clook(int p, int a[MAX_TRACKS], int x) {
    printf("\nCLOOK\n");
    int temp1[MAX_TRACKS], temp2[MAX_TRACKS], j = 0, k = 0, sum = 0;

    for (int i = 0; i < x; i++) {
        if (a[i] > p)
            temp1[j++] = a[i];
        else
            temp2[k++] = a[i];
    }

    sort(temp1, j);
    sort(temp2, k);

    printf("%d\t", p);
    for (int i = 0; i < j; i++)
        printf("%d\t", temp1[i]);
    for (int i = 0; i < k; i++)
        printf("%d\t", temp2[i]);

    sum = (temp1[j - 1] - p) + (temp1[j - 1] - temp2[0]) + (temp2[k - 1] - temp2[0]);
    printf("\nThe total seek time is %d\n", sum);
}

// *Main Function*
int main() {
    int n, req[MAX_TRACKS], max, curr;

    printf("Enter the number of tracks in the request:");
    scanf("%d", &n);
    printf("Enter the sequence of request:");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }
    printf("Enter the max track of the disc:");
    scanf("%d", &max);
    printf("Enter the current position of the head:");
    scanf("%d", &curr);

    fcfs(curr, req, n);
    sstf(curr, req, n);
    scan(curr, req, n, max);
    cscan(curr, req, n, max);
    look(curr, req, n);
    clook(curr, req, n);

    return 0;
}
