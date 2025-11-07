#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void decrypt(int key);
void test(char *input, char *magic_ptr);

int main(void)
{
    char buffer[100];
    unsigned int seed;

    seed = time(NULL);
    srand(seed);

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");

    printf("Password: ");
    scanf("%99s", buffer);  // Lecture du mot de passe (sans \n)

    test(buffer, (char *)0x1337d00d);  // Appel avec une valeur magique

    return 0;
}

void test(char *input, char *magic_ptr)
{
    int key = (int)((long)magic_ptr - (long)atoi(input));
    if (key >= 1 && key <= 21) {
        decrypt(key);
    } else {
        decrypt(rand());
    }
}

void decrypt(int key)
{
    unsigned char encrypted[] = {
        0x51, 0x7d, 0x7c, 0x75, 0x60, 0x73, 0x66, 0x67,
        0x7e, 0x73, 0x66, 0x7b, 0x7d, 0x7c, 0x61, 0x33, 0x00
    };

    char decrypted[sizeof(encrypted)];
    for (int i = 0; i < sizeof(encrypted) - 1; i++) {
        decrypted[i] = encrypted[i] ^ key;
    }
    decrypted[sizeof(encrypted) - 1] = '\0';

    if (strncmp(decrypted, "Congratulations!", 16) == 0) {
        system("/bin/sh");
    } else {
        puts("\nInvalid Password");
    }
}
