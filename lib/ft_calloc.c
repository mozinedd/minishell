/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:04:34 by mozinedd          #+#    #+#             */
/*   Updated: 2025/06/16 20:05:05 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_calloc(size_t count, size_t size)
{
    void *pointer;
    pointer = malloc(count * size);
    if (pointer == NULL)
        return (NULL);
    ft_memset(pointer, 0, (count * size));
    return (pointer);
}
