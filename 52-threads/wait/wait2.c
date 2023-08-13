#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

void print_rusage(int pid, struct rusage *pUsage)
{
    printf("╒══════╤════════════════════════════════════╤══════╕\n");
    printf("│%-6s│ %-35s│%-6s│\n", "PID", "Parameter", "value");
    printf("│------│------------------------------------│------│\n");
    printf("│%-6d│ %-35s│%-2ld:%3ld│\n", pid, "Total user space time", pUsage->ru_utime.tv_sec, pUsage->ru_utime.tv_usec);
    printf("│%-6d│ %-35s│%-2ld:%3ld│\n", pid, "Total kernel space time" , pUsage->ru_stime.tv_sec, pUsage->ru_stime.tv_usec);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Max resident set size", pUsage->ru_maxrss);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Max integral shared memory size", pUsage->ru_ixrss);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Max integral unshared data size", pUsage->ru_idrss);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Max integral unshared stack size", pUsage->ru_isrss);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Soft page faults", pUsage->ru_minflt);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Hard page faults", pUsage->ru_majflt);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num swaps", pUsage->ru_nswap);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num block input operations", pUsage->ru_inblock);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num block output operations", pUsage->ru_oublock);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num IPC messages sent", pUsage->ru_msgsnd);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num IPC messages received", pUsage->ru_msgrcv);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num of signals received", pUsage->ru_nsignals);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num voluntary context switches", pUsage->ru_nvcsw);
    printf("│%-6d│ %-35s│%-6ld│\n", pid, "Num involuntary context switches", pUsage->ru_nivcsw);
    printf("╘══════╧════════════════════════════════════╧══════╛\n");
}

int main()
{
    int wStatus;
    int pid = fork();
    struct rusage usage = {0};
    int rc = 0;

    if(0 == pid)
    {
        // child process
        printf("child: hello\n");
        sleep(1);

        printf("child: hello\n");
        sleep(1);

        printf("child: hello\n");
        sleep(1);
        
        _exit(EXIT_SUCCESS);
    }
    else
    {
        // parent process
    }

    wait(&wStatus);
    if(WIFEXITED(wStatus))
    {
        printf("process %d: returned with status %d\n", pid, WEXITSTATUS(wStatus));
        rc = getrusage(RUSAGE_CHILDREN, &usage);    
        if(rc < 0)
        {
            perror("getrusage() failed");
            _exit(EXIT_FAILURE);
        }
        print_rusage(pid, &usage);
    }

}
