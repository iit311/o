
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    int pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child: PID = %d\n", getpid());
        sleep(3);
        printf("Child completed.\n");
        exit(0);
    }
    else {
        // Parent process
        printf("Parent: PID = %d\n", getpid());

        // ZOMBIE STATE
        sleep(5);
        printf("Zombie state demonstration completed.\n");

        wait(NULL);  // Removes zombie child

        // ORPHAN STATE
        int pid2 = fork();

        if (pid2 == 0) {
            printf("\nOrphan child: PID = %d\n", getpid());
            printf("Original parent PID = %d\n", getppid());

            sleep(5);

            printf("New parent PID = %d\n", getppid());
        }
        else {
            printf("Parent terminating now.\n");
            exit(0);
        }
    }

    return 0;
}
