/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/06 01:36:29 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char const *argv[], char *envp[])
{
	char	**env_paths;
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		fd_in;
	int		fd_out;
	t_pipex	*data;

	if (argc < 5)
		error_handler(ERR_LESS_ARGS, NULL, NULL, 1);
	else if (argc > 5)
		error_handler(ERR_MORE_ARGS, NULL, NULL, 1);
	data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		error_handler(ERR_DATA_MALLOC, NULL, NULL, 1);
	data_init(&data);
	env_paths = get_env_path(envp);
	get_cmd_args(argv[2], &data, env_paths, 1);
	get_cmd_args(argv[3], &data, env_paths, 0);
	get_cmd_path(&(data->lcmd_path), data->lcmd_args, &data, env_paths);
	get_cmd_path(&(data->rcmd_path), data->rcmd_args, &data, env_paths);
	if (pipe(pipefd) == -1)
		error_handler(ERR_PIPE, &data, env_paths, 1);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		error_handler(ERR_INFILE, &data, env_paths, 0);
	fd_out = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd_out < 0)
		error_handler(ERR_OUTFILE, &data, env_paths, 0);
	if (data->lcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, &data, env_paths, 0);
	else if(fd_in >= 0)
	{
		pid1 = fork();
		if (pid1 < 0)
			error_handler(ERR_FORK, &data, env_paths, 0);
		else if (pid1 == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(fd_in);
			close(fd_out);
			close(pipefd[0]);
			close(pipefd[1]);
			if (execve(data->lcmd_path, data->lcmd_args, NULL) == -1)
				error_handler(ERR_FORK, &data, env_paths, 0);
			end_program(&data, env_paths);
		}
	}
	if (data->rcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, &data, env_paths, 0);
	else if (fd_out >= 0)
	{
		pid2 = fork();
		if (pid2 < 0)
			error_handler(ERR_FORK, &data, env_paths, 0);
		else if (pid2 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_in);
			close(fd_out);
			close(pipefd[0]);
			close(pipefd[1]);
			if (execve(data->rcmd_path, data->rcmd_args, NULL) == -1)
				error_handler(ERR_FORK, &data, env_paths, 0);
			end_program(&data, env_paths);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_in);
	close(fd_out);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	end_program(&data, env_paths);
}

//? --track-fds=yes --track-origins=yes --keep-debuginfo=yes --leak-check=full --show-leak-kinds=all --trace-children=yes

	//! Si erreur avec une commande, passer a la suivante
	//! Si erreur de lecture du fichier d'entree, passer a la 2eme qui aura rien en entree
	//! Si erreur fichier de sortie, pas d'execution de la derniere commande
	//! Pour le limiteur -> Il faut que la ligne soit egale a "LIMITEUR\n" (ou \0)

	//! Penser a free
	//! Penser aux leaks
	//! Penser a gerer les retours d'erreur des commandes
	//! Afficher toutes les erreurs possibles
	//! Penser a VALGRIND
