#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100 // Maximum storage blocks

int disk[MAX_BLOCKS]; // Disk blocks (0 = free, 1 = allocated)

// Function to initialize the disk
void initializeDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i] = 0; // All blocks are initially free
    }
}

// Function to display disk status
void displayDisk() {
    printf("\nDisk Status: \n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

// *1. Sequential (Contiguous) Allocation*
void contiguousAllocation(int start, int size) {
    int i, free_blocks = 0;

    // Check if enough contiguous space is available
    for (i = start; i < MAX_BLOCKS; i++) {
        if (disk[i] == 0)
            free_blocks++;
        else
            free_blocks = 0;

        if (free_blocks == size)
            break;
    }

    if (free_blocks < size) {
        printf("\nError: Not enough contiguous space available.\n");
        return;
    }

    // Allocate blocks
    for (int j = i - size + 1; j <= i; j++) {
        disk[j] = 1;
    }

    printf("\nContiguous Allocation: Blocks %d to %d allocated.\n", i - size + 1, i);
}

// *2. Indexed Allocation*
void indexedAllocation(int indexBlock, int blocks[], int size) {
    if (disk[indexBlock] == 1) {
        printf("\nError: Index block already allocated.\n");
        return;
    }

    disk[indexBlock] = 1; // Allocate index block

    printf("\nIndexed Allocation: Index Block %d -> [ ", indexBlock);
    for (int i = 0; i < size; i++) {
        if (disk[blocks[i]] == 1) {
            printf("\nError: Block %d is already allocated.\n", blocks[i]);
            return;
        }
        disk[blocks[i]] = 1;
        printf("%d ", blocks[i]);
    }
    printf("]\n");
}

// *3. Linked Allocation*
void linkedAllocation(int startBlock, int size) {
    int allocated = 0, current = startBlock;

    if (disk[startBlock] == 1) {
        printf("\nError: Starting block already allocated.\n");
        return;
    }

    printf("\nLinked Allocation: Blocks allocated -> ");
    while (allocated < size) {
        if (disk[current] == 0) {
            disk[current] = 1;
            printf("%d -> ", current);
            allocated++;
        }
        current++;
        if (current >= MAX_BLOCKS) {
            printf("\nError: Not enough free space.\n");
            return;
        }
    }
    printf("NULL\n");
}

// *Main function*
int main() {
    initializeDisk();
    
    int choice, start, size, indexBlock, blocks[10];

    while (1) {
        printf("\nFile Allocation Strategies\n");
        printf("1. Contiguous Allocation\n");
        printf("2. Indexed Allocation\n");
        printf("3. Linked Allocation\n");
        printf("4. Display Disk\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter starting block and size: ");
                scanf("%d %d", &start, &size);
                contiguousAllocation(start, size);
                break;
            case 2:
                printf("Enter index block: ");
                scanf("%d", &indexBlock);
                printf("Enter number of blocks: ");
                scanf("%d", &size);
                printf("Enter block numbers: ");
                for (int i = 0; i < size; i++)
                    scanf("%d", &blocks[i]);
                indexedAllocation(indexBlock, blocks, size);
                break;
            case 3:
                printf("Enter starting block and size: ");
                scanf("%d %d", &start, &size);
                linkedAllocation(start, size);
                break;
            case 4:
                displayDisk();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
