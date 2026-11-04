#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = getpid();

    printf("Програму запущено. PID процесу: %d\n", (int)pid);
    printf("Команда для надсилання сигналу з іншого терміналу:\n");
    printf("  kill -3 %d\n\n", (int)pid);

    printf("Очікування сигналу... (Натисніть Ctrl+\\ у цьому терміналі для перевірки)\n");
    printf("Для виходу натисніть Ctrl+C\n");
    fflush(stdout);

    while (1) {
        sleep(1);
    }

    return 0;
}