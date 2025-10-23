#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

/*
 * cat: A basic implementation of the 'cat' utility.
 *
 * This program should read a file specified by the user
 * and print its contents to the standard output (the terminal).
 *
 * Usage:
 * ./cat <filename>
 *
 * The program should:
 * 1. Check if exactly one filename is provided as a command-line argument.
 * 2. Open the specified file for reading.
 * 3. Read the file's contents in chunks (using a buffer).
 * 4. Write each chunk to standard output (STDOUT_FILENO).
 * 5. Close the file and handle any potential errors.
 */
int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1; // Return an error code.
    }

    


    char *filepath = argv[1];
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1; // Return an error code.
    }




    char buffer[BUFFER_SIZE];

    int rd;

     printf("Printing %s\n", argv[1]);

    while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0) {
        int written = 0;
        while (written < rd) {
            int w = write(STDOUT_FILENO, buffer + written, rd - written);
            if (w == -1) {
                
                perror("write");
                close(fd);
                return 1;
            }
            written += w;
        }
    }

    if (rd == -1) {
        perror("read");
        close(fd);
        return 1;
    }




    
    close(fd);
    return 0;
}
    

