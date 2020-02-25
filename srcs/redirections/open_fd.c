#include "minishell.h"

int		redirect_output(char *filename)
{
	int	fd;

	if (!(fd = open(filename, O_WRONLY | O_APPEND | O_CREAT | S_IRWXU)));
		return (-1);
	return (fd);
}