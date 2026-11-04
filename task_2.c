#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static void handle_sigquit(int sig)
{
    (void)sig;
    static const char msg[] = "\nОтримано SIGQUIT\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void)
{
    pid_t pid = getpid();

    printf("Програму запущено. PID процесу: %d\n", (int)pid);
    printf("Команда для надсилання сигналу з іншого терміналу:\n");
    printf("  kill -3 %d\n\n", (int)pid);

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigquit;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Очікування сигналу... (Натисніть Ctrl+\\ у цьому терміналі для перевірки)\n");
    printf("Для виходу натисніть Ctrl+C\n");
    fflush(stdout);

    while (1) {
        sleep(1);
    }

    return 0;
}