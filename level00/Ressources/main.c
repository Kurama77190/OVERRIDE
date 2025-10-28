#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*args[] = {"/bin/sh", NULL };
	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");

	int buffer;
	scanf("%d", &buffer);
	if (buffer != 5276) { // <---- the password is here.
		puts("\nInvalid Password!");
	} else {
		puts("\nAuthenticated!");
		execve("/bin/sh", args, envp);
	}
	return (0);
}

