/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/28 11:09:47 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	int	fd_out;
	int	fd_in;

	if (argc != 5)
	{
		ft_putendl_fd("Pipex: Wrong arguments count!", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		fd_out = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0777);		// * >
		fd_in = open(argv[1], O_RDONLY);										// * <
		if (fd_in < 0)
		{
			ft_putendl_fd("Pipex: Can't open input file!", 2);
			// close(fd_out);
			// exit(EXIT_FAILURE);
		}

		//TODO Execute all commands one by one

		//! Penser a free
		//! Penser aux leaks
		//! Penser a gerer les retours d'erreur des commandes
		//! Afficher toutes les erreurs possibles
		//! Penser a VALGRIND
	}
	if (fd_in > 0)
		close(fd_in);
	close(fd_out);
	return 0;
}
