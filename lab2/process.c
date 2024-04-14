#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/logger.h"

void main()
{
    pid_t pid;
    pid = fork();
    init_logger("process_logs.txt", 1, 1);

    switch(pid)
    {
        case -1:
            log_error("fork error");
            destroy_logger();
            exit(1);

        case 0:
            log_info("Дочерний процесс: pid = %d, ppid = %d", getpid(), getppid());
            sleep(5);
            break;

        default:
            log_info("Родительский процесс: pid = %d", getpid());
            sleep(5);
            break;
    }
    destroy_logger();
    return 0;
}