#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define CONFIG_FILE "config.txt"

static char logLevel[32] = "info";
static int  logInterval  = 5;

static volatile sig_atomic_t reload_requested = 0;

static int loadConfig(void)
{
    FILE *f = fopen(CONFIG_FILE, "r");
    if (f == NULL) {
        perror("loadConfig: fopen");
        return -1;
    }

    char level[32];
    int interval;

    if (fscanf(f, "%31s %d", level, &interval) != 2 || interval <= 0) {
        fprintf(stderr, "loadConfig: невірний формат %s (очікується: <рівень> <інтервал>)\n",
                CONFIG_FILE);
        fclose(f);
        return -1;
    }
    fclose(f);

    snprintf(logLevel, sizeof(logLevel), "%s", level);
    logInterval = interval;

    printf("\n[CONFIG LOADED] logLevel: \"%s\", logInterval: %d\n\n", logLevel, logInterval);
    return 0;
}

static void handle_sigusr1(int sig)
{
    (void)sig;
    reload_requested = 1;
}

int main(void)
{
    if (loadConfig() == -1) {
        return 1;
    }

    printf("PID процесу: %d\n", (int)getpid());
    printf("Команда для перезавантаження конфігурації:\n");
    printf("  kill -USR1 %d\n\n", (int)getpid());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    while (1) {
        if (reload_requested) {
            reload_requested = 0;
            loadConfig();
        }

        printf("[%s] Повідомлення системи (інтервал %d сек)...\n", logLevel, logInterval);
        fflush(stdout);
        sleep(logInterval);
    }

    return 0;
}