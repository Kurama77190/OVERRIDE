#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#define SYSCALL_EXECVE 11
#define OFFSET_EAX (4 * 11) // EAX est le registre qui contient le syscall number en x86

int main(void) {
    pid_t pid;
    int status;
    long syscall_num;
    char buffer[128]; // buffer vulnérable

    memset(buffer, 0, sizeof(buffer));

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
	// Child process
    if (pid == 0) {
        // Empêche l'attach si parent meurt
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        puts("Give me some shellcode, k");

        // ⚠️ Vulnérabilité ici : gets() permet un overflow contrôlé
        gets(buffer);
        return (0);
    }
	// Parent process
    else {
        while (1) {
            wait(&status);

            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                puts("child is exiting...");
                break;
            }
            // Lire le registre EAX du process enfant
            syscall_num = ptrace(PTRACE_PEEKUSER, pid, OFFSET_EAX, 0);

            if (syscall_num == SYSCALL_EXECVE) {
                puts("no exec() for you");
				// Tuer le process enfant si il utilise execve
                kill(pid, SIGKILL);
                break;
            }
        }
    }
    return (0);
}
