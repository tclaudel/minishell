#include "minishell.h"

void		printf_welcome(void)
{
	ft_printf(""YELLOW"\n######################################################");
	ft_printf("##########################\n\n");
	ft_printf(""LIGHT_PINK"\n\t\t __  __ ___ _   _ ___ ____  _   _ _____ _     _   \n");
	ft_printf(""YELLOW"\t\t|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |  \n");
	ft_printf(""BLUE"\t\t| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |  \n");
	ft_printf(""GREEN"\t\t| |  | || || |\\  || | ___) |  _  | |___| |___| |___ \n");
	ft_printf(""LIGHT_RED"\t\t|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|\n");
	ft_printf(""YELLOW"\n\n\n#######################################################");
	ft_printf("#########################\n\n"RESET"");
	ft_printf("\tCreated by\t: coscialp & tclaudel\n");
	ft_printf("\tGithub\t\t: https://github.com/tclaudel/minishell\n\n\n");
}

void		print_prompt(t_strhash *hash)
{
	if (ft_get_hash_value(hash, "PWD"))
	{
		ft_dprintf(1, ""YELLOW_BOLD "%s: "GREY"%s : " RESET"",
			ft_get_hash_value(hash, "USER"),
			ft_strrchr(ft_get_hash_value(hash, "PWD"), '/'));
	}
	else
		ft_dprintf(1, ""YELLOW_BOLD "%s: "GREY"%s : " RESET"",
			ft_get_hash_value(hash, "USER"), NULL);
}
