// 1 to 4
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {

    // Create 4 files with some sample content
    system("echo 'This is file 1.' > file1.txt");
    system("echo 'This is file 2.' > file2.txt");
    system("echo 'This is file 3.' > file3.txt");
    system("echo 'This is file 4.' > file4.txt");

    // Open the output file for writing
    int output_file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    //Copy 1/4 of the content of each file into the output file
    for (int i = 1; i <= 4; i++) {
        // Open the input file for reading
        char filename[10];
        sprintf(filename, "file%d.txt", i);
        int input_file = open(filename, O_RDONLY);
       //Copy 1/4 of the content of the input file into the output file
        char buffer[BUFFER_SIZE];
        int total_bytes_read = 0;
        int bytes_to_read = 0;
        int bytes_read = 0;
        int bytes_written = 0;
        off_t file_size = lseek(input_file, 0, SEEK_END);
        bytes_to_read = file_size / 4;
        lseek(input_file, 0, SEEK_SET);
        while (total_bytes_read < bytes_to_read &&( bytes_read=read(input_file , buffer , file_size/4))>0 ) {
            bytes_written = write(output_file, buffer, bytes_read);
            total_bytes_read += bytes_read;
        }

        
    }

   
    return 0;
}



// file name

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 256

int main() {
    // Define the five file names
    char* filenames[5] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};

    // Initialize the maximum file size and file name
    off_t max_file_size = 0;
    char max_file_name[MAX_FILENAME_LENGTH];

    // Find the largest file size and file name among the five files
    for (int i = 0; i < 5; i++) {
        // Get the file size using the stat() function
        struct stat st;
        if (stat(filenames[i], &st) == -1) {
            printf("Error: could not get file size for %s. %s\n", filenames[i], strerror(errno));
            return 1;
        }
        off_t file_size = st.st_size;

        // Check if this file is larger than the current maximum
        if (file_size > max_file_size) {
            max_file_size = file_size;
            strncpy(max_file_name, filenames[i], MAX_FILENAME_LENGTH);
        }
    }

    // Print the largest file name
    printf("The largest file name (size-wise) is %s with a size of %ld bytes.\n", max_file_name, max_file_size);

    // Done
    return 0;
}