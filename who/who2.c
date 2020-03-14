/* who2.c —— read /etc/utmp and list info therein 
 *         - suppresses empty records
 *         - formats time nicely
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST // include remote machine on output

int main() {
    struct utmp current_record; // read info into here
    int utmpfd; // read from this descriptor
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE); // UTMP_FILE is in utmp.h
        exit(1);
    }

    while (read(utmpfd, &current_record, reclen) == reclen) {
        show_info(&current_record);
    }
    close(utmpfd);

    return 0; // went ok
}

/*
 * show info()
 * displays contents of the utmp struct in human readable form
 * displays nothing if record has no user name
 */
void show_info(struct utmp *utbufp) {
    if (utbufp->ut_type != USER_PROCESS) { // users only
        return;
    }
    printf("%-8.8s", utbufp->ut_name); // the username
    printf(" "); // a space
    printf("%-8.8s", utbufp->ut_line); // the tty
    printf(" "); // a space
    show_time(utbufp->ut_time); // display time
    printf(" "); // a space
#ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0') {
        printf("(%s)", utbufp->ut_host); // the host
    }
#endif
    printf("\n"); // newline
}

/*
 * display time in a format fit for human consumption
 * uses ctime to build a string then picks parts out of it
 * Note: %12.12s prints a string 12 chars wide and LIMITS it to 12chars
 */
void show_time(long timeval) {
    char* cp; // to hold address of time

    cp = ctime(&timeval); // convert time to string, string looks like: Mon Feb 4 00:46:40 EST 1991 0123456789012345.
    printf("%12.12s", cp+4); // pick 12 chars from pos 4
}
