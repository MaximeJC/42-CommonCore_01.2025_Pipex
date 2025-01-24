/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgouraud <mgouraud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:34 by mgouraud          #+#    #+#             */
/*   Updated: 2025/01/24 17:01:05 by mgouraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		ft_putendl_fd("Not enough arguments!", 2);
		return 0;
	}
	if (!ft_strncmp(argv[2], "here_doc", 9))
	{
		//TODO Gestion << et >>
	}
	else
	{
		//TODO Get file 2 (argv[argc - 1])
		//TODO Check if exist and Get file 1 (argv[1])

		//TODO Execute all commands one by one

		//! Penser a close
		//! Penser a free
		//! Penser aux leaks
		//! Penser a gerer les retours d'erreur des commandes
		//! Afficher toutes les erreurs possibles
	}

	return 0;
}
