/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:31:13 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/08 20:22:20 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get value : status : any number 
//			 : is_get = 1
//-----------------------------
// set value : status : your new  exit status
//           : is_get : 0

int exit_status(int status, int is_get)
{
	static int state;
	if (is_get == 0)
		state = status;
	return state;
}
