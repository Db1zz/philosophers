#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <error.h>
#include <errno.h>

typedef struct t_str
{
	char *str;
}	t_str;

void	test(char *s, t_str *str)
{
	str->str = s;
}

int	main(void)
{
	t_str my_str;
	test("Hallo aus 42\n", &my_str);
	printf("%s", my_str.str);
	return (0);
}