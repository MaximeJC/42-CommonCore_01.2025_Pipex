/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:52:20 by mgouraud          #+#    #+#             */
/*   Updated: 2025/02/04 11:42:55 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* int main(int argc, char *argv[])
{
	int	fd_out;
	int	fd_in;

	if (argc < 5 || (argc < 6 && !ft_strncmp(argv[2], "here_doc", 8)))
	{
		ft_putendl_fd("Pipex: Not enough arguments!", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (!ft_strncmp(argv[2], "here_doc", 8))
		{
			fd_in = 0;								// * <<
			fd_out = open(argv[argc - 1], O_RDWR | O_APPEND | O_CREAT, 0777);
					// * >>
			//TODO Gestion << et >>
		}
		else
		{
			fd_in = open(argv[1], O_RDONLY);		// * <
			if (fd_in < 0)
			{
				ft_putendl_fd("Pipex: Can't open input file!", 2);
				exit(EXIT_FAILURE);
			}
			fd_out = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0777);
					// * >
			//TODO Get file 2 (argv[argc - 1])
		}
		//TODO Check if exist and Get file 1 (argv[1])

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
} */
