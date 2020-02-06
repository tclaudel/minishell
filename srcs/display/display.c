/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tclaudel <tclaudel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 09:22:05 by tclaudel     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 13:21:23 by tclaudel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "minishell.h"

void		printf_welcome(void)
{
	ft_printf(""YELLOW"\n################################################");
	ft_printf("################################\n\n");
	ft_printf(""LIGHT_PINK"\n\t\t __  __ ___ _   _ ___ ____  _");
	ft_printf("   _ _____ _     _   \n");
	ft_printf(""YELLOW"\t\t|  \\/  |_ _| \\ | |_ _/ ___|| | | | ");
	ft_printf("____| |   | |  \n");
	ft_printf(""BLUE"\t\t| |\\/| || ||  \\| || |\\___ \\| |_| |  _");
	ft_printf("| | |   | |  \n");
	ft_printf(""GREEN"\t\t| |  | || || |\\  || | ___) |  _  | |___|");
	ft_printf(" |___| |___ \n");
	ft_printf(""LIGHT_RED"\t\t|_|  |_|___|_| \\_|___|____/|_| |_|__");
	ft_printf("___|_____|_____|\n");
	ft_printf(""YELLOW"\n\n\n########################################");
	ft_printf("###############");
	ft_printf("#########################\n\n"RESET"");
	ft_printfducul("\tCreated by\t: coscialp & tclaudel\n");
	ft_printf("\tGithub\t\t: https://github.com/tclaudel/minishell\n\n\n");
}

void		print_prompt(t_strhash *hash)
{
	if (ft_get_hash_value(hash, "PWD"))
	{
		ft_dprintf(1, ""YELLOW_BOLD "%s: "DARK_BLUE"%s : " RESET"",
			ft_get_hash_value(hash, "USER"),
			ft_strrchr(ft_get_hash_value(hash, "PWD"), '/'));
	}
	else
		ft_dprintf(1, ""YELLOW_BOLD "%s: "DARK_BLUE"%s : " RESET"",
			ft_get_hash_value(hash, "USER"), NULL);
}
