#include "../include/minishell.h"

int main(int ac, char **av)
{
	char s[] = "&&";
	char g[] = "&& ";

	if (ac >= 2)
		printf("%d\n", strncmp(s, g, atoi(av[1])));
}