/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:25:51 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/11 18:10:18 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cmdsize(t_cmds *cmd)
	{
		t_cmds *curr = cmd;
		int counter = 0;
		
		if (!curr)
			return 0;
		while(curr){
			counter++;
			curr = curr->next;
		}
		return counter;
	}
    
    void execute_command(t_glob *global)
    {
        int ft_cmd_size = 0;

		// t_commands *current;
		// current = cmd;
		// while(current)
		// {
		// 	printf("the command 0 is : %s\n", current->cmd[0]);
		// 	printf("the command 1 is : %s\n", current->cmd[1]);
		// 	printf("the command 2 is : %s\n", current->cmd[2]);
		// 	printf("the inoutfile 0 is : %s\n", current->inoutfile[0]);
		// 	printf("the inoutfile 1 is : %s\n", current->inoutfile[1]);
		// 	current = current->next;
		// }

        ft_cmd_size = ft_cmdsize(global->cmd);
		// ft_cmd_size = 1;
        if (ft_cmd_size > 1)
        {
            printf("handle multiple command\n");
            handle_multiple_command(global);
        }
        else
        {
			if (check_is_builtin(global->cmd))
				exec_is_builtin(&global->env, global->cmd);
			else
				handle_single_command(global);
        }
    }