#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	- le programme est normalement en SUID mais les machines de l'ecole ne me le permettent pas. donc faisons semblant que c'est le cas. 🤝
*/

int main(void) {
    char username[100] = {0};
    char password[100] = {0};
    char file_pass[50] = {0};
    FILE *fp = NULL;
    size_t len;

    // Ouvre le fichier contenant le mot de passe
    fp = fopen("pass", "r");
    if (fp == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    // Lit exactement 41 octets
    size_t read_len = fread(file_pass, 1, 40, fp);
    fclose(fp);

    if (read_len != 40) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }

    // Supprime le \n du mot de passe du fichier
    len = strcspn(file_pass, "\n");
    file_pass[len] = '\0';

    // Interface utilisateur
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username, sizeof(username), stdin);
    len = strcspn(username, "\n");
    username[len] = '\0';

    printf("--[ Password: ");
    fgets(password, sizeof(password), stdin);
    len = strcspn(password, "\n");
    password[len] = '\0';

    puts("*****************************************");

    // Vérifie le mot de passe
    if (strncmp(file_pass, password, 0x29) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }

    // VULNÉRABILITÉ : printf(username) sans format string
    printf(username);
    puts(" does not have access!");
    exit(1);
}
