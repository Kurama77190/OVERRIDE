#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/ptrace.h>

int auth(const char *login, unsigned int serial);

int main(void) {
    char login[32];
    unsigned int serial;



    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    printf("-> Enter Login: ");
    fgets(login, sizeof(login), stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    if (auth(login, serial) == 0) {
        puts("Authenticated!");
        system("/bin/sh");
    }

    return 0;
}

int auth(const char *login, unsigned int serial) {
	size_t len = strcspn(login, "\n");
	char clean_login[32];
	strncpy(clean_login, login, sizeof(clean_login));
	clean_login[len] = '\0';

	len = strnlen(clean_login, 32);
	if ((int)len < 6) {
		return 1;  // trop court
	}

	// Détection de debugger
	if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m'---------------------------'");
		return 1;
	}

	unsigned int calc = ((int)clean_login[3] ^ 4919) + 6221293;

	for (int i = 0; i < (int)len; i++) {
		if (clean_login[i] < ' ') {
			return 1;  // caractère de contrôle interdit
		}
		calc += ((int)clean_login[i] ^ calc) % 1337;
	}

	if (serial == calc) {
		return 0;  // OK
	} else {
		return 1;  // Mauvais serial
	}
}
