/* cp1.c
 * version 1 of cp -- user read and write with tunable buffer size
 * usage: cp1 src dest
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char*, char*);

int main(int ac, char* av[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    if (ac != 3) { // check args
        fprintf(stderr, "usage: %s source destionation\n", *av);
        exit(1);
    }

    if ((in_fd = open(av[1], O_RDONLY)) == -1) { // open files
        oops("Cannot open", av[1]);
    }

    if ((out_fd = creat(av[2], COPYMODE)) == -1) {
        oops("Cannot creat", av[2]);
    }

    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) { // copy files 
        if (write(out_fd, buf, n_chars) != n_chars) {
            oops("Write error to", av[2]);
        }
    }

    if (n_chars == -1) {
        oops("Read error from", av[1]);
    }

    if (close(in_fd) == -1 || close(out_fd) == -1) { // close files
        oops("Error closing files", "");
    }
}

void oops(char* s1, char* s2) {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}

/*
flow chart:

         open sourcefile for reading
         open copyfile for writing
    +--> read from source to buffer -- eof? --+
    |                                         |
    +--  write from buffer to copy            |
         close sourcefile <-------------------+
         close copyfile

*/