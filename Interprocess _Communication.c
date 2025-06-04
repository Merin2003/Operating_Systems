//USER1


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define NAME "mmchat"

typedef struct {
    int datastatus;    // 0: empty, 1: full
    int exitstatus;    // 1 when EXIT is sent
    char message[50];  // shared message
} shared_area;

int main() {
    int fd;
    shared_area *sh;
    char mess[50];

    // Create shared memory
    fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set size of shared memory
    if (ftruncate(fd, sizeof(shared_area)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map shared memory
    sh = (shared_area *)mmap(0, sizeof(shared_area), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (sh == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Initialize flags
    sh->datastatus = 0;
    sh->exitstatus = 0;

    do {
        // Get message from User 1
        printf("User 1: Enter message (type 'EXIT' to stop): ");
        fgets(mess, sizeof(mess), stdin);
        mess[strcspn(mess, "\n")] = 0; // Remove newline

        strcpy(sh->message, mess);
        sh->datastatus = 1; // Indicate message is available

        if (strcmp(mess, "EXIT") == 0) {
            sh->exitstatus = 1;
            break;
        }

        // Wait for User 2 to respond
        while (sh->datastatus == 1);

        // Print User 2's response
        printf("User 2: %s\n", sh->message);

        if (sh->exitstatus == 1) {
            printf("\nUser 1 Exiting...\n");
            break;
        }

    } while (1);

    // Cleanup
    munmap(sh, sizeof(shared_area));
    close(fd);
    shm_unlink(NAME); // Optional: remove shared memory

    return 0;
}

//USER2
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define NAME "mmchat"

typedef struct {
    int datastatus;    // 0: empty, 1: full
    int exitstatus;    // 1 when "EXIT" is sent
    char message[50];  // shared message
} shared_area;

int main() {
    int fd;
    shared_area *sh;
    char mess[50];

    // Open existing shared memory
    fd = shm_open(NAME, O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map shared memory
    sh = (shared_area *)mmap(0, sizeof(shared_area), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (sh == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    do {
        // Wait for message from User 1
        while (sh->datastatus == 0);

        // Print User 1's message
        printf("User 1: %s\n", sh->message);

        // Check for EXIT condition
        if (sh->exitstatus == 1) {
            printf("\nUser 2 Exiting...\n");
            break;
        }

        // Get response from User 2
        printf("User 2: Enter response (type 'EXIT' to stop): ");
        fgets(mess, sizeof(mess), stdin);
        mess[strcspn(mess, "\n")] = 0; // Remove newline

        strcpy(sh->message, mess);
        sh->datastatus = 1; // Indicate message is written

        if (strcmp(mess, "EXIT") == 0) {
            sh->exitstatus = 1;
            break;
        }

    } while (1);

    // Cleanup
    munmap(sh, sizeof(shared_area));
    close(fd);

    return 0;
}
