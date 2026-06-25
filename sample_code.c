#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. Declare a file pointer
    FILE *fptr;
    char buffer[100];

    // --- WRITING TO A FILE ---
    // Open the file in write mode ("w"). This creates a new file or overwrites an existing one.
    fptr = fopen("example.txt", "w");

    // Always check if the file opened successfully
    if (fptr == NULL) {
        printf("Error opening file for writing!\n");
        exit(1); // Exit the program
    }

    // Write text to the file
    fprintf(fptr, "Hello, World!\n");
    fprintf(fptr, "This is a simple file handling program in C.\n");

    // Always close the file when you are done with it
    fclose(fptr);
    printf("Data successfully written to example.txt\n\n");


    // --- READING FROM A FILE ---
    // Open the file in read mode ("r")
    fptr = fopen("example.txt", "r");

    if (fptr == NULL) {
        printf("Error opening file for reading!\n");
        exit(1);
    }

    printf("Reading content from example.txt:\n");
    printf("---------------------------------\n");

    // Read the file line by line until the end of the file (EOF)
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        // Print the line we just read
        printf("%s", buffer);
    }

    // Close the file again
    fclose(fptr);

    return 0;
}
