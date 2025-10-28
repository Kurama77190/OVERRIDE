#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool verify_user_name(void);
bool verify_user_pass(const char *pass);

char a_user_name[256];

int main(void)
{
    unsigned char password[64]; // <-- we can exploit this variable with a stack overflow
    bool check = false;

    memset(password, 0, sizeof(password));

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, sizeof(a_user_name), stdin);

    check = verify_user_name();
    if (check == true)
	{
        puts("Enter Password: ");
        fgets((char *)password, 100, stdin); // <-- We can overflow password here.

        check = verify_user_pass((const char *)password);

        if ((check == true) || (check != false))
		{
            puts("nope, incorrect password...\n");
            return (1);
        }
		else
		{
            return (0);
        }
    }
	else
	{
        puts("nope, incorrect username...\n");
        return (1);
    }
	return (0);
}

bool verify_user_name(void)
{
    puts("verifying username....\n");
    return (strncmp(a_user_name, "dat_wil", 7) == 0 ? true : false);
}

bool verify_user_pass(const char *pass)
{
	puts("verifying password....\n");
    return (strncmp(pass, "admin", 5) == 0 ? true : false);
}
