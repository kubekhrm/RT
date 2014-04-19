/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 04:18:02 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/02/17 21:43:26 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_memory.h>
#include <ft_strings.h>

void	ft_strclr(char *s)
{
	if (s)
		ft_bzero(s, ft_strlen(s));
}