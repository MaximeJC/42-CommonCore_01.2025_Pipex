/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/04 16:17:08 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char const *argv[], char *envp[])
{
	char	**env_paths;
	// int		pipefd[2];
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
	// TODO Add verif si rien trouve => data->lcmd_path uninitialized (pour commande suivante)
	if (data->lcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, &data, env_paths, 0);
	if (data->rcmd_path == NULL)
		error_handler(ERR_CMD_NOT_FOUND, &data, env_paths, 0);
	end_program(&data, env_paths);
}

//? --track-fds=yes --track-origins=yes --keep-debuginfo=yes --leak-check=full --show-leak-kinds=all --trace-children=yes

	//! Si erreur avec une commande, passer a la suivante
	//! Si erreur de lecture du fichier d'entree, passer a la 2eme qui aura rien en entree
	//! Si erreur fichier de sortie, pas d'execution de la derniere commande
	//! Pour le limiteur -> Il faut que la ligne soit egale a "LIMITEUR\n" (ou \0)

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
