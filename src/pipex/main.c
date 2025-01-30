/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 11:02:20 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_pipex	*data;
	char	**env_paths;
	char	**cmd1;
	char	**cmd2;
	char	*testcmd;
	char	*cmd1_path;
	int		i;

	if (argc < 5)
		return (ft_putendl_fd("Pipex: Not enough arguments", 2));
	else if (argc > 5)
		return (ft_putendl_fd("Pipex: Too much arguments", 2));
	data_init(&data);
	i = 0;
	testcmd = NULL;
	cmd1_path = NULL;
	// cmd2_path = NULL;
	env_paths = get_env_path(envp);
	if (env_paths == NULL)
		return 1;
	cmd1 = ft_split(argv[2], ' ');
	if (cmd1 == NULL || cmd1[0] == NULL)
	{
		ft_putendl_fd("Pipex: cmd1 split error", 2);
		//TODO Free paths
		return (1);
	}
	cmd2 = ft_split(argv[3], ' ');
	if (cmd2 == NULL || cmd2[0] == NULL)
	{
		ft_putendl_fd("Pipex: cmd2 split error", 2);
		//TODO Free paths
		//TODO Free cmd1
		return (1);
	}
	ft_printf("%s - %s\n", cmd2[0], cmd2[1]);

	int	size;

	size = 0;
	while (env_paths[size] != NULL)
	{
		size++;
	}

	while (i < size)
	{
		testcmd = ft_calloc(ft_strlen(env_paths[i]) + ft_strlen(cmd1[0]) + 2, sizeof(char));
		if (testcmd == NULL)
		{
			ft_putendl_fd("Pipex: testcmd1 malloc error", 2);
			//TODO Free paths
			//TODO Free cmd1
			//TODO Free cmd2
			return (1);
		}
		ft_strlcat(testcmd, env_paths[i], ft_strlen(testcmd) + ft_strlen(env_paths[i]) + 1);
		ft_strlcat(testcmd, "/", ft_strlen(testcmd) + 2);
		ft_strlcat(testcmd, cmd1[0], ft_strlen(testcmd) + ft_strlen(cmd1[0]) + 1);
		if (access(testcmd, X_OK) == 0)
		{
			cmd1_path = ft_strdup(testcmd);
			if (cmd1_path == NULL)
			{
				ft_putendl_fd("Pipex: cmd1_path malloc error", 2);
				free(testcmd);
				//TODO Free paths
				//TODO Free cmd1
				//TODO Free cmd2
				return (1);
			}
			free(testcmd);
			break;
		}
		free(testcmd);
		i++;
	}
	ft_printf("%s (%d)\n", cmd1_path, access(cmd1_path, X_OK));
	free(cmd1_path);
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
