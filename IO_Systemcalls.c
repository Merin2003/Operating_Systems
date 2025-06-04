#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024  // Buffer size for reading data

int main()
{
    int fd;         // File descriptor
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    
    
    fd = open("user_data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(0);
    }

    // Get user input
    printf("Enter some text to store in the file: ");
    fgets(buffer, BUFFER_SIZE, stdin);  // Read input from user

    // Write user input to the file
    bytesWritten = write(fd, buffer, strlen(buffer));
    if (bytesWritten == -1) {
        printf("errorg to file");
        close(fd);
        exit(0);
    }
    printf("Data written successfully.\n");

    // Close the file
    close(fd);

    // Open the same file for reading
    fd = open("user_data.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // Read data from the file
    bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead == -1) 
    {
        printf("error");
        close(fd);
        exit(0);
    }
    
    buffer[bytesRead] = '\0'; // Null-terminate the string
    printf("Data read from file:\n%s", buffer);

    // Close the file
    close(fd);
    
    return 0;
}
