#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOGIN_LEN 6
#define NUM_ENTRIES 10

unsigned int generate_serial(const char *login) {
    unsigned int calc = (login[3] ^ 0x1337) + 6221293;

    for (int i = 0; i < LOGIN_LEN; i++) {
        calc += (login[i] ^ calc) % 1337;
    }

    return calc;
}

void generate_random_login(char *login) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < LOGIN_LEN; i++) {
        login[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    login[LOGIN_LEN] = '\0';
}

int main() {
    srand(time(NULL));

    char login[LOGIN_LEN + 1];
    unsigned int serial;

    printf("Generated Logins + Serials:\n");
    printf("----------------------------\n");

    for (int i = 0; i < NUM_ENTRIES; i++) {
        generate_random_login(login);
        serial = generate_serial(login);
        printf("Login : %-10s Serial : %u\n", login, serial);
    }

    return 0;
}