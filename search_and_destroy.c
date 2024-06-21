#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void search_and_destroy();
int TOTAL_PROCESSES = 500;
long unsigned int LINES = 1000000000000;

void main()
{
    int i, processes_created;
    pid_t pid;

    printf("Welcome to search and dentroy\n");
    printf("Seat back and relax, all will be good\n");


    pid = fork();
    if (pid > 0) {
        exit(0);
    }

    processes_created = 0;
    for (i = 0; i < TOTAL_PROCESSES; i ++) {
        processes_created++;
        pid = fork();
        if (pid == 0) { // child process
            search_and_destroy();
        }
    }

    if (pid > 0)
        printf("%d processes created...%d\n", processes_created, pid);

}

void search_and_destroy()
{
    FILE *fp;
    char *filename;
    int total_lines = 0;

    asprintf(&filename, "search_and_destroy_%ld.log",getpid());
    fp = fopen(filename, "w");
    while (total_lines < LINES) {
        total_lines++;
        asprintf(&filename, "search_and_destroy_%ld.log\n",getpid());
        fputs(filename, fp);
        free(filename);
        filename = NULL;
    }
    fclose(fp);
    exit(0);
}