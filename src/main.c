/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/28 15:25:04 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
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
}

		//! Penser a free
		//! Penser aux leaks
		//! Penser a gerer les retours d'erreur des commandes
		//! Afficher toutes les erreurs possibles
		//! Penser a VALGRIND
