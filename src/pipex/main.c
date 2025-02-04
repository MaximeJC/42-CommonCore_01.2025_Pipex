/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/04 10:53:05 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_pipex	*data;
	char	**env_paths;

	if (argc < 5)
		error_handler("Pipex: Not enough arguments", NULL, NULL, 1);
	else if (argc > 5)
		error_handler("Pipex: Too much arguments", NULL, NULL, 1);
	data = ft_calloc(1, sizeof(t_pipex));
	if (data == NULL)
		error_handler("Pipex: Data malloc error", NULL, NULL, 1);
	data_init(&data);
	env_paths = get_env_path(envp);
	get_cmd_args(argv[2], &data, env_paths, 1);
	get_cmd_args(argv[3], &data, env_paths, 0);

	//! Si erreur avec une commande, passer 0 la suivante
	//! Si erreur de lecture du fichier d'entree, passer a la 2eme qui aura rien en entree
	//! Si erreur fichier de sortie, pas d'execution de la derniere commande
	//! Pour le limiteur -> Il faut que la ligne soit egale a "LIMITEUR\n" (ou \0)

	// TODO Add verif si rien trouve => data->lcmd_path uninitialized (pour commande suivante)
	if (data->lcmd_path != NULL)
		ft_printf("%s (%d)\n", data->lcmd_path, access(data->lcmd_path, X_OK));
	else
		error_handler("Pipex: command not found / have permision to execute it",
			&data, env_paths, 0);
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
