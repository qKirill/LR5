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

