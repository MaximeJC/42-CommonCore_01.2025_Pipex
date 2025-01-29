/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/29 16:41:37 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**check_path(char *envp[])
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
	{
		ft_putendl_fd("Pipex: envp reading error", 2);
		// exit(EXIT_FAILURE);
		return (NULL);
	}
	path = ft_strdup(envp[i] + 5);
	if (path == NULL)
	{
		ft_putendl_fd("Pipex: envp path duplication error", 2);
		// exit(EXIT_FAILURE);
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (paths == NULL)
	{
		free(path);
		ft_putendl_fd("Pipex: envp path split error", 2);
		return (NULL);
	}
	free(path);
	return (paths);
}

int	main(int argc, char const *argv[], char *envp[])
{
	(void)argc;
	char	**paths;
	char	**cmd1;
	char	**cmd2;

	paths = check_path(envp);
	if (paths == NULL)
		return 1;
	cmd1 = ft_split(argv[2], ' ');
	if (cmd1 == NULL || cmd1[0] == NULL)
	{
		//TODO Free paths
		return (1);
	}
	cmd2 = ft_split(argv[3], ' ');
	if (cmd2 == NULL || cmd2[0] == NULL)
	{
		//TODO Free paths
		//TODO Free cmd1
		return (1);
	}
	ft_printf("%s - %s\n", cmd2[0], cmd2[1]);
	ft_printf("%d", access("/usr/bin/ls", X_OK));
}






/* int main(int argc, char *argv[])
{
	int	pipefd[2];
	int	fd_in;
	int	fd_out;

	if (argc != 5)
	{
		ft_putendl_fd("Pipex: Wrong arguments count!", 2);
		exit(EXIT_FAILURE);
	}
	fd_out = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0777);		// * >
	fd_in = open(argv[1], O_RDONLY);										// * <
	if (fd_in < 0)
	{
		ft_putendl_fd("Pipex: Can't open input file!", 2);
		// close(fd_out);
		// exit(EXIT_FAILURE);
	}
	if (fd_in > 0)
		close(fd_in);
	close(fd_out);
	return 0;
} */

		//! Penser a free
		//! Penser aux leaks
		//! Penser a gerer les retours d'erreur des commandes
		//! Afficher toutes les erreurs possibles
		//! Penser a VALGRIND
