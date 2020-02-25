#include "minishell.h"

void	first_part_of_pipe(size_t *i)
{
	dup2(sh()->fd[1], STDOUT_FILENO);
	//Ici je veut que ls sois envoyer sur pipefd[0]. Vue que ls ecris
	// sur STDOUT, je dois remplacer STDOUT par mon pipe de write
	close(sh()->fd[0]); //Je ferme les deux, car je n'en ai plus besoin,
	close(sh()->fd[1]); //Celui utile a deja ete dup.
	ft_exec((*i));
	//Aucun code apres execve ne seras executé, sauf si
	//celui-ci fail, du coup pas de code derriere sauf un return erreur
	exit(1);
}

void	ft_pipe(size_t *i)
{
	pid_t	pid;
	int		status;
	int		stdin_bkp;

	status = 0;
	stdin_bkp = dup(STDIN_FILENO);
	if (pipe(sh()->fd)) //J'ouvre le pipe
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "%s\n", strerror(errno));
	if (pid == 0) //Dans le child
		first_part_of_pipe(i);
	wait(NULL); //J'attend que mon ls se sois executer, sinon y a rien a lire
	(*i)++; //Dans le pere
 	close(sh()->fd[1]); //Plus beosin ici donc on close
	dup2(sh()->fd[0], STDIN_FILENO);
	ft_exec((*i));
	wait(NULL);
	dup2(stdin_bkp, STDIN_FILENO);
	close(sh()->fd[0]); // Je n'oublie pas de terminer de close mon pipe.
}
