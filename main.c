/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:25:09 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/28 16:50:35 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc > 1)
		return (write(2, "Usage: ./minishell\n", 20), 1);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		mshll_loop(env);
	return (0);
}
