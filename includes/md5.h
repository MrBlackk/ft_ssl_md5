/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchornyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:54:55 by vchornyi          #+#    #+#             */
/*   Updated: 2018/10/22 20:54:56 by vchornyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include "common.h"

# define MD5_LENGTH 32

typedef unsigned int t_round(unsigned int x, unsigned int y, unsigned int z);
typedef struct s_md	t_md;

struct	s_md
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;
	size_t			len;
};

#endif
