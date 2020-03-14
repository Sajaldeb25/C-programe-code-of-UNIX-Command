### who1.c
- function:
    > implement "who" cmd, show username, terminal name, login time and remote host name
- issue:
    > show some empty records
    > login time field is a number format

### who2.c
- function:
    > Based on who1.c, this revsion resolve last version's issue.
- issue:
    > frequently system calls(read), inefficiency

### who3.c
- function:
    > Based on who2.c, this version decline system calls by cache in memory(utmplib.c).