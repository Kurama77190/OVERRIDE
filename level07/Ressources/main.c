#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int get_unum(void);
void clear_stdin(void);
int store_number(int *data);
int read_number(int *data);

int main(int argc, char **argv, char **envp) {
    int data[100] = {0};
    char input[20] = {0};
    int status = 1;

    // Nettoyage des arguments
    for (int i = 0; argv[i] != NULL; i++) {
        memset(argv[i], 0, strlen(argv[i]));
    }
    for (int i = 0; envp[i] != NULL; i++) {
        memset(envp[i], 0, strlen(envp[i]));
    }

    puts("----------------------------------------------------");
    puts("  Welcome to wil's crappy number storage service!   ");
    puts("----------------------------------------------------");
    puts(" Commands:                                          ");
    puts("    store - store a number into the data storage    ");
    puts("    read  - read a number from the data storage     ");
    puts("    quit  - exit the program                        ");
    puts("----------------------------------------------------");
    puts("   wil has reserved some storage :>                 ");
    puts("----------------------------------------------------");

    while (1) {
        printf("Input command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Supprimer le newline

        if (strncmp(input, "store", 5) == 0) {
            status = store_number(data);
        } else if (strncmp(input, "read", 4) == 0) {
            status = read_number(data);
        } else if (strncmp(input, "quit", 4) == 0) {
            break;
        }

        if (status == 0) {
            printf(" Completed %s command successfully\n", input);
        } else {
            printf(" Failed to do %s command\n", input);
        }

        memset(input, 0, sizeof(input));
    }

    return 0;
}

unsigned int get_unum(void) {
    unsigned int num = 0;
    fflush(stdout);
    scanf("%u", &num);
    clear_stdin();
    return num;
}

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int store_number(int *data) {
    unsigned int number, index;

    printf(" Number: ");
    number = get_unum();
    printf(" Index: ");
    index = get_unum();

    if (index % 3 == 0 || (number >> 24) == 0xB7) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    data[index] = number;
    return 0;
}

int read_number(int *data){
    unsigned int index;
    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, data[index]);
    return 0;
}
