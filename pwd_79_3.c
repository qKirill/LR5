#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <limits.h>

#define PROG_NAME "pwd_79_3"       
#define VERSION   "1.0.0"
#define AUTHOR    "Балюра Кирило"   

static void print_help(void)
{
    printf("Використання: %s [-L | -P] [ОПЦІЇ]\n", PROG_NAME);
    printf("Виводить ім'я поточної робочої директорії.\n\n");
    printf("  -L         Вивести логічний шлях (з $PWD, враховуючи символічні лінки)\n");
    printf("  -P         Вивести фізичний шлях (розкриваючи всі символічні лінки)\n");
    printf("  --help     Показати цю допомогу та завершити роботу\n");
    printf("  --version  Показати версію утиліти\n");
    printf("  --author   Показати ім'я та прізвище розробника\n");
}

static int print_physical(void)
{
    char *path = realpath(".", NULL);
    if (path == NULL) {
        perror(PROG_NAME ": realpath");
        return 1;
    }
    printf("%s\n", path);
    free(path);
    return 0;
}

static int print_logical(void)
{
    const char *env = getenv("PWD");
    struct stat st_env, st_dot;

    if (env != NULL && env[0] == '/' && stat(env, &st_env) == 0 && stat(".", &st_dot) == 0 &&
        st_env.st_dev == st_dot.st_dev && st_env.st_ino == st_dot.st_ino) {
        printf("%s\n", env);
        return 0;
    }

    char buf[PATH_MAX];
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror(PROG_NAME ": getcwd");
        return 1;
    }
    printf("%s\n", buf);
    return 0;
}

