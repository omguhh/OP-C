    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    int main(int argc, char *argv[])
    {
    char *newargv[] = { "/bin/ps", "-l", NULL };
    char *newenviron[] = { NULL };
    char *exeprog = "/bin/ps";
    execve(exeprog, newargv, newenviron);
    exit(EXIT_FAILURE);
}
