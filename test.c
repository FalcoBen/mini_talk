#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_context
{
    unsigned char received_char;
    int bit_count;
} t_context;

void handle_signal(int sig, siginfo_t *info, void *ucontext)
{
    static t_context ctx = {0, 0}; // Static variable to maintain state between signals

    (void)ucontext; // Unused parameter

    if (sig == SIGUSR1)
        ctx.received_char |= (0 << ctx.bit_count); // Add 0 to the current bit position
    else if (sig == SIGUSR2)
        ctx.received_char |= (1 << ctx.bit_count); // Add 1 to the current bit position

    ctx.bit_count++;
    if (ctx.bit_count == 8) // When a full byte is received
    {
        if (ctx.received_char == '\0') // End of message
            write(1, "\n", 1);
        else
            write(1, &ctx.received_char, 1); // Print the character
        ctx.received_char = 0;
        ctx.bit_count = 0;
    }

    // Acknowledge the signal by sending SIGUSR1 back to the client
    kill(info->si_pid, SIGUSR1);
}

int main(int ac, char **av)
{
    if (ac != 1)
    {
        printf("Usage: ./server\n");
        return 1;
    }

    struct sigaction sa;
    sa.sa_sigaction = handle_signal; // Use sa_sigaction instead of sa_handler
    sa.sa_flags = SA_SIGINFO;       // Enable passing additional info to the handler
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("Server PID: %d\n", getpid());

    while (1)
        pause(); // Wait for signals

    return 0;
}