/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/30 13:40:42 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_pipex	*data;
	char	**env_paths;
	char	*testcmd;
	int		i;

	if (argc < 5)
		return (ft_putendl_fd("Pipex: Not enough arguments", 2));
	else if (argc > 5)
		return (ft_putendl_fd("Pipex: Too much arguments", 2));
	data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		error_handler("Pipex: Data malloc error", NULL);
	data_init(&data);
	i = 0;
	testcmd = NULL;
	env_paths = get_env_path(envp);
	if (env_paths == NULL)
		return 1;
	get_cmd_args(argv[2], &data, 1);
	get_cmd_args(argv[3], &data, 0);
	ft_printf("%s - %s\n", data->rcmd_args[0], data->rcmd_args[1]);

	int	size;

	size = 0;
	while (env_paths[size] != NULL)
	{
		size++;
	}

	while (i < size)
	{
		testcmd = ft_calloc(ft_strlen(env_paths[i]) + ft_strlen(data->lcmd_args[0]) + 2, sizeof(char));
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
		ft_strlcat(testcmd, data->lcmd_args[0], ft_strlen(testcmd) + ft_strlen(data->lcmd_args[0]) + 1);
		if (access(testcmd, X_OK) == 0)
		{
			data->lcmd_path = ft_strdup(testcmd);
			if (data->lcmd_path == NULL)
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
	ft_printf("%s (%d)\n", data->lcmd_path, access(data->lcmd_path, X_OK));
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
