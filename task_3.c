#include <stdio.h>

#define CONFIG_FILE "config.txt"

static char logLevel[32] = "info";
static int  logInterval  = 5;

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

int main(void)
{
    return loadConfig() == 0 ? 0 : 1;
}