/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:48:14 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/02 22:50:51 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    int i;
    int j;
    int lentofs1s2;
    char *allstr;

    i = 0;
    j = 0;

    lentofs1s2 = ft_strlen(s1) + ft_strlen(s2);
    allstr = malloc(lentofs1s2 + 1);
    if (!allstr)
        return (NULL);
    while(s1 != NULL && s1[i])
    {
        allstr[j++] = s1[i++];
    }
    i = 0;
    while (s2 != NULL && s2[i])
    {
        allstr[j++] = s2[i++];
    }
    allstr[j] = '\0';
    return (allstr);
}