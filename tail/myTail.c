#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1024
#define DEFAULT_N 10

int main(int argc, char *argv[]) {
char **tail;
int count = DEFAULT_N, n, i, headX = 0, tailX = 0, z = 1;

/* Validate command line arguments, if any. */
/* 2 or more args; 1st argument may be -n, the count */

 if (argc >= 2) {
   if ((sscanf(argv[1], "%d", &n) == 1) && (n < 0)) {
   count = -n; /* save size of tail */
   z = 2; /* check argv[2], if present, for filename */
   }
/* 1st or 2nd arg may be the filename */
 if ((z < argc) && (freopen(argv[z], "r", stdin) == NULL)) {
   fprintf(stderr, "%s not found.\n", argv[z]);
 }
}

/* Allocate space for tail buffer */
 tail = calloc(count, sizeof(char *));

 for (i = 0; i < count; i++) {
   tail[i] = calloc(MAX_LINE_LEN, sizeof(char));
 }

/* Fill circular tail buffer until EOF */

while (fgets(tail[tailX], MAX_LINE_LEN, stdin) != NULL) {
   tailX = (tailX + 1) % count;
   if (tailX == headX) {
     headX = (headX + 1) % count;
   }
 }

/* Display tail */
i = tailX;
do {
  printf("%s", tail[i]);
  i = (i + 1) % count;
  } while (i != tailX);

return 0;
}


/// command -->  $ ./myTail -7 myTail.c
